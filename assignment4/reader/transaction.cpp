#include <string>
#include "transaction.h"

using namespace std;

transaction::transaction(string upc, string warehouseName, int count, string type, int date) :
  upc(upc), warehouseName(warehouseName), count(count), type(type), date(date)
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

int transaction::get_date()
{
  return date;
}
