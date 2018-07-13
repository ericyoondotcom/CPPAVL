#pragma once
#include <stdio.h>
#include <memory>

using namespace std;
template <class T>
class AVLNode
{
public:
    AVLNode(T newVal, int newHeight = 1, shared_ptr<AVLNode<T>> newParent = nullptr);
    T val;
    int Height;
    int GetBalance();
    shared_ptr<AVLNode<T>> left = nullptr;
    shared_ptr<AVLNode<T>> right = nullptr;
    shared_ptr<AVLNode<T>> parent = nullptr;

private:
};


template <class T>
AVLNode<T>::AVLNode(T newVal, int newHeight, shared_ptr<AVLNode<T>> newParent){
    val = newVal;
    parent = newParent;
    Height = 1;
}

template <class T>
int AVLNode<T>::GetBalance(){
    
    if(right == nullptr && left == nullptr)
    {
        return 0;
    }
    if(left == nullptr)
    {
        return right->Height;
    }
    if(right == nullptr){
        return -1 * left->Height;
    }
    return right->Height - left->Height;
}
