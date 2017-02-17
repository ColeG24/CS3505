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

warehouse::warehouse(string name) :
  name(name)
{
  cout << "Called named constructor ------------------" << endl;
}

warehouse::warehouse () :
  name("")
{
  cout << "Called defult constructor ----" << endl;
}

string warehouse::get_name()
{
  return name;
}

vector<string> warehouse::get_upc_codes() const 
{
  vector<string> upcCodes;
  cout << "iM size " << inventoryMap.size() << endl;
  for (auto kv : inventoryMap)
  {
    upcCodes.push_back(kv.first);
  }
  return upcCodes;
}

void warehouse::process_transaction(transaction trans, food_item foodItem)
{
  cout << "Transac Process" << endl;
  if (trans.get_type() == "request")
  {
    request(foodItem, trans.get_count());
  }
  else 
  {
    receive(foodItem, trans.get_count(), trans.get_date());
  }
}

void warehouse::request(food_item foodItem, int count) 
{
  cout << "Request begin" << endl;
  int amountLeft = count;
  if (inventoryMap.find(foodItem.get_upc()) != inventoryMap.end())
  {
    cout << "a" << endl;
    // Add item to queue
    queue<inventory_item> & candidates = inventoryMap[foodItem.get_upc()];
    while (amountLeft > 0)
    {
      cout << "Amount Left: " << amountLeft << endl;
      
      inventory_item & currItem = candidates.front();
      if (currItem.get_quantity() > amountLeft) 
      {
        cout << "b" << endl;
        currItem.decrement_quantity(amountLeft);
        amountLeft = 0;
      }
      else
      {
        cout << "c" << endl;
        // We have to totally get rid of this inventory item
        amountLeft -= currItem.get_quantity();
        cout << "d" << endl;
        candidates.pop();
        cout << "e" << endl;
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
  cout << "End amount left " << amountLeft << endl;
  // Warehouse does not contain item so ignore request
}

/*
 * Expects to recieve food in order
 */
void warehouse::receive(food_item foodItem, int count, int currDate)
{
  cout << "Receive Begin" << endl;
  inventory_item item (foodItem, count, currDate);

  cout << item.get_expiration_date() << endl;
 
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
  else // WE don have this item in inventory
  {
    cout << "item not in inventory yet" << endl;
    // Create new queue and add to inventory map
    queue<inventory_item> inventoryItems;
    cout << "new que created" << endl;
    inventoryItems.push(item);
    cout << "pusged item" << endl;
    inventoryMap.emplace(foodItem.get_upc(), inventoryItems);
    cout << "emplaced" << endl;
  }

  cout << item.get_expiration_date() << endl;
  // Add to expiration date map  
  if (expirationDateMap.find("" + item.get_expiration_date()) != expirationDateMap.end())
  {
    cout << "e" << endl;
    // Add item to map
    expirationDateMap["" + item.get_expiration_date()].emplace(item.get_upc(), item);
  }
  else 
  {
    cout << "f" << endl;
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
  cout << "Expiration " << expirationDate << endl;
  if (expirationDateMap.find("" + expirationDate) != expirationDateMap.end()) // There is expired items
  {
    cout << "deleting" << endl;
    // TODO might be issue with key for expiredItemsMap not matching its values expiraation date
    unordered_map<string, inventory_item> expiredItemsMap = expirationDateMap["" + expirationDate];
    for (auto kv: expiredItemsMap) 
    {    
      inventory_item &  expiredItem = kv.second;
      cout << expiredItem.get_upc() << endl;
      cout << "eI date " << expiredItem.get_expiration_date() << endl;
      // delete this from inventory map
      queue<inventory_item> & candidates = inventoryMap[expiredItem.get_upc()];
      cout << "cand size " << candidates.size() << endl;
      // Remove all candidates with expired date
      cout << "cF date " << candidates.front().get_expiration_date() << endl;
      while (candidates.front().get_expiration_date() == expirationDate)
      {
        cout << "popping" << endl;
        candidates.pop();
      }
    }
    // Erase expired items
    expirationDateMap.erase("" + expirationDate);
  }
  // Else nothing expired and nothing to remove
}

