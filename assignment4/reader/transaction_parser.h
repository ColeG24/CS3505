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
#include <sstream>

#ifndef TRANSACTION_PARSER_H
#define TRANSACTION_PARSER_H

class transaction_parser
{
  private:
    // Vector of requests and recieves for each index(day).
    std::vector <std::vector<transaction>> transactions;

    // Maps name of warehouse to that warehouse.
    std::unordered_map <std::string, warehouse> warehouses;

    // Maps upc code to that food_item.
    std::unordered_map<std::string, food_item> foodItems;
   
    bool reachedEnd;
    int numDays;
    int startDate;
    file_data data;

    // Helper methods for processing each possible line.
    void process_line(std::string line);
    void process_food_item(std::istringstream & iss);
    void process_warehouse(std::istringstream & iss);
    void process_start_date();
    void process_receive(std::istringstream & iss);
    void process_request(std::istringstream & iss);
    void process_next();
    void process_end();

  public:
    // Constructor
    transaction_parser(std::string filename);
    
    // Accessor
    file_data get_file_data() const;
};

#endif
