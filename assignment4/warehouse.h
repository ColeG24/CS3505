#include <string.h>
#include <unordered_map>

class warehouse 
{
  private:
    string name;
    std::unordered_map<std::string, inventory_item>;

  public:
    warehouse(std::string);
    
    get_upc_codes();

    request(food_item, int count);

    receive(food_item, int count);

}
