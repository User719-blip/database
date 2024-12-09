#include <iostream>
#include "./core.cpp"
#include "./json.cpp"
#include <string>
#include <map>
#include "../headers/read.h"

using namespace std;

int main() 
{    
    // //inserting data
    map<string , string> umap;
    insert(umap);
    

    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 60);
    insert(root, 15);
    insert(root, 70); 

    cout << "In-order traversal of the BST: ";
    inorder(root);
    cout << endl;

    root = dele(root, 30);
    cout << "In-order traversal after deleting 30: ";
    inorder(root);
    cout << endl;
    
    root = Update(root,30);
    cout << "In-order traversal after updating 30: ";
    inorder(root);
    return 0;
}
