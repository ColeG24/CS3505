#include <string>

#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H

class food_item 
{
  private:
    std::string upc;
    int shelfLife;
    std::string name;

  public:
    food_item(std::string name, std::string upc, int shelfLife);

    food_item ();

    std::string get_upc() const;
    
    std::string get_name() const;

    int get_shelf_life() const;
};

#endif
