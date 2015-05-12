#ifndef NODE_H_
#define NODE_H_

template <class T>
struct node
{
node():right(nullptr),left(nullptr),parent(nullptr),data(0){}
node(T data):right(nullptr),left(nullptr),parent(nullptr),data(data){}
  
  node *right;
  node *left;
  node *parent;
  T data;

};

#endif
