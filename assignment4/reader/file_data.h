/*
 *   A struct containing all transactions, warehouses, food items, and days.
 */

#include <string>
#include <unordered_map>
#include <vector>
#include "../processor/food_item.h"
#include "../processor/warehouse.h"
#include "transaction.h"

#ifndef FILE_DATA_H
#define FILE_DATA_H

struct file_data
{
  // Map the date to a vector of all requests/receives for that day.
  std::vector<std::vector<transaction>> transactions;

  // Maps the warehouse name to warehouse.
  std::unordered_map<std::string, warehouse> warehouses;

  // Maps upc code to food items.
  std::unordered_map<std::string, food_item> foodItems;

  int numDays;
};

#endif
