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
  compute_unstocked_and_wellstocked_products();
}

void processor::preprocess()
{

  for (int i = 0; i <= data.numDays; i++)
  {
    removeExpiredFood(i);

    vector<transaction> transactionsForDay = data.transactions[i];

    cout << "tfd size " << transactionsForDay.size() << endl;
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
    cout << kv.first << endl;
    warehouseNames.push_back(kv.first);
  }

  allFood.reserve(data.foodItems.size());
  for (auto kv : data.foodItems)
  {
    cout << kv.second.get_name() << endl;
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
    food_item currFood = allFood[i];
    allFoodNotSeen.insert(currFood.get_upc());
  }

  cout << "All food Initialized." << endl;

  for (int i = 0; i < warehouseNames.size(); i++)
  {
    unordered_set<string> warehouseUPCS;
    vector<string>  warehouseFoods = data.warehouses[warehouseNames[i]].get_upc_codes();
    cout << "Warehouse: " << i << endl;
    cout << "whf size " << warehouseFoods.size() << endl;
    for (int j = 0; j < warehouseFoods.size(); j++)
    {
      cout << "Food: " << j << endl;
      cout << "size: " << warehouseFoods.size() << endl;
      string currupc = warehouseFoods[j];
      if (warehouseUPCS.find(currupc) != warehouseUPCS.end())
      {
	continue;
      }
      warehouseUPCS.insert(currupc);
      if (allFoodNotSeen.find(currupc) != allFoodNotSeen.end())
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

  cout << "All warehouses processed" << endl;
  for (const auto& elem: allFoodNotSeen)
  {
    unstockedFood.push_back(data.foodItems[elem]);
  }
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
