/*
 * AUTHORS: Cole Gordon & Philipp Hojnacki
 */
#include "../reader/file_data.h"
#include <vector>
#include "food_item.h"
#include "warehouse.h"
#include <unordered_map>

class processor
{
 private:
  file_data data;
  
  std::vector<food_item> allFood;
  std::vector<food_item> wellStockedFood;
  std::vector<food_item> unstockedFood;

  // Maps all requests upc codes to quantity.
  std::unordered_map<std::string, int> quantityMap;
  // Vector of top 3 products.
  std::vector<food_item> top3;
  
  std::vector<std::string> warehouseNames;

  void preprocess();
  
  void initialize();

  void removeExpiredFood(int day);

  void compute_unstocked_and_wellstocked_products();

  void compute_top_3_products();

 public:
  processor(file_data & data);
  std::vector<food_item> get_top3_products();
  std::vector<food_item> get_wellstocked_food();
  std::vector<food_item> get_unstocked_food();
};
