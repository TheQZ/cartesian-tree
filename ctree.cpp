#include "ctree.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <locale>
#include <sstream>

// - - - - - - - - - - - //
// DESTRUCTOR/CLEANCTREE //
// - - - - - - - - - - - //
template <class T>
ctree<T>::~ctree()
{
  if(root != nullptr) cleanCtree(root);
}

template <class T>
void ctree<T>::cleanCtree(node<T> *nd)
{
  if(nd != nullptr){
    cleanCtree(nd->left);
    cleanCtree(nd->right);
    delete nd;
  }
}

// - - - - - - - - - - - //
//   INSERT/MOVE AROUND  //
// - - - - - - - - - - - //
template <class T>
void ctree<T>::insert(T data)
{
  if(root == nullptr){
    root = new node<T>(data);
    std::cout << "Inserted: " << data;
  }else{
    insert(root, data);
    std::cout << ", " << data;
  }
}

template <class T>
void ctree<T>::insert(node<T> *nd, T data)
{
  // find rightmost node
  while(nd->right != nullptr) nd = nd->right;
  node<T> *nn = new node<T>(data);
  nn->parent = nd;
  nd->right = nn;
  
  // Call movearound regardless.
  // I think it's better to just let it hit the base case in the function instead.
  moveAround(nn);
}

template <class T>
void ctree<T>::moveAround(node<T> *nd)
{
  if(nd->parent == nullptr) return;
  if(nd->parent->data < nd->data) return;
  
  if(nd->left == nullptr){
    if(nd->parent == root){
      nd->left = nd->parent;
      nd->parent->right = nullptr;
      nd->parent = nullptr;
      nd->left->parent = nd;
      root = nd;
    }else{
      nd->parent = nd->parent->parent;
      nd->left = nd->parent->right;
      nd->left->parent = nd;
      nd->parent->right = nd;
      nd->left->right = nullptr;
    }
  }else{
    if(nd->parent == root) root = nd;
    nd->parent->right = nd->left;
    nd->left->parent = nd->parent;
    nd->left = nd->parent;
    nd->parent = nd->left->parent;
    nd->left->parent = nd;
    if(nd->parent != nullptr) nd->parent->right = nd;
  }
  moveAround(nd);
}

// - - - - - - - - - - - //
//       IN ORDER        //
// - - - - - - - - - - - //
template <class T>
std::string ctree<T>::inOrder()
{
  outStr = "";
  inOrderVec.clear();
  heights.clear();

  if(root == nullptr){
    heights.push_back(0);
    return outStr;
  }

  inOrder(root);
  outStr.erase(outStr.find_last_of(" "));
  outStr.erase(outStr.find_last_of(","));

  return outStr;
}

template <class T>
void ctree<T>::inOrder(node<T> *nd)
{
  if(nd == nullptr) return;

  inOrder(nd->left);
  
  std::ostringstream ss;
  ss << nd->data;
  outStr += ss.str();
  outStr += ", ";

  inOrderVec.push_back(nd->data);
  heights.push_back(getHeight(nd));

  inOrder(nd->right);
}

// - - - - - - - - - - - //
//         SIZE          //
// - - - - - - - - - - - //
template <class T>
int ctree<T>::size()
{
  if(root == nullptr) return 0;
  return size(root);
}

template <class T>
int ctree<T>::size(node<T> *nd)
{
  if(nd == nullptr) return 0;
  return size(nd->left) + size(nd->right) + 1;
}

// - - - - - - - - - - - //
//        HEIGHT         //
// - - - - - - - - - - - //
template <class T>
int ctree<T>::height()
{
  if(root == nullptr) return 0;
  return height(root);
}

template <class T>
int ctree<T>::height(node<T> *nd)
{
  if(nd == nullptr) return 0;
  return std::max(1 + height(nd->left), 1 + height(nd->right));
}

// - - - - - - - - - - - //
//        SEARCH         //
// - - - - - - - - - - - //
template <class T>
bool ctree<T>::search(T data)
{
  if(root == nullptr) return false;
  return search(root, data);
}

template <class T>
bool ctree<T>::search(node<T> *nd, T data)
{
  if(nd == nullptr) return false;
  if(data == nd->data) return true;
  if(data < nd->data) return false;
  return search(nd->left, data) || search(nd->right, data);
}

// - - - - - - - - - - - //
//       VISUALIZE       //
// - - - - - - - - - - - //
template <class T>
void ctree<T>::visualize()
{
  std::cout << inOrder();
  std::cout << "\n";
  for(int i = 0; i < height(); i++){
    for(int j = 0; j < size(); j++){
      if(height() - heights[j] + 1 > 0){
	std::cout << "#  ";
	std::cout << std::string(numSize(inOrderVec[j])-1, ' ');
	heights[j]++;
      }else{
	std::cout << "   ";
	std::cout << std::string(numSize(inOrderVec[j])-1, ' ');
      }
    }
    std::cout << "\n";
  }
}

template <class T>
int ctree<T>::numSize(T num)
{
  std::ostringstream ss;
  ss << num;
  return ss.str().size();
}

// - - - - - - - - - - - //
//      GET HEIGHT       //
// - - - - - - - - - - - //
template <class T>
int ctree<T>::getHeight(node<T> *nd)
{
  int h = 0;
  while(nd != root){
    h++;
    nd = nd->parent;
  }
  return h+1;
}

// - - - - - - - - - - - //
//        IS HEAP        //
// - - - - - - - - - - - //
template <class T>
bool ctree<T>::isHeap()
{
  return isHeap(root);
}

template <class T>
bool ctree<T>::isHeap(node<T> *nd)
{
  if(nd == nullptr) return true;
  if(nd->left != nullptr && nd->data > nd->left->data) return false;
  if(nd->right != nullptr && nd->data > nd->right->data) return false;
  return isHeap(nd->left) && isHeap(nd->right);
}
