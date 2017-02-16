#include "food_item.h"
#include "inventory_item.h"

using namespace std;

inventory_item::inventory_item(const food_item & foodItem, int count, int currDate) :
  count(count), foodItem(foodItem)
{
  // Calculate expiration date from food item and current date
}

int inventory_item::get_count() 
{
  return count;
}

int get_expiration_date() 
{
  return expirationDate;
}

