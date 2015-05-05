#ifndef CTREE_H_
#define CTREE_H_

#include "node.h"
#include <string>

template <class T>
class ctree
{
 public:
 ctree():root(nullptr){}
  ~ctree();
  
  void insert(T data);
  std::string inOrder();
  int size();
  int height();
  bool search(T data);
  bool isHeap();
    
 private:
  node<T> *root;
  std::string ostr;
  
  void cleanCtree(node<T> *nd);
  void insert(node<T> *nd, T data);
  void moveAround(node<T> *nd);
  void inOrder(node<T> *nd);
  int size(node<T> *nd);
  int height(node<T> *nd);
  bool search(node<T> *nd, T data);
  bool isHeap(node<T> *nd);
};

#include "ctree.cpp"

#endif
