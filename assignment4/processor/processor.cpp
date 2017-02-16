#include "processor.h"
#include <vector>
#include "food_item.h"
#include "../reader/file_data.h"

processor::processor(file_data data):
  data(data)
{
  
}

void processor::preprocess()
{
  for (int i = 0; i < data.numDays; i++)
  {
    vector<request> requestsForDay = data.requests[i];
    vector<receive> receivesForDay = data.receives[i];

    
  }
}
