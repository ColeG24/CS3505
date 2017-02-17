#include "reader/transaction_parser.h"
#include "reader/file_data.h"
#include "reader/transaction.h"
#include "processor/food_item.h"
#include "processor/warehouse.h"
#include "processor/processor.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
  if (argc != 2) 
  {
    cout << "Wrong number of arguments" << endl;
    return 0;
  }

  string filename = argv[1];
  transaction_parser parser(filename);

  file_data data = parser.get_file_data();

  processor process (data);

  vector<food_item> wellStockedFood = process.get_wellstocked_food();

  vector<food_item> unstockedFood = process.get_unstocked_food();

  cout << "All Well Stocked Food." << endl;
  for (int i = 0; i < wellStockedFood.size(); i++)
    cout << wellStockedFood[i].get_upc() << endl;

  cout << "All UNSTOCKED FOOD. " << endl;
  for (int i = 0; i < unstockedFood.size(); i++)
    cout << unstockedFood[i].get_upc() << endl;

  return 0;
}
