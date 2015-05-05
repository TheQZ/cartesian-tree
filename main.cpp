#include "ctree.h"

int main()
{
  ctree<int> rene;
  rene.insert(5);
  rene.insert(3);
  rene.insert(1);
  rene.insert(8);
  rene.insert(0);
  rene.insert(2);
  rene.insert(7);
  rene.insert(35);
  rene.insert(4);
  rene.insert(9);
  
  std::cout << "\nIn-Order: " << rene.inOrder() << std::endl;
  std::cout << "Is Heap?: " << (rene.isHeap() ? "Yes, indeed." : "No, sirree.") << std::endl;

  return 0;
}
