#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include "inventory_item.h"
#include "boost/date_time/gregorian/gregorian.hpp"


#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class warehouse 
{
  private:
    std::string name;
    std::unordered_map<std::string, queue<inventory_item>> inventoryMap; // Maps upc code to vector of inventory items by time we added
    std::unordered_map<std::string, vector<inventory_item>>; expirationDateMap; // Maps expiration date to all inventory items that share expiration date.  
  public:
    warehouse(std::string name);
    
    std::vector<std::string> get_upc_codes();

    void request(food_item foodItem, int count);

    void receive(food_item foodItem, int count, const boost::gregorian::date curr_date);
    
    void remove_at_expiration_date(const boost::gregorian::date expirationDate); 
};

#endif
