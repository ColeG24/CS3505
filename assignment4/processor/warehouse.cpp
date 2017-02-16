#include <vector>
#include <unordered_map>
#include "warehouse.h"
#include "inventory_item.h"
#include <string>
#include "queue"

using namespace std:

warehouse::warehouse(string name) :
  name(name)
{}

vector<string> warehouse::get_upc_codes() 
{
  // not implementing yet, because not sure if we need this functionality
}

void warehouse::request(food_item foodItem, int count) 
{

}

/*
 * Expects to recieve food in order
 */
void warehouse::receive(food_item foodItem, int count, int currDate)

  inventory_item item (foodItem, count, currDate);

  // Add to inventory map
  if (inventoryMap.find(foodItem.get_upc() != inventoryMap.end()))
  {
    // Add item to queue
    inventoryMap[foodItem.get_upc()].push_back(item);
  }
  else 
  {
    // Create new queue and add to inventory map
    queue<inventory_item> inventoryItems;
    inventoryItems.push(item);
    inventoryMap.emplace(foodItem.get_upc(), inventoryItems);
  }

  // Add to expiration date map  
  if (expirationDateMap.find(item.get_expiration_date()) != inventoryMap.end())
  {
    // Add item to list
    expirationDateMap[foodItem.get_upc()].push_back(item);
  }
  else 
  {
    // Create new vector and add item, then add to expiration map
    vector<inventory_item> inventoryItems;
    inventoryItems.push_back(item);
    expirationDateMap.emplace(foodItem.get_upc(), inventoryItems);
  }
}

/*
 * Removes all items that expire on the passed in date
 */
void remove_at_expiration_date(const int expirationDate) 
{
  if (expirationDateMap.find(expirationDate) != expirationDateMap.end())
  {
    vector<inventory_items> expiredItems = expirationDateMap[expirationDate];
    for (int i = 0; i < expiredItems.size(); i++) // For each expired item
    {
      inventory_item expiredItem = expiredItems[i];
      // delete this from inventory map
      queue canidates = inventory_map[expiredItem.get_upc()];
      // Remove all candidates with expired date
      while (candidates.front().get_expiration_date() == expirationDate)
      {
        candidates.pop();
      }
    }
    // Erase expired items
    expirationDateMap.erase(expirationDate);
  }
  // Else nothing expired and nothing to remove
}

