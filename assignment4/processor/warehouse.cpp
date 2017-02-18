/*
 * This class is used to represent a warehouse. Each warehouse has a name, and an inventory.
 * The inventory will store any food item and its quantity and expiration date.
 */

#include <vector>
#include <unordered_map>
#include "warehouse.h"
#include "inventory_item.h"
#include "../reader/transaction.h"
#include <string>
#include <queue>
#include <unordered_set>
#include <iostream>

using namespace std;

/*
 * Creates a new warehouse of name. Warehouses contain inventory items.
 */
warehouse::warehouse(string name) :
  name(name)
{
}

warehouse::warehouse () :
  name("")
{
}

string warehouse::get_name()
{
  return name;
}

/*
 * Returns all upc_codes of food_items in this warehouse
 */
vector<string> warehouse::get_upc_codes() const 
{
  vector<string> upcCodes;
  for (auto kv : inventoryMap)
  {
    upcCodes.push_back(kv.first);
  }
  return upcCodes;
}

/*
 * Processes the transaction, and the assosiated food item to the transaction.
 * Updates the warehouse depending on the transaction
 */
void warehouse::process_transaction(transaction & trans, food_item & foodItem)
{
  if (trans.get_type() == "request")
  {
    request(foodItem, trans.get_count());
  }
  else 
  {
    receive(foodItem, trans.get_count(), trans.get_date());
  }
}

/*
 * Processes the food item and count, as a request. The request will remove from
 * both the inventory map, and expiration date map. Request is not fully processed
 * if there is not enough in inventory
 */
void warehouse::request(food_item & foodItem, int count) 
{
  int amountLeft = count;
  if (inventoryMap.find(foodItem.get_upc()) != inventoryMap.end())
  {
    // Add item to queue
    queue<inventory_item> & candidates = inventoryMap[foodItem.get_upc()];
    while (amountLeft > 0)
    {
      inventory_item & currItem = candidates.front();
      if (currItem.get_quantity() > amountLeft) 
      {
        currItem.decrement_quantity(amountLeft);
        amountLeft = 0;
      }
      else
      {
        // We have to totally get rid of this inventory item
        amountLeft -= currItem.get_quantity();
        candidates.pop();

        // Now erase from expiration date
        expirationDateMap["" + currItem.get_expiration_date()].erase(currItem.get_upc());
      }
      if (candidates.size() == 0)
      {
        inventoryMap.erase(foodItem.get_upc());
        break;
      }
    }
    
  }
}

/*
 * Expects to recieve food in order. Processes the food item, given the count and current date
 * as a receive transaction. Adds to both inventory map, and expirationDateMap
 */
void warehouse::receive(food_item & foodItem, int count, int currDate)
{
  
  inventory_item item (foodItem, count, currDate);
  
  // Add to inventory map
  if (inventoryMap.find(foodItem.get_upc()) != inventoryMap.end()) // We have this item in inventory already
  {
    
    queue<inventory_item> & items = inventoryMap[foodItem.get_upc()];

    if (items.back().get_expiration_date() == item.get_expiration_date())
    {
      // Then we can just increment quantity and be done
      items.back().increment_quantity(count);
      return;
    }
    else
    {
      // This needs to be pushed on the queue
      items.push(item);
    }
  }
  else // We dont have this item in inventory
  {
    // Create new queue and add to inventory map
    queue<inventory_item> inventoryItems;
    inventoryItems.push(item);
    inventoryMap.emplace(foodItem.get_upc(), inventoryItems);
  }

  // Add to expiration date map  
  if (expirationDateMap.find("" + item.get_expiration_date()) != expirationDateMap.end())
  {
    // Add item to map
    expirationDateMap["" + item.get_expiration_date()].emplace(item.get_upc(), item);
  }
  else 
  {
    // Create new map and add item, then add to expiration map
    unordered_map<string, inventory_item> inventoryItems;
    inventoryItems.emplace(item.get_upc(), item);
    expirationDateMap.emplace("" + item.get_expiration_date(), inventoryItems);
  }    
}

/*
 * Removes all items that expire on the passed in date
 */
void warehouse::remove_at_expiration_date(const int expirationDate) 
{
  if (expirationDateMap.find("" + expirationDate) != expirationDateMap.end()) // There is expired items
  {
    unordered_map<string, inventory_item> expiredItemsMap = expirationDateMap["" + expirationDate];
    for (auto kv: expiredItemsMap) 
    {    
      inventory_item &  expiredItem = kv.second;
      // delete this from inventory map
      queue<inventory_item> & candidates = inventoryMap[expiredItem.get_upc()];
      // Remove all candidates with expired date
      while (candidates.front().get_expiration_date() == expirationDate)
      {
        candidates.pop();
      }
      // If all inventory items with upc code are removed/expired. Delete that  entry in inventory map.
      if (candidates.size() == 0)
      {
	      inventoryMap.erase(expiredItem.get_upc());
      }
    }
    // Erase expired items
    expirationDateMap.erase("" + expirationDate);
  }
  // Else nothing expired and nothing to remove
}

