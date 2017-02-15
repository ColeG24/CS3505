#include <string.h>
#include <unordered_map>
#include "food_item.h"
#include "warehouse.h"
#include "request.h"
#include "receive.h"
#include <boost/date_time/gregorian/gregorian.hpp>

class transaction_parser
{
  private:
    undordered_map<std::string date, std::vector<request>> requests;
    undordered_map<std::string date, std::vector<receive>> receieves;
    std::vector<food_item> foodItems;
    std::vector<warehouse> warehouses;
    int numDays;
    date startDate;
  
  public:
    transaction_parser(string filename);
   
    std::vector<request> get_requests(date startDate);

    std::vector<receive> get_receives(date startDate);

    std::vector<food_item> get_food_items();

    std::vector<warehouse> get_warehouses();

    date get_start_date();

    int get_number_of_days();
};
