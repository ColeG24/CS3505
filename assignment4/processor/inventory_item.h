#include "food_item.h" 

#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

class inventory_item 
{
  private:
    int quantity;
    food_item foodItem;
    int expirationDate;

  public:
    inventory_item(const food_item & foodItem, int quantity, int currDate);
    
    int get_quantity();

    int get_expiration_date();

    int decrement_quantity(int amount);
 
};

#endif
