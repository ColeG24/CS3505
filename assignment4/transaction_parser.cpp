#include "transaction_parser.h"
#include <string.h>
#include <unordered_map>

#include "food_item.h"
#include "warehouse.h"
#include "request.h"
#include "receive.h"
#include <boost/date_time/gregorian/gregorian.hpp>
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

vector<request> transaction_parser::get_requests(boost::gregorian::date startDate)
{

}

vector<receive> transaction_parser::get_receives(boost::gregorian::date startDate)
{

}

vector<food_item> transaction_parser::get_food_items()
{

}

vector<warehouse> transaction_parser::get_warehouses()
{

}

boost::gregorian::date transaction_parser::get_start_date()
{

}

int transaction_parser::get_number_of_days()
{

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
    process_start_date(iss);
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

}

void transaction_parser::process_warehouse(istringstream & iss)
{
}

void transaction_parser::process_start_date(istringstream & iss) 
{
}

void transaction_parser::process_receive(istringstream & iss) 
{
}

void transaction_parser::process_request(istringstream & iss)
{
}

void transaction_parser::process_next()
{

}

void transaction_parser::process_end()
{
  reachedEnd = true;
}
