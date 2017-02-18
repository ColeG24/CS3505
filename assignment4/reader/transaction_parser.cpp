/*
 *  Defines the transaction parser.
 */

#include "transaction_parser.h"
#include <string>
#include <unordered_map>
#include "../processor/food_item.h"
#include "../processor/warehouse.h"
#include "transaction.h"
#include "file_data.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

transaction_parser::transaction_parser(string filename) :
  reachedEnd(false), numDays(0)
{
  ifstream file(filename);
  std::string line;

  // Process each line.
  while (getline(file, line))
  {
    process_line(line);  
  }

  // Store all data into data struct.
  data.transactions = transactions;
  data.warehouses = warehouses;
  data.foodItems = foodItems;
  data.numDays = numDays;
}

file_data transaction_parser::get_file_data() const
{
  return data;
}

// Processes each line according to its first word.
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

// Processes a food item.
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

  food_item food(name, upc, shelfLife);

  foodItems.emplace(upc, food);
}

// Processes a warehouse.
void transaction_parser::process_warehouse(istringstream & iss)
{
  iss.ignore(256, '-');
  string warehouseName;
  iss >> warehouseName;
  warehouse warehouse (warehouseName);

  warehouses.emplace(warehouseName, warehouse);
}

// Processes the start date.
void transaction_parser::process_start_date() 
{
  startDate = 0;
  
  vector<transaction> tranStart;
  transactions.push_back(tranStart);
}

// Processes a receive.
void transaction_parser::process_receive(istringstream & iss) 
{
  string upc;
  iss >> upc;

  int count;
  iss >> count;

  string warehouse;
  iss >> warehouse;

  // Create transaction and add to vector.
  transaction receive (upc, warehouse, count, "receive", numDays);
  transactions[numDays].push_back(receive);
}

// Processes a request.
void transaction_parser::process_request(istringstream & iss)
{
  string upc;
  iss >> upc;

  int count;
  iss >> count;

  string warehouse;
  iss >> warehouse;

  // Create transaction and add to vector.
  transaction request (upc, warehouse, count, "request", numDays);
  transactions[numDays].push_back(request);
}

// Processes the next day.
void transaction_parser::process_next()
{
  numDays++;

  vector<transaction> transForDay;
  transactions.push_back(transForDay);
}

// Processes end of file.
void transaction_parser::process_end()
{
  reachedEnd = true;
}
