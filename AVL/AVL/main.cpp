#include <iostream>
#include "AVLTree.hpp"
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    AVLTree<int> tree;
    while(true){
        cout << "What should I do?\n(add / delete) > ";
        string op;
        cin >> op;
        if(op == "add" || op == "insert" || op == "i" || op == "a" || op == "+"){
            cout << "What value should I add?\n<int> > ";
            int newval;
            cin >> newval;
            tree.Insert(newval);
        }else if(op == "remove" || op == "delete" || op == "-" || op == "d" || op == "r"){
            int val;
            cin >> val;
        }else{
            cout << "I don't understand.\n";
        }
        cout << "\n~~~~~~~~~~~~~~~~~~\n";
    }
    return 0;
}

