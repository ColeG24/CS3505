/*
 * AUTHORS: Cole Gordon & Philipp Hojnacki
 *
 *  The main entry of the program. 
 */

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

  // Get, parse, and process the file.

  string filename = argv[1];
  transaction_parser parser(filename);
  file_data data = parser.get_file_data();
  processor process (data);

  // Retrieve report data.
  
  vector<food_item> wellStockedFood = process.get_wellstocked_food();

  vector<food_item> unstockedFood = process.get_unstocked_food();

  vector <food_item> top3 = process.get_top3_products();


  //**************GENERATE REPORT**************************

  cout << "Report by Cole Gordon & Philipp Hojnacki. " << endl;

  cout << endl << "Unstocked Products: " << endl;
  for (int i = 0; i < unstockedFood.size(); i++)
  {
    cout << unstockedFood[i].get_upc() << " " << unstockedFood[i].get_name() << endl;
  }

  cout << endl << "Well-Stocked Products: " << endl;
  for (int i = 0; i < wellStockedFood.size(); i++)
  {
    cout << wellStockedFood[i].get_upc() << " " << wellStockedFood[i].get_name() << endl;
  }

  cout << endl << "Most Popular Products: " << endl;
  for (int i = 0; i < top3.size(); i++)
  {
    cout << top3[i].get_upc() << " " << top3[i].get_name() << endl;
  }

  cout << endl;

  // Report generated, return.

  return 0;
}
