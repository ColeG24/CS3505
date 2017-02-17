#include "processor.h"
#include <vector>
#include "food_item.h"
#include "../reader/transaction.h"
#include "../reader/file_data.h"
#include <iostream>

using namespace std;

processor::processor(file_data & data):
  data(data)
{
  initialize();
  preprocess();
  cout << "tihr" << endl;
  compute_unstocked_and_wellstocked_products();
  cout << "Here" << endl;
  compute_top_3_products();
}

void processor::preprocess()
{

  for (int i = 0; i <= data.numDays; i++)
  {
    removeExpiredFood(i);

    vector<transaction> transactionsForDay = data.transactions[i];

    for (int j = 0; j < transactionsForDay.size(); j++)
    {
      transaction & trans = transactionsForDay[j];

      food_item & foodItem = data.foodItems[trans.get_upc()];

      warehouse & currWarehouse = data.warehouses[trans.get_warehouse_name()]; 

      currWarehouse.process_transaction(trans, foodItem);
    }
  }
}

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

void processor::removeExpiredFood(int day)
{
  for (int i = 0; i < warehouseNames.size(); i++)
  {
    data.warehouses[warehouseNames[i]].remove_at_expiration_date(day);
  }
}

void processor::compute_unstocked_and_wellstocked_products()
{
  unordered_set<string> allFoodNotSeen;
  unordered_map<string, int> upcToQuantity;
  // Initialize all Food not seen to all food seen.
  for (int i = 0; i < allFood.size(); i++)
  {
    food_item & currFood = allFood[i];
    allFoodNotSeen.insert(currFood.get_upc());
  }
  for (int i = 0; i < warehouseNames.size(); i++)
  {
    unordered_set<string> warehouseUPCS;
    vector<string> * warehouseFoods = data.warehouses[warehouseNames[i]].get_upc_codes();
    cout << "1" << endl;
    for (int j = 0; j < warehouseFoods->size(); j++)
    {
      cout << "2" << endl;
      string currupc = (*warehouseFoods)[j];
      if (warehouseUPCS.find(currupc) != warehouseUPCS.end())
      {
	      continue;
      }
      cout << "3" << endl;
      warehouseUPCS.insert(currupc);
      if (allFoodNotSeen.find(currupc) != allFoodNotSeen.end()) // Found current upc_code.
      {
	      allFoodNotSeen.erase(currupc);
       	upcToQuantity.emplace(currupc, 1);
      }
      else
      {
	      upcToQuantity[currupc]++;
	      // If # of times we saw a upc = # of warehouses, then it is well stocked. 
	      if (upcToQuantity[currupc] == 2)
        {
	        wellStockedFood.push_back(data.foodItems[currupc]);
        }
      }
      delete warehouseFoods;
    }
  }
  for (const auto& elem: allFoodNotSeen)
  {
    unstockedFood.push_back(data.foodItems[elem]);
  }
}

void processor::compute_top_3_products() 
{
  cout << "top 3" << endl;
  unordered_map<string, int> requestToQuantityMap;
  for (int i = 0; i < data.transactions.size(); i++) 
  {
    cout << "l begin" << endl;
    vector<transaction> & transForDay = data.transactions[i];
    cout << "b" << endl;
    for (int j = 0; j < transForDay.size(); j++)
    { 
      transaction & trans = transForDay[j];
      cout << trans.get_type() << endl;
      if (trans.get_type() != "request") // Process only requests
      {
        continue;
      }

      if (requestToQuantityMap.find(trans.get_upc()) != requestToQuantityMap.end())
      {
        cout << "found " << endl;
        requestToQuantityMap[trans.get_upc()] += trans.get_count();
      }
      else 
      {
        cout << "new " << endl;
        requestToQuantityMap.emplace(trans.get_upc(), trans.get_count());
      }
    }  
  }
  cout << "c" <<endl;
  vector<int> largestQuantities;
  largestQuantities.reserve(3);
  vector <string> correspondingUPC;
  correspondingUPC.reserve(3);
  top3.reserve(3);

  cout << "d" << endl;
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
  cout << "--------------" << endl;
  cout << top3.size() << endl;
  cout << largestQuantities.size() << endl;
}

vector<food_item> processor::get_top3_products()
{
  return top3;
}

vector<food_item> processor::get_wellstocked_food()
{
  return wellStockedFood;
}

vector<food_item> processor::get_unstocked_food()
{
  return unstockedFood;
}
