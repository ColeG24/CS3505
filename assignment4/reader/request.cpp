#include <string>
#include "request.h"

using namespace std;

request::request(string upc, string warehouseName, int count) :
 upc(upc), warehouseName(warehouseName), count(count)
{}

string request::get_upc() 
{
  return upc;
}

string request::get_warehouse_name()
{
  return warehouseName;
}

int request::get_count() 
{
  return count;
}
