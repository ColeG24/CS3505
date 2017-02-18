/*
 * Class to represent food items, which contain infomraiton about its upc, name and shelflife
 */

#include <string>
#include "food_item.h"

using namespace std;

food_item::food_item(string name, string upc, int shelfLife) :
  upc(upc), name(name), shelfLife(shelfLife)
{}

food_item::food_item () :
  upc(""), name(""), shelfLife(0)
{}

string food_item::get_upc() const
{
  return upc; 
} 

string food_item::get_name() const
{
  return name;
}

int food_item::get_shelf_life() const
{
  return shelfLife;
}
