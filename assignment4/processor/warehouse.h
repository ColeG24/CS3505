#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include "inventory_item.h"


#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class warehouse 
{
  private:
    std::string name;
    std::unordered_map<int, std::queue<inventory_item>> inventoryMap; // Maps upc code to vector of inventory items by time we added
    std::unordered_map<int, std::vector<inventory_item>> expirationDateMap; // Maps expiration date to all inventory items that share expiration date.  
  public:
    warehouse(std::string name);
    
    std::vector<std::string> get_upc_codes();

    void request(food_item foodItem, int count

    void receive(food_item foodItem, int count, const int date);
    
    void remove_at_expiration_date(const int expirationDate); 
};

#endif
