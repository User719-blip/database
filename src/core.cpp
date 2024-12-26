#include <iostream>
#include <map>
#include <memory>

struct BSTNode //
{
    int key;
    std::map<std::string, std::string> map;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;

    BSTNode(int k, std::map<std::string, std::string>& m) : key(k), map(m) {} //removing reffrencve from here *m to &m
};

void insertNode(std::unique_ptr<BSTNode>& root, int key, std::map<std::string, std::string>& map) //removing reffrence from here *map to &map
{
    if (!root) 
    {
        root = std::make_unique<BSTNode>(key, map);
        return;
    }

    if (key < root->key) 
    {
        insertNode(root->left, key, map);
    } 
    else if (key > root->key) 
    {
        insertNode(root->right, key, map);
    } 
    else 
    {
        root->map = map; 
    }
}

void inorder(const std::unique_ptr<BSTNode>& root) 
{
    if (!root) return;

    inorder(root->left);

    std::cout << "Key: " << root->key << std::endl;
    std::cout << "HashMap: " << std::endl;
    for (const auto& pair : (root->map)) //
    {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    inorder(root->right);
}

std::map<std::string, std::string>* search(const std::unique_ptr<BSTNode>& root, int key) 
{
    if (!root) 
    {
        return nullptr; // Key not found
    }

    if (root->key == key) 
    {
        return &(root->map); // Key found, return the hash map
    } 
    else if (key < root->key) 
    {
        return search(root->left, key); // Search in the left subtree
    } 
    else 
    {
        return search(root->right, key); // Search in the right subtree
    }
}


std::map<std::string, std::string> update(std::unique_ptr<BSTNode>& root, int key, const std::map<std::string, std::string>& new_data) 
{
    if (!root) 
    {
        std::cout << "Key not found in the tree." << std::endl;
        return {}; // Return an empty map if the key is not found
    }

    if (root->key == key) 
    {
        root->map = new_data; // Update the HashMap
        std::cout << "Key " << key << " updated successfully." << std::endl;
        return root->map; // Return the updated HashMap
    } 
    else if (key < root->key) 
    {
        return update(root->left, key, new_data);
    } 
    else 
    {
        return update(root->right, key, new_data);
    }
}


std::unique_ptr<BSTNode> deleteNode(std::unique_ptr<BSTNode>& root, int key) 
{
    if (!root)
    {
        std::cout << "Key not found in the tree." << std::endl;
        return nullptr;
    } 
    
    if (key < root->key) 
    {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->key) 
    {
        root->right = deleteNode(root->right, key);
    } 
    else 
    {
        // Node with only one child or no child
        if (!root->left) 
        {
            return std::move(root->right);
        } 
        else if (!root->right) 
        {
            return std::move(root->left);
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        std::unique_ptr<BSTNode>& minNode = root->right;
        while (minNode->left) 
        {
            minNode = std::move(minNode->left);
        }

        root->key = minNode->key;
        root->map = minNode->map;

        // Delete the inorder successor
        root->right = deleteNode(root->right, minNode->key);
    }

    return std::move(root);
}

std::map<std::string, std::string>* search_map(const std::unique_ptr<BSTNode>& root, int key) 
{
    if (!root) 
    {
        return nullptr; // Key not found
    }

    if (root->key == key) 
    {
        std::string field;
        std::cout << "Enter a field to search: ";
        std::cin >> field;

        auto it = root->map.find(field);
        if (it != root->map.end()) 
        {
            std::cout << "Field found: " << it->first << " -> " << it->second << std::endl;
            return &(root->map); // Return pointer to the map
        } 
        else 
        {
            std::cout << "Field not found in the map." << std::endl;
        }
        return nullptr;
    } 
    else if (key < root->key) 
    {
        return search(root->left, key); // Search in the left subtree
    } 
    else 
    {
        return search(root->right, key); // Search in the right subtree
    }
}