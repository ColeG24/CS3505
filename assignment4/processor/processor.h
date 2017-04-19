/*
 * AUTHORS: Cole Gordon & Philipp Hojnacki
 */
#include "../reader/transaction_parser.h"
#include <vector>
#include "food_item.h"
#include "warehouse.h"
#include <string>
#include <unordered_map>

class processor
{
 private:
  transaction_parser & parser;
 
  int day;

  std::vector<food_item> allFood;
  std::vector<food_item> wellStockedFood;
  std::vector<food_item> unstockedFood;

  std::unordered_map<std::string, int> & requestToQuantityMap;
  

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
  processor(transaction_parser & parser);
  std::vector<food_item> get_top3_products();
  std::vector<food_item> get_wellstocked_food();
  std::vector<food_item> get_unstocked_food();
};
