#pragma once
#include <stdio.h>
#include <memory>
#include "AVLNode.hpp"

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
};

template <class T>
AVLTree<T>::AVLTree(){
    
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
                break;
            }
            currNode = currNode->left;
            break;
        }else{
            if(currNode->right == nullptr){
                currNode->right = make_shared<AVLNode<T>>(AVLNode<T>(newVal, 1, currNode));
                break;
            }
            currNode = currNode->right;
        }
    }
    int iteration = 2;
    while(currNode != nullptr){
        if(currNode->height < iteration){
            currNode->height = iteration;
        }
        int bal = currNode->GetBalance();
        if(bal > 1){
            if(currNode->right->GetBalance() < 1){
                currNode->parent->right = currNode->left;
                currNode->left->parent = currNode->parent;
                auto right = currNode->left->right;
                currNode->left->right = currNode;
                currNode->left = right;

            }
            currNode->parent->right = currNode->left;
            currNode->left = currNode->parent;
            if(currNode->parent == head){
                head = currNode;
            }else{
                if(currNode->parent->parent->left == currNode){
                    currNode->parent->parent->left = currNode;
                }else{
                    currNode->parent->parent->right = currNode;
                }
            }
            currNode->parent = currNode->left->parent;
            currNode->left->parent = currNode;
        }else if(bal < -1){
            if(currNode->left->GetBalance() > 1){
                currNode->parent->left = currNode->right;
                currNode->right->parent = currNode->parent;
                auto left = currNode->right->left;
                currNode->right->left = currNode;
                currNode->right = left;

            }
            currNode->parent->left = currNode->right;
            currNode->right = currNode->parent;
            if(currNode->parent == head){
                head = currNode;
            }else{
                if(currNode->parent->parent->left == currNode){
                    currNode->parent->parent->left = currNode;
                }else{
                    currNode->parent->parent->right = currNode;
                }
            }
            currNode->parent = currNode->right->parent;
            currNode->right->parent = currNode;
        }
        currNode = currNode->parent;
        iteration++;
    }
    
}
