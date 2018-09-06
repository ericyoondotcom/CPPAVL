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
        void Remove(T val);
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
    shared_ptr<AVLNode<T>> child = node->left;
    auto last = child->right;
    
    child->parent = parent;
    child->right = node;
    node->parent = child;
    node->left = last;
    if(last != nullptr)
        last->parent = node;
    if(parent != nullptr && parent->right == node)
        parent->right = child;
    else if(parent != nullptr && parent->left == node)
        parent->left = child;
    else
        head = child;
    cout << "Prev node height: " << node->Height << endl;
    node->Height -= 2;
    cout << "After node height: " << node->Height << endl;
    return child;
}

template <class T>
shared_ptr<AVLNode<T>> AVLTree<T>::RotateLeft(shared_ptr<AVLNode<T>> node)
{
    auto parent = node->parent;
    shared_ptr<AVLNode<T>> child = node->right;
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
    cout << "Prev node height: " << node->Height << endl;
    node->Height -= 2;
    cout << "After node height: " << node->Height << endl;
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
        cout << bal;
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

template <class T>
void AVLTree<T>::Remove(T val){
    auto currNode = head;
    while(true){
        
        if(val < currNode->val){
            currNode = currNode->left;
        } else if(val > currNode->val){
            currNode = currNode->right;
        }else{
            break;
        }
    }
    if(currNode->left == nullptr){
        if(currNode->right == nullptr){
            //He dies alone... :(
            if(currNode == head){
                head = nullptr;
                return;
            }
            if(currNode->parent->left == currNode){
                currNode->parent->left = nullptr;
                currNode = currNode->parent;
            }else if(currNode->parent->right == currNode){
                currNode->parent->right = nullptr;
                currNode = currNode->parent;
            }else{
                throw "Parent pointers messed up really badly or something.";
            }
            
        }else{
            //He dies with one right heir
            if(currNode == head){
                head = currNode->right;
            }else{
                if(currNode->parent->left == currNode){
                    currNode->parent->left = currNode->right;
                    currNode->right->parent = currNode->parent;
                    
                }else if(currNode->parent->right == currNode){
                    currNode->parent->right = currNode->right;
                    currNode->right->parent = currNode->parent;
                }else{
                    throw "Parent pointers messed up really badly or something.";
                }
                currNode = currNode->right;
            }
        }
    }else if(currNode->right == nullptr){
        //He dies with one left heir
        if(currNode == head){
            head = currNode->left;
        }else{
            if(currNode->parent->left == currNode){
                currNode->parent->left = currNode->left;
                currNode->left->parent = currNode->parent;
            }else if(currNode->parent->right == currNode){
                currNode->parent->right = currNode->left;
                currNode->left->parent = currNode->parent;
            }else{
                throw "Parent pointers messed up really badly or something.";
            }
            currNode = currNode->left;
        }
    }else{
        //He dies with two heirs who will battle for his will in a fight to the death!
        auto searchNode = currNode;
        searchNode = searchNode->left;
        while(searchNode->right != nullptr){
            searchNode = searchNode->right;
        }
        if(searchNode->left == nullptr){
            currNode->val = searchNode->val;
            if(searchNode->parent->left == searchNode){
                searchNode->parent->left = nullptr;
            }else if(searchNode->parent->right == searchNode){
                searchNode->parent->right = nullptr;
            }else{
                throw "Parent pointers messed up really badly or something.";
            }
        }else{
            if(searchNode->parent->left == searchNode){
                searchNode->parent->left = searchNode->left;
                searchNode->left->parent = searchNode->parent;
            }else if(searchNode->parent->right == searchNode){
                searchNode->parent->right = searchNode->left;
                searchNode->left->parent = searchNode->parent;
            }else{
                throw "Parent pointers messed up really badly or something.";
            }
        }
        currNode = searchNode;
    }
    
    while(currNode != nullptr){
        
        int leftHeight = (currNode->left == nullptr ? 0 : currNode->left->Height);
        int rightHeight = (currNode->right == nullptr ? 0 : currNode->right->Height);
        currNode->Height = max(leftHeight, rightHeight) + 1;
        
        int bal = currNode->GetBalance();
        cout << bal;
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
