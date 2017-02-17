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

  return 0;
}
