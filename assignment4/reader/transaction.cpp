#include <string>
#include "transaction.h"

using namespace std;

transaction::transaction(string upc, string warehouseName, int count, string type) :
  upc(upc), warehouseName(warehouseName), count(count), type(type)
{}

string transaction::get_upc() 
{
  return upc;
}

string transaction::get_warehouse_name()
{
  return warehouseName;
}

int transaction::get_count() 
{
  return count;
}

string transaction::get_type()
{
  return type;
}
