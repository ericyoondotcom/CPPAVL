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
    int height;
    int GetBalance();
    shared_ptr<AVLNode<T>> left = nullptr;
    shared_ptr<AVLNode<T>> right = nullptr;
    shared_ptr<AVLNode<T>> parent = nullptr;
private:
};

template <class T>
AVLNode<T>::AVLNode(T newVal, int newHeight, shared_ptr<AVLNode<T>> newParent){
    val = newVal;
    height = newHeight;
    parent = newParent;
}

template <class T>
int AVLNode<T>::GetBalance(){
    if(left == nullptr){
        if(right == nullptr){
            return 0;
        }
        return right->height;
    }
    if(right == nullptr){
        return -left->height;
    }
    return right->height - left->height;
}
