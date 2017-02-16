#include <vector>
#include <unordered_map>
#include "warehouse.h"
#include "inventory_item.h"
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"


using namespace std:
using namespace boost::gregorian;

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

void warehouse::receive(food_item foodItem, int count, date currDate)

  inventory_item item (foodItem, count);
  if (inventoryMap.find(foodItem.get_upc() != inventoryMap.end()))
  {
    // Add item to list
    inventoryMap[foodItem.get_upc()].push_back(item);
  }
  else 
  {
    vector<inventory_item> inventoryItems;
    inventoryItems.push_back(item);
    inventoryMap.emplace(foodItem.get_upc(), inventoryItems);
  }
}

void remove_at_expiration_date(const date expirationDate) 
{
  string dateAsString = to_simple_string(expirationDate);
  if (expirationDateMap.find(dateAsString) != expirationDateMap.end())
  {
    vector<inventory_items> expiredItems = expirationDateMap[dateAsString];
    for (int i = 0; i < expiredItems.size(); i++) // For each expired item
    {
      inventory_item expiredItem = expiredItems[i];
      // delete this from inventory map
    }
  }
  // Else nothing expired and nothing to remove
}

