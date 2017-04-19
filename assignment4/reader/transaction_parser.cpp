/*
 * AUTHORS: Cole Gordon & Philipp Hojnacki
 */
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
  reachedEnd(false), numDays(0), warehouses(*new unordered_map<string, warehouse>()), foodItems(*new unordered_map<string, food_item>()), file(*new ifstream(filename))
{
  std::string line;

  // Process the warehouses and 
  while (getline(file, line))
  {
    if (!process_header(line))
      break;
  }	
}

// Processes each line according to its first word.
bool transaction_parser::process_header(string & line) 
{
  istringstream iss(line);

  string firstWord;
  iss >> firstWord;
  
  if ("FoodItem" == firstWord)
  {
    process_food_item(iss);
    return true;
  }
  else if ("Warehouse" == firstWord)
  {
    process_warehouse(iss);
    return true;
  }
  else
  {
    return false;
  }
}

transaction * transaction_parser::next_item() {
  
  string line;    
  string firstWord;
  istringstream * iss = NULL; 

  do {
    iss = new istringstream(line);   
    getline(file, line);    
    *iss >> firstWord; 
    if ("Next" == firstWord)
      numDays++;
  }
  while ("Next" == firstWord);

  if ("Receive:" == firstWord) 
  {
    return & process_receive(*iss);
  }
  else if ("Request:" == firstWord) 
  {
    return & process_request(*iss);
  }
  else 
  {
    process_end();
    return NULL;
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

// Processes a receive.
transaction & transaction_parser::process_receive(istringstream & iss) 
{
  string upc;
  iss >> upc;

  int count;
  iss >> count;

  string warehouse;
  iss >> warehouse;

  return *new transaction (upc, warehouse, count, "receive", numDays);
}

// Processes a request.
transaction & transaction_parser::process_request(istringstream & iss)
{
  string upc;
  iss >> upc;

  int count;
  iss >> count;

  string warehouse;
  iss >> warehouse;

  return *new transaction (upc, warehouse, count, "request", numDays);
}


// Processes end of file.
void transaction_parser::process_end()
{
  reachedEnd = true;
}

unordered_map<string, warehouse> & transaction_parser::get_warehouses() {
 return warehouses;
}

unordered_map<string, food_item> & transaction_parser::get_food_items() {
 return foodItems;
}
