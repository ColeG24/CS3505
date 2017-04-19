/*
 * AUTHORS: Cole Gordon & Philipp Hojnackie
 */
/*
 *  Parses the transaction data into easily readable data.
 */

#include <string>
#include <unordered_map>
#include <vector>
#include "../processor/food_item.h"
#include "../processor/warehouse.h"
#include "transaction.h"
#include "file_data.h"
#include <fstream>
#include <sstream>

#ifndef TRANSACTION_PARSER_H
#define TRANSACTION_PARSER_H

class transaction_parser
{
  private:
    // Maps name of warehouse to that warehouse.
    std::unordered_map <std::string, warehouse> & warehouses;

    // Maps upc code to that food_item.
    std::unordered_map<std::string, food_item> & foodItems;
   
    bool reachedEnd;
    int numDays;
    int startDate;
    file_data data;
    std::ifstream & file;
    
    // Helper methods for processing each possible line.
    bool process_header(std::string & line);
    void process_line(std::string & line);
    void process_food_item(std::istringstream & iss);
    void process_warehouse(std::istringstream & iss);
    void process_start_date();
    transaction & process_receive(std::istringstream & iss);
    transaction & process_request(std::istringstream & iss);
    void process_end();

  public:
    // Constructor
    transaction_parser(std::string filename);
    std::unordered_map <std::string, warehouse> & get_warehouses();
    std::unordered_map<std::string, food_item> & get_food_items();
    transaction * next_item(); 
   };

#endif
