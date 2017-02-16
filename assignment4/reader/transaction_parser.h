#include <string>
#include <unordered_map>
#include <vector>

#include "../processor/food_item.h"
#include "../processor/warehouse.h"

#include "request.h"
#include "receive.h"

#include <sstream>

#ifndef TRANSACTION_PARSER_H
#define TRANSACTION_PARSER_H

class transaction_parser
{
  private:
    // Maps the date to the requests and recieves of that date.
    std::vector <std::vector<request>> requests; 
    std::vector <std::vector<receive>> receives;

    // Maps name of warehouse to that warehouse.
    std::unordered_map <std::string, warehouse> warehouses;
    // Maps upc code to that food_item.
    std::unordered_map<std::string, food_item> foodItems;
   
    bool reachedEnd;
    int numDays;
    int startDate;

    void process_line(std::string line);
    void process_food_item(std::istringstream & iss);
    void process_warehouse(std::istringstream & iss);
    void process_start_date();
    void process_receive(std::istringstream & iss);
    void process_request(std::istringstream & iss);
    void process_next();
    void process_end();

  public:
    transaction_parser(std::string filename);
   
    std::vector<std::vector<request>> get_requests_map();

    std::vector<std::vector<receive>> get_receives_map();

    std::unordered_map<std::string, warehouse> get_warehouse_map();

    std::unordered_map<std::string, food_item> get_food_items_map();;

    int get_number_of_days();

    void add_day();
};

#endif
