#include <vector>
#include <unordered_map>
#include "warehouse.h"
#include "inventory_item.h"
#include <string>
#include <queue>

using namespace std;

warehouse::warehouse(string name) :
  name(name)
{}

vector<string> warehouse::get_upc_codes() 
{
  // not implementing yet, because not sure if we need this functionality
}

void warehouse::request(food_item foodItem, int count) 
{
  int amountLeft = count;
  if (inventoryMap.find(foodItem.get_upc()) != inventoryMap.end())
  {
    // Add item to queue
    queue<inventory_item> candidates = inventoryMap[foodItem.get_upc()];
    while (amountLeft > 0)
    {
      inventory_item currItem = candidates.front();
      if (currItem.get_quantity() > amountLeft) 
      {
        currItem.decrement_quantity(amountLeft);
        amountLeft = 0;
      }
      else
      {
        amountLeft -= currItem.get_quantity();
        candidates.pop();
        // TODO remove from expiration date map
      }
    }
    
  }
  // Warehouse does not contain item so ignore request
}

/*
 * Expects to recieve food in order
 */
void warehouse::receive(food_item foodItem, int count, int currDate)
{
  // TODO when adding to queue check if there is already a inventory item with same expiration date in back, if there is, just add to it instead of making two entries.
  inventory_item item (foodItem, count, currDate);

  // Add to inventory map
  if (inventoryMap.find(foodItem.get_upc()) != inventoryMap.end())
  {
    // Add item to queue
    inventoryMap[foodItem.get_upc()].push(item);
  }
  else 
  {
    // Create new queue and add to inventory map
    queue<inventory_item> inventoryItems;
    inventoryItems.push(item);
    inventoryMap.emplace(foodItem.get_upc(), inventoryItems);
  }

  // Add to expiration date map  
  if (expirationDateMap.find("" + item.get_expiration_date()) != expirationDateMap.end())
  {
    // Add item to list
    expirationDateMap["" + item.get_expiration_date()].push_back(item);
  }
  else 
  {
    // Create new vector and add item, then add to expiration map
    vector<inventory_item> inventoryItems;
    inventoryItems.push_back(item);
    expirationDateMap.emplace("" + foodItem.get_upc(), inventoryItems);
  }
}

/*
 * Removes all items that expire on the passed in date
 */
void warehouse::remove_at_expiration_date(const int expirationDate) 
{
  if (expirationDateMap.find("" + expirationDate) != expirationDateMap.end())
  {
    vector<inventory_item> expiredItems = expirationDateMap["" + expirationDate];
    for (int i = 0; i < expiredItems.size(); i++) // For each expired item
    {
      inventory_item expiredItem = expiredItems[i];
      // delete this from inventory map
      queue<inventory_item> candidates = inventoryMap[expiredItem.get_upc()];
      // Remove all candidates with expired date
      while (candidates.front().get_expiration_date() == expirationDate)
      {
        candidates.pop();
      }
    }
    // Erase expired items
    expirationDateMap.erase("" + expirationDate);
  }
  // Else nothing expired and nothing to remove
}

