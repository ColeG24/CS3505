#include "../reader/file_data.h"
#include <vector>
#include "food_item.h"
#include "warehouse.h"
#include <unordered_map>

class processor
{
 private:
  file_data data;
  // Maps all requests upc codes to quantity.
  std::unordered_map<std::string, int> quantityMap;
  // Vector of top 3 products.
  std::vector<food_item> top3;
  
  std::vector<warehouse> warehouses;

  void preprocess();
  
  void initialize();

  void removeExpiredFood(int day);

 public:
  processor(file_data data);
  std::vector<food_item> get_unstocked_products();
  std::vector<food_item> get_wellstocked_products();
  std::vector<food_item> get_top3_products();
};
