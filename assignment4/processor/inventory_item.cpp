#include "food_item.h"
#include "inventory_item.h"

using namespace std;

inventory_item::inventory_item(const food_item & foodItem, int quantity, int currDate) :
  quantity(quantity), foodItem(foodItem)
{
  // Calculate expiration date from food item and current date
}

int inventory_item::get_quantity() 
{
  return quantity;
}

int inventory_item:: get_expiration_date() 
{
  return expirationDate;
}

