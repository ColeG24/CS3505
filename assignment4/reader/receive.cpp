#include <string>

using namespace std;

receive::receive(string upc, string warehouseName, int count) :
 upc(upc), warehouseName(warehouseName), count(count)
{}

string receive::get_upc() 
{
  return upc;
}

string receive::get_warehouse_name()
{
  return warehouseName;
}

int receive::get_count() 
{
  return count;
}
