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
  bool find(T data);
  
 private:
  node<T>* root;
  std::string ostr;

  void cleanCtree(node<T>* nd);
  void insert(node<T>* nd, T data);
  void inOrder(node<T>* nd);
  int size(node<T>* nd);
  bool find(node<T>* nd, T data);
  std::string toStr(T data);
};

#include "ctree.cpp"

#endif
