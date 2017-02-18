/*
 *  Class declaration for a single transaction.
 */

#include <string>
#include "transaction.h"

using namespace std;

// Constructor
transaction::transaction(string upc, string warehouseName, int count, string type, int date) :
  upc(upc), warehouseName(warehouseName), count(count), type(type), date(date)
{}

// Gets the upc code for this transaction
string transaction::get_upc() 
{
  return upc;
}

// Gets the warehouse name for this transaction
string transaction::get_warehouse_name()
{
  return warehouseName;
}

// Gets the quantity for this transaction
int transaction::get_count() 
{
  return count;
}

// Gets the type for this transaction (Receive or Request).
string transaction::get_type()
{
  return type;
}

// Gets the date for this transaction.
int transaction::get_date()
{
  return date;
}
