#include <string>
#include <unordered_map>
#include <vector>

#include "../processor/food_item.h"
#include "../processor/warehouse.h"

#include "request.h"
#include "receive.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <sstream>

#ifndef TRANSACTION_PARSER_H
#define TRANSACTION_PARSER_H

class transaction_parser
{
  private:
    std::unordered_map <std::string, std::vector<request>> requests;
    std::unordered_map <std::string, std::vector<receive>> receieves;
    std::unordered_map <std::string, warehouse> warehouses;
    std::vector<food_item> foodItems;
    bool reachedEnd;
    int numDays;
    boost::gregorian::date startDate;

    void process_line(std::string line);
    void process_food_item(std::istringstream & iss);
    void process_warehouse(std::istringstream & iss);
    void process_start_date(std::istringstream & iss);
    void process_receive(std::istringstream & iss);
    void process_request(std::istringstream & iss);
    void process_next();
    void process_end();

  public:
    transaction_parser(std::string filename);
   
    std::vector<request> get_requests(boost::gregorian::date startDate);

    std::vector<receive> get_receives(boost::gregorian::date startDate);

    void get_warehouse(std::string name);

    std::vector<food_item> get_food_items();

    boost::gregorian::date get_start_date();

    int get_number_of_days();

    void add_day();
};

#endif
