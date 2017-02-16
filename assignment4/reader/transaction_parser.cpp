#include "transaction_parser.h"
#include <string>
#include <unordered_map>

#include "../processor/food_item.h"
#include "../processor/warehouse.h"
#include "request.h"
#include "receive.h"
#include <fstream>
#include <sstream>

using namespace std;

transaction_parser::transaction_parser(string filename) :
  reachedEnd(false)
{
  // TODO make sure we handle bad files ok
  ifstream file(filename);
  std::string line;
  while (getline(file, line))
  {
    process_line(line);  
  }
}

unordered_map<int, vector<request>> transaction_parser::get_requests_map()
{
  return requests;
}

unordered_map<int, vector<receive>> transaction_parser::get_receives_map()
{
  return receives;
}

unordered_map<string, food_item> transaction_parser::get_food_items_map()
{
  return foodItems;
}

unordered_map<string, warehouse> transaction_parser::get_warehouse_map()
{
  return warehouses;
}

int transaction_parser::get_number_of_days()
{
  return numDays;
}

void transaction_parser::add_day()
{
  numDays++;
}

void transaction_parser::process_line(string line) 
{
  istringstream iss(line);

  string firstWord;
  iss >> firstWord;
  
  if ("FoodItem" == firstWord)
  {
    process_food_item(iss);
  }
  else if ("Warehouse" == firstWord)
  {
    process_warehouse(iss);
  }
  else if ("Start" == firstWord)
  {
    process_start_date();
  }
  else if ("Receive:" == firstWord) 
  {
    process_receive(iss);
  }
  else if ("Request:" == firstWord) 
  {
    process_request(iss);
  }
  else if ("Next" == firstWord)
  {
    process_next();
  }
  else if ("End" == firstWord)
  {
    process_end();
    return;
  }
}

void transaction_parser::process_food_item(istringstream & iss) 
{
  iss.ignore(256, ':');
  string upc;
  iss >> upc;
  
  iss.ignore(256, ':');
  int shelfLife;
  iss >> shelfLife;

  iss.ignore(256, ':');
  iss.ignore();
  string name;
  getline(iss, name);

  cout << upc << " " << shelfLife << " " << name << endl;

  food_item food(name, upc, shelfLife);
}

void transaction_parser::process_warehouse(istringstream & iss)
{
  iss.ignore(256, '-');
  string warehouseName;
  iss >> warehouseName;

  cout << warehouseName << endl;

  // Create warehouse and add to warehouses.
  //  warehouse warehouse (warehouseName);

  // Add warehouse to warehouse map..
}

void transaction_parser::process_start_date() 
{
  startDate = 0;
}

void transaction_parser::process_receive(istringstream & iss) 
{
  string upc;
  iss >> upc;

  int count;
  iss >> count;

  string warehouse;
  iss >> warehouse;

  cout << upc << " " << count << " " << warehouse << endl;
}

void transaction_parser::process_request(istringstream & iss)
{
  
  string upc;
  iss >> upc;

  int count;
  iss >> count;

  string warehouse;
  iss >> warehouse;

  cout << upc << " " << count << " " << warehouse << endl;
}

void transaction_parser::process_next()
{
  add_day();
}

void transaction_parser::process_end()
{
  reachedEnd = true;
}
