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

    std::string get_upc();

    std::string get_name();

    int get_shelf_life();
};

#endif
