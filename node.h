#ifndef NODE_H_
#define NODE_H_

#include <QLabel>

template <class T>
struct node
{
node():right(nullptr),left(nullptr),parent(nullptr),data(0), ql(new QLabel()){}
node(T data):right(nullptr),left(nullptr),parent(nullptr),data(data), ql(new QLabel()){}
  
  node *right;
  node *left;
  node *parent;
  T data;
  QLabel *ql;
};

#endif
