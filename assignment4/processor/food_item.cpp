#include <string>
#include "food_item.h"

using namespace std;

food_item::food_item(string name, string upc, int shelfLife) :
  upc(upc), name(name), shelfLife(shelfLife)
{}

string food_item::get_upc() const;
{
  return upc; 
} 

string food_item::get_name()
{
  return name;
}

int food_item::get_shelf_life()
{
  return shelfLife;
}
