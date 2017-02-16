#include <boost/date_time/gregorian/gregorian.hpp>
#include "food_item.h"
#include "inventory_item.h"

using namespace std;
using namespace boost::date;

inventory_item::inventory_item(const food_item & foodItem, int count, const date currDate) :
  count(count), foodItem(foodItem)
{
  // Calculate expiration date from food item and current date
}

int inventory_item::get_count() 
{
  return count;
}

date get_expiration_date() 
{
  return expirationDate;
}

