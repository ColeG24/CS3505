/*
 * AUTHORS: Cole Gordon & Philipp Hojnackie
 */
/*
 *  Represents a single transaction.
 */

#include <string.h>

#ifndef TRANSACTION_H
#define TRANSACTION_H

class transaction
{
  private:
    std::string upc;
    std::string warehouseName;
    std::string type;
    int count;
    int date;

  public:
    // Construtor
    transaction(std::string upc, std::string warehouseName, int count, std::string type, int date);

    // Accessors
    std::string get_upc();
    std::string get_warehouse_name();
    int get_count();
    int get_date();
    std::string get_type();
};

#endif
