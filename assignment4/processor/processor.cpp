/*
 * This classed is used to process a file_data. Passing the file_data object into the constructor automatically processes the data. 
 * Use the accessors to get the processed information
 */

#include "processor.h"
#include <vector>
#include "food_item.h"
#include "../reader/transaction.h"
#include "../reader/file_data.h"
#include <iostream>

using namespace std;

/*
 * Creates a new processor, which processes the passed in file data
 */
processor::processor(file_data & data):
  data(data)
{
  initialize();
  preprocess();
  compute_unstocked_and_wellstocked_products();
  compute_top_3_products();
}

/*
 * Runs the transactions against the warehouses, and handles all food expiration
 */
void processor::preprocess()
{

  for (int i = 0; i <= data.numDays; i++)
  {
    removeExpiredFood(i);

    vector<transaction> & transactionsForDay = data.transactions[i];

    for (int j = 0; j < transactionsForDay.size(); j++)
    {
      transaction & trans = transactionsForDay[j];

      food_item & foodItem = data.foodItems[trans.get_upc()];

      warehouse & currWarehouse = data.warehouses[trans.get_warehouse_name()]; 

      currWarehouse.process_transaction(trans, foodItem);
    }
  }
}

/*
 * Initializes the member variables of processor using the data from file_data
 */ 
void processor::initialize()
{
  warehouseNames.reserve(data.warehouses.size());
  for (auto kv : data.warehouses)
  {
    warehouseNames.push_back(kv.first);
  }

  allFood.reserve(data.foodItems.size());
  for (auto kv : data.foodItems)
  {
    allFood.push_back(kv.second);
  }
}

/*
 * Removes the expired food from all warehouses for that day
 */
void processor::removeExpiredFood(int day)
{
  for (int i = 0; i < warehouseNames.size(); i++)
  {
    data.warehouses[warehouseNames[i]].remove_at_expiration_date(day);
  }
}

/*
 * Computes both the unstocked products and well stocked products.
 */
void processor::compute_unstocked_and_wellstocked_products()
{
  unordered_set<string> allFoodNotSeen;
  unordered_map<string, int> upcToQuantity;

  // Initialize all Food not seen to all food seen.
  for (int i = 0; i < allFood.size(); i++)
  {
    food_item currFood = allFood[i];
    allFoodNotSeen.insert(currFood.get_upc());
  }

  for (int i = 0; i < warehouseNames.size(); i++)
  {
    unordered_set<string> warehouseUPCS;
    vector<string>  warehouseFoods = data.warehouses[warehouseNames[i]].get_upc_codes();
    for (int j = 0; j < warehouseFoods.size(); j++)
    {
      string currupc = warehouseFoods[j];
      if (warehouseUPCS.find(currupc) != warehouseUPCS.end())
      {
	      continue;
      }
      warehouseUPCS.insert(currupc);
      if (allFoodNotSeen.find(currupc) != allFoodNotSeen.end()) // Found current upc_code.
      {
	      allFoodNotSeen.erase(currupc);
	      upcToQuantity.emplace(currupc, 1);
      }
      else
      {
	      upcToQuantity[currupc]++;
	      if (upcToQuantity[currupc] == 2)
        {
	        wellStockedFood.push_back(data.foodItems[currupc]);
        }
      }
    }
  }
  for (const auto& elem: allFoodNotSeen)
  {
    unstockedFood.push_back(data.foodItems[elem]);
  }
}

/*
 * Returns a vector oup to the top 3 products
 */
vector<food_item> processor::get_top3_products()
{
  return top3;
}

/*
 * Returns a vector of all the well stocked food. Well stocked food is food items that are in
 * multiple warehouses by the end of the simulation
 */
vector<food_item> processor::get_wellstocked_food()
{
  return wellStockedFood;
}

/*
 * Returns all food that is not found in any warehouses
 */
vector<food_item> processor::get_unstocked_food()
{
  return unstockedFood;
}

/*
 * Computes the top 3 products and stores into top3 vector
 */
void processor::compute_top_3_products() 
{
  unordered_map<string, int> requestToQuantityMap;
  for (int i = 0; i < data.transactions.size(); i++) 
  {
    vector<transaction> & transForDay = data.transactions[i];
    for (int j = 0; j < transForDay.size(); j++)
    { 
      transaction & trans = transForDay[j];
      if (trans.get_type() != "request") // Process only requests
      {
        continue;
      }

      if (requestToQuantityMap.find(trans.get_upc()) != requestToQuantityMap.end())
      {
        requestToQuantityMap[trans.get_upc()] += trans.get_count();
      }
      else 
      {
        requestToQuantityMap.emplace(trans.get_upc(), trans.get_count());
      }
    }  
  }
  vector<int> largestQuantities;
  largestQuantities.reserve(3);
  vector <string> correspondingUPC;
  correspondingUPC.reserve(3);
  top3.reserve(3);

  int largestQuantity = 0;
  for (int i = 0; i < 3; i++) 
  {
    if (requestToQuantityMap.size() == 0)
    {
      break;
    }

    largestQuantities.push_back(-1);
    correspondingUPC.push_back("");

    for (auto kv : requestToQuantityMap)
    {
      if (kv.second > largestQuantities[i]) 
      {
        largestQuantities[i] = kv.second;
        correspondingUPC[i] = kv.first;
      }
    }
    requestToQuantityMap.erase(correspondingUPC[i]);
    top3.push_back(data.foodItems[correspondingUPC[i]]);
  }
}

