#include "food_item.h" 

#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

class inventory_item 
{
  private:
    int count;
    food_item foodItem;
    int expirationDate;

  public:
    inventory_item(const food_item & foodItem, int count, int currDate);
    
    int get_count();

    int get_expiration_date();
 
};

#endif
