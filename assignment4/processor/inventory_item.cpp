#include "food_item.h"
#include "inventory_item.h"
#include <string>

using namespace std;

inventory_item::inventory_item(const food_item & foodItem, int quantity, int currDate) :
  quantity(quantity), foodItem(foodItem)
{
  // Calculate expiration date from food item and current date
  expirationDate = currDate + foodItem.get_shelf_life();
}

int inventory_item::get_quantity() 
{
  return quantity;
}

int inventory_item:: get_expiration_date() 
{
  return expirationDate;
}

string inventory_item::get_upc() 
{
  return foodItem.get_upc();
}

void inventory_item::decrement_quantity(int amount)
{
  quantity -= amount;
}

void inventory_item::increment_quantity(int amount)
{
  quantity += amount;
}
