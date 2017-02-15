#include 

class inventory_item 
{
  private:
    int count;
    food_item foodItem;
    date expirationDate;

  public:
    inventory_item(const food_item, int count, date currDate);
    
    int get_count();

    date get_expiration_date();
 
};
