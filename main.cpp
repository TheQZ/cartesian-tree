#include "ctree.h"

int main()
{
  ctree<int> rene;
  rene.insert(5);
  rene.insert(3);
  rene.insert(1);
  rene.insert(8);
  
  std::cout << rene.inOrder() << std::endl;
  
  return 0;
}
