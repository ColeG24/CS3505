#include <string.h>

class receive
{
  private:
    std::string upc;
    std::string warehouseName;
    int count;

  public:
    receive(std::string upc, std::warehouseName, int count);

    std::string get_upc();
    std::string get_warehouse_name();
    int get_count();
};
