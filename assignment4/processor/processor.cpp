#include "processor.h"
#include <vector>
#include "food_item.h"
#include "../reader/transaction.h"
#include "../reader/file_data.h"
#include <iostream>

using namespace std;

processor::processor(file_data data):
  data(data)
{
  initialize();
  preprocess();
}

void processor::preprocess()
{
  cout << "Entered preprocess.. " << endl;
  for (int i = 0; i < data.numDays; i++)
  {
    cout << "Start outer loop" << endl;

    removeExpiredFood(i);

    cout << "Removed expired food.. " << endl;
    vector<transaction> transactionsForDay = data.transactions[i];

    for (int j = 0; j < transactionsForDay.size(); j++)
    {
      cout << "Start inner loop.." << endl;
      cout << "Get transaction.. " << endl;
      transaction & trans = transactionsForDay[j];

      cout << "Get food.. " << endl;
      food_item & foodItem = data.foodItems[trans.get_upc()];

      cout << "Get warehouse.." << endl;
      warehouse & currWarehouse = data.warehouses[trans.get_warehouse_name()]; 

      cout << "process transaction.. " << endl;
      currWarehouse.process_transaction(trans, foodItem);

      cout << "End of inner loop.." << endl;
    }
    cout << "End of outer loop.." << endl;
  }
}

void processor::initialize()
{
  warehouses.reserve(data.warehouses.size());
  for (auto kv : data.warehouses)
  {
    warehouses.push_back(kv.second);
  }
}

void processor::removeExpiredFood(int day)
{
  for (int i = 0; i < warehouses.size(); i++)
  {
    warehouses[i].remove_at_expiration_date(day);
  }
}
