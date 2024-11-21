#include<iostream>

struct Node 
{
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};
Node* Update(Node* root , int value)
{
  if (root == nullptr) 
  return root;
  if (value < root->data)
  root->left = Update(root->left ,value);
  if (value > root->data)
  root->right= Update(root->right,value);
  else
  root->data = value ;
  
  return root;
}

// Function to find the in-order successor (smallest in the right subtree)
Node* inorder_successor(Node* root) 
{
    Node* ptr = root;
    while (ptr && ptr->left != nullptr) 
    {
        ptr = ptr->left; // Move to the leftmost node
    }
    return ptr;
}

// Function to delete a node from the BST
Node* dele(Node* root, int value) 
{
    if (root == nullptr) 
    {
        return nullptr; // Node not found
    }
    // seching
    if (value < root->data) 
    {
        root->left = dele(root->left, value);
    } 
    else if (value > root->data) 
    {
        root->right = dele(root->right, value);
    } 
    else //leaf node 
    {
        // Node with one or no child
        if (root->left == nullptr) 
        {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Node* in_succ = inorder_successor(root->right);
        root->data = in_succ->data;
        root->right = dele(root->right, in_succ->data);
    }

    return root;
}

// Function to insert a node into the BST
Node* insert(Node* root, int value) 
{
    if (root == nullptr) 
    {
        return new Node(value);
    }
    if (value < root->data) 
    {
        root->left = insert(root->left, value);
    } 
    else 
    {
        root->right = insert(root->right, value);
    }
    return root;
}

// Function for in-order traversal of the BST
void inorder(Node* root) 
{
    if (root != nullptr) 
    {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
}