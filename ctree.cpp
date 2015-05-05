#include "ctree.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <locale>
#include <sstream>

template <class T>
ctree<T>::~ctree()
{
    if(root != nullptr)
        cleanCtree(root);
}

template <class T>
void ctree<T>::cleanCtree(node<T>* nd)
{
    if(nd != nullptr){
        cleanCtree(nd->left);
        cleanCtree(nd->right);
        delete nd;
    }
}

template <class T>
void ctree<T>::insert(T data)
{
    if(root == nullptr){
        node<T>* nn = new node<T>(data);
        root = nn;
    }else
        insert(root, data);
}

template <class T>
void ctree<T>::insert(node<T>* nd, T data)
{
    // find rightmost node
    while(nd->right != nullptr) nd = nd->right;
    node<T>** nn = new node<T>(data);
    nd->right = nn;

    // if necessary, call movearound
    if(nn->data < nd->data) moveAround(nd);
}

template <class T>
void ctree<T>::moveAround(node * nd) {
    
    // node *s = nd->right; // node that we are moving
    // nd->right = s->left;
    // s->left = nd;
     
    
    //s->parent = nd->parent
    // nd->parent->child = s;
    // change the other parents too:
    // the one for nd->right
    // nd->parent = s
    // etc. etc.
}

template <class T>
std::string ctree<T>::inOrder()
{
    ostr = "";

    if(root == nullptr)
        return this->ostr;

    inOrder(root);
    ostr.erase(ostr.find_last_of(" "));
    ostr.erase(ostr.find_last_of(","));
    return this->ostr;
}

template <class T>
void ctree<T>::inOrder(node<T>* nd)
{
    if(nd == nullptr)
        return;

    inOrder(nd->left);
    ostr += toStr(nd->data);
    ostr += ", ";
    inOrder(nd->right);
}

template <class T>
int ctree<T>::size()
{
    if(root == nullptr)
        return 0;

    return size(root);
}

template <class T>
int ctree<T>::size(node<T>* nd)
{
    if(nd == nullptr)
        return 0;

    return size(nd->left) + size(nd->right) + 1;
}

template <class T>
bool ctree<T>::find(T data)
{
    if(root == nullptr)
        return nullptr;

    return find(root, data);
}

template <class T>
bool ctree<T>::find(node<T>* nd, T data)
{
    if(data == nd->data)
        return nd;

    if(nd->right == nullptr && nd->left == nullptr)
        return nullptr;

    if(data > nd->data)
        return find(nd->right, data);
    else
        return find(nd->left, data);
}

template <class T>
std::string ctree<T>::toStr(T data)
{
    std::ostringstream ss;
    ss << data;
    return ss.str();
}
