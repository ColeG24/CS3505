#include "../reader/file_data.h"
#include <vector>
#include "food_item.h"
#include <unordered_map>

class processor
{
 private:
  file_data data;
  // Maps all requests upc codes to quantity.
  std::unordered_map<std::string, int count> quantityMap;
  // Vector of top 3 products.
  std::vector<food_item> top3;

  void preprocess();

 public:
  processor(file_data data);
  vector<food_item> get_unstocked_products();
  vector<food_item> get_wellstocked_products();
  vector<food_item> get_top3_products();
}
