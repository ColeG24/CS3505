#include <boost/date_time/gregorian/gregorian.hpp>
#include "food_item.h" 

#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

class inventory_item 
{
  private:
    int count;
    food_item foodItem;
    boost::gregorian::date expirationDate;

  public:
    inventory_item(const food_item & foodItem, int count, const boost::gregorian::date & currDate);
    
    int get_count();

    boost::gregorian::date get_expiration_date();
 
};

#endif
