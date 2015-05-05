#ifndef NODE_H_
#define NODE_H_

template <class T>
struct node
{
  node* right;
  node* left;
  T data;
  node():right(nullptr),left(nullptr),data(0){}
  node(T dta):right(nullptr),left(nullptr),data(dta){}
};

#endif
