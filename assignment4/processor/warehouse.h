/*
 * AUTHORS: Cole Gordon & Philipp Hojnacki
 */
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "inventory_item.h"
#include "../reader/transaction.h"


#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class warehouse 
{
  private:
    std::string & name;
    std::unordered_map<std::string, std::queue<inventory_item>> & inventoryMap; // Maps upc code to vector of inventory items by time we added
    std::unordered_map<std::string, std::unordered_map<std::string, inventory_item>> & expirationDateMap; // Maps expiration date to all inventory items that share expiration date. 

    void request(food_item & foodItem, int count);

    void receive(food_item & foodItem, int count, const int date);

  public:
    warehouse(std::string name);
    
    warehouse();

    std::vector<std::string> get_upc_codes() const;
    
    void remove_at_expiration_date(const int expirationDate); 
    
    void process_transaction(transaction & trans, food_item & foodItem);

    std::string get_name();
};

#endif
