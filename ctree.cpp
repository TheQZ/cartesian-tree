#include "ctree.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <locale>
#include <sstream>
#include <queue>

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

// - - - - - - - - - - - //
//      DELETE KEY       //
// - - - - - - - - - - - //
template <class T>
void ctree<T>::deleteKey() {
  if (root == nullptr) return;

<<<<<<< Updated upstream
  // create a queue of pointers to nodes 
  std::queue<node<T>*> q();
=======
    // create a queue of pointers to nodes 
    std::queue<node<T> *> q = new std::queue<node<T> *>{};
>>>>>>> Stashed changes

  // add all nodes except root to a queue in order
  addToQueue(q);
  root->left = nullptr;
  root->right = nullptr;

  // delete key
  delete root;

  // reinsert nodes according to order.
  while(!q.empty()) {
    reinsert(q.pop());
  }
}

template <class T>
void ctree<T>::addToQueue(std::queue<node<T>*> &q) {
  // add nodes left of root to queue in sorted order
  addToQueue(root->left, q);
  // add nodes right of root to queue in sorted order
  addToQueue(root->right, q);
}

template <class T>
void ctree<T>::addToQueue(node<T> *n, std::queue<node<T>*> &q) {
  if(n == nullptr) return;

  addToQueue(n->left, q);
  n->left == nullptr;

  node<T> *t = n->right;
  t->parent = nullptr;
  n->right == nullptr;

  n->parent == nullptr;
  q.push(n);
    
  addToQueue(t);
}

template <class T>
<<<<<<< Updated upstream
void ctree<T>::reinsert(node<T> * n) {
  if(root == nullptr) root = n;
  else {
    node<T> *t = root;
    while(t->right != nullptr) t = t->right;
    n->parent = t;
    t->right = n;
    moveAround(n);
  }
=======
void ctree<T>::reinsert(node<T> *n) {
    if(root == nullptr) root = n;
    else {
        node<T> *t = root;
        while(t->right != nullptr) t = t->right;
        n->parent = t;
        t->right = n;
        moveAround(n);
    }
>>>>>>> Stashed changes
}

// - - - - - - - - - - - - //
//  VECTOR IN SORTED ORDER //
// - - - - - - - - - - - - //
template <class T>
<<<<<<< Updated upstream
std::vector<node<T>*> ctree<T>::sortedVector() {
  std::vector<node<T>*> candidates = new std::vector<node<T>*>{};
  std::vector<node<T>*> sorted = new std::vector<node<T>*>{};

  candidates.push_back(root);
  while(!candidates.empty()) {
    unsigned int i = smallestCandidate(candidates);
    node<T> *s = candidates[i];
    sorted.push_back(s);
    candidates.erase(candidates.begin() + i);

    if(s->left != nullptr) candidates.push_back(s->left);
    if(s->right != nullptr) candidates.push_back(s->right);
  }
=======
std::vector<node<T> *> ctree<T>::sortedVector() {
    std::vector<node<T> *> candidates = new std::vector<node<T> *>{};
    std::vector<node<T> *> sorted = new std::vector<node<T> *>{};

    candidates.push_back(root);
    while(!candidates.empty()) {
        unsigned int i = smallestCandidate(candidates);
        node<T> *s = candidates[i];
        sorted.push_back(s);
        candidates.erase(candidates.begin() + i);

        if(s->left != nullptr) candidates.push_back(s->left);
        if(s->right != nullptr) candidates.push_back(s->right);
    }
>>>>>>> Stashed changes

  return sorted;
}

template <class T>
<<<<<<< Updated upstream
unsigned int ctree<T>::smallestCandidate(std::vector<node<T>*> &c) {
  unsigned int smallest = 0;
  for (int i = 0; i < c.size(); i++) {
    if(c[i]->data < c[smallest]->data) smallest = i;
  }
  return smallest;
=======
unsigned int ctree<T>::smallestCandidate(std::vector<node<T> *> &c) {
    unsigned int smallest = 0;
    for (int i = 0; i < c.size(); i++) {
        if(c[i]->data < c[smallest]->data) smallest = i;
    }
    return smallest;
>>>>>>> Stashed changes
}
