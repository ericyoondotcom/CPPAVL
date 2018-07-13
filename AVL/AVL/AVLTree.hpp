#pragma once
#include <stdio.h>
#include <memory>
#include "AVLNode.hpp"
#include <algorithm>

using namespace std;
template <class T>
class AVLTree
{
    public:
        AVLTree();
        void Insert(T newVal);
        void Delete(T value);
        shared_ptr<AVLNode<T>> head;
    private:
    shared_ptr<AVLNode<T>> RotateRight(shared_ptr<AVLNode<T>> node);
    shared_ptr<AVLNode<T>> RotateLeft(shared_ptr<AVLNode<T>> node);
};

template <class T>
AVLTree<T>::AVLTree(){
    
}

template <class T>
shared_ptr<AVLNode<T>> AVLTree<T>::RotateRight(shared_ptr<AVLNode<T>> node)
{
    auto parent = node->parent;
    auto child = node->left;
    auto last = child->right;
    
    child->parent = parent;
    child->right = node;
    node->parent = child;
    node->left = last;
    if(last != nullptr)
        last->parent = node;
    if(parent != nullptr && parent->left == node)
        parent->left = child;
    else if(parent != nullptr && parent->right == node)
        parent->right = child;
    else
        head = child;
    child->Height++;
    node->Height--;
    return child;
}

template <class T>
shared_ptr<AVLNode<T>> AVLTree<T>::RotateLeft(shared_ptr<AVLNode<T>> node)
{
    auto parent = node->parent;
    auto child = node->right;
    auto last = child->left;
    
    child->parent = parent;
    child->left = node;
    node->parent = child;
    node->right = last;
    if(last != nullptr)
        last->parent = node;
    if(parent != nullptr && parent->right == node)
        parent->right = child;
    else if(parent != nullptr && parent->left == node)
        parent->left = child;
    else
        head = child;
    child->Height++;
    node->Height--;
    return child;
}


template <class T>
void AVLTree<T>::Insert(T newVal){
    if(head == nullptr){
        head = make_shared<AVLNode<T>>(AVLNode<T>(newVal, 1));
        return;
    }
    auto currNode = head;
    while(true){
        
        if(newVal < currNode->val){
            
            if(currNode->left == nullptr){
                currNode->left = make_shared<AVLNode<T>>(AVLNode<T>(newVal, 1, currNode));
                currNode->left->parent = currNode;
                break;
            }
            currNode = currNode->left;
            break;
        }else{
            if(currNode->right == nullptr){
                currNode->right = make_shared<AVLNode<T>>(AVLNode<T>(newVal, 1, currNode));
                currNode->right->parent = currNode;
                break;
            }
            currNode = currNode->right;
        }
    }
    
    while(currNode != nullptr){
        
        int leftHeight = (currNode->left == nullptr ? 0 : currNode->left->Height);
        int rightHeight = (currNode->right == nullptr ? 0 : currNode->right->Height);
        currNode->Height = max(leftHeight, rightHeight) + 1;
        
        int bal = currNode->GetBalance();
        
        if(bal > 1){
            
            if(currNode->right->GetBalance() < 0)
                RotateRight(currNode->right);
            
            currNode = RotateLeft(currNode);
        }else if(bal < -1){
            
            if(currNode->left->GetBalance() > 0)
                RotateLeft(currNode->left);
            
            currNode = RotateRight(currNode);
        }
        currNode = currNode->parent;
    }
}
