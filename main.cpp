#include "ctree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  std::vector<int> v;
  ctree<int> rene;
  int n, s;
  
  /*<DBG>*
  if(argc != 3){
    std::cout << "Correct syntax: " << argv[0] << " <[# of elements]> <[# to search for]>\n";
    return 1;
  }

  srand(time(NULL));  

  n = atoi(argv[1]);
  s = atoi(argv[2]);

  for(int i = 0; i < n; i++)  
    v.push_back(rand()%1000);
  /*</DBG>*//*<DBG>*/
  v.push_back(5);
  v.push_back(3);
  v.push_back(1);
  v.push_back(8);
  v.push_back(0);
  /*</DBG>*/
  for(int i = 0; i < v.size(); i++)  
    rene.insert(v[i]);
  
  std::cout << "\nIn-Order: " << rene.inOrder() << std::endl;
  std::cout << "Is Heap?: " << (rene.isHeap() ? "Yes, indeed." : "No, sirree.") << std::endl;
  std::cout << "Search(" << (s ? s : 1) << "): " << (rene.search((s ? s : 1)) ? "Found it!" : "Not there.") << std::endl;
  std::cout << "Size: " << rene.size() << std::endl;
  std::cout << "Height: " << rene.height() << std::endl;
  
  return 0;
}
