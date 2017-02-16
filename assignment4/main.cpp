#include "reader/transaction_parser.h"
#include <string.h>
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
  
  return 0;
}
