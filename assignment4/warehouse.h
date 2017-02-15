#include <string>
#include <vector>
#include <unordered_map>
#include "inventory_item.h"

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class warehouse 
{
  private:
    std::string name;
    std::unordered_map<std::string, inventory_item> inventoryMap;

  public:
    warehouse(std::string name);
    
    std::vector<std::string> get_upc_codes();

    void request(food_item foodItem, int count);

    void receive(food_item foodItem, int count, boost::gregorian::date curr_date);

};

#endif
