#include <iostream>
#include <map>
#include <memory>
#include "../headers/read.h"

std::unique_ptr<BSTNode> root = nullptr;
// struct BSTNode //
// {
//     int key;
//     std::map<std::string, std::string> map;
//     std::unique_ptr<BSTNode> left;
//     std::unique_ptr<BSTNode> right;

//     BSTNode(int k, std::map<std::string, std::string>& m) : key(k), map(m) {} //removing reffrencve from here *m to &m
// };

// key is randome value type int
void insertNode(std::map<std::string , std::string>result,std::unique_ptr<BSTNode>& root, int key, std::map<std::string, std::string>& map) ///removing reffrence from here *map to &map
{
    if (key < 0) 
    {
        std::cout << "Invalid key. Key must be a non-negative integer." << std::endl;
        return;
    }
    if (map.empty()) 
    {
        std::cout << "Empty map provided. No data to insert." << std::endl;
        return;
    }
    if (result.empty()) 
    {
        std::cout << "Result map is empty. No schema to validate against." << std::endl;
        return;
    }
    if (!check(map, result)) 
    {
        std::cout << "Provided map does not match the schema." << std::endl;
        return;
    }
    if (!root) 
    {
        root = std::make_unique<BSTNode>(key, map);
        return;
    }

    if (key < root->key) 
    {
        insertNode(result, root->left, key, map);
    } 
    else if (key > root->key) 
    {
        insertNode(result, root->right, key, map);
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
// return pointer to the map
// use eg std::map<std::string, std::string>* map = search()
std::map<std::string, std::string>* search(const std::unique_ptr<BSTNode>& root, int key) 
{
    if (!root) 
    {
        std::cout << "Key " << key << " not found in the BST." << std::endl;
        return nullptr; // Key not found
    }

    if (root->key == key) 
    {
        std::cout << "Key " << key << " found in the BST."<< std::endl << " Hash Map:" << std::endl;
        for (const auto& pair : root->map) 
        {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
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


void update(std::unique_ptr<BSTNode>& root, int key, std::map<std::string, std::string>& schema)
{
    // Find the node using search
    std::map<std::string, std::string>* old_data = search(root, key);
    if (!old_data) 
    {
        std::cout << "Key not found in the tree." << std::endl;
        return;
    }

    // Make a copy of the original data
    std::map<std::string, std::string> original_data = *old_data;
    std::map<std::string, std::string> new_data = original_data;

    // Show current data
    std::cout << "Current data:\n";
    for (const auto& pair : original_data) 
    {
        std::cout << "  " << pair.first << " : " << pair.second << std::endl;
    }

    // User input loop for updating fields
    char choice;
    do {
        std::string field, value;
        std::cout << "Enter field to update: ";
        std::cin >> field;
        std::cout << "Enter new value for " << field << ": ";
        std::cin >> value;
        new_data[field] = value;

        std::cout << "Do you want to add/update another field? (y/n): ";
        std::cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            std::cout << "Invalid choice! Please enter 'y' or 'n': ";
            std::cin >> choice;
        }
    } while (choice == 'y' || choice == 'Y');

    // Update the map in the BST node
    *old_data = new_data;

    // Validate the update
    if (!check(new_data, schema)) 
    {
        std::cout << "Validation failed. Reverting changes.\n";
        *old_data = original_data; // Restore original
        return;
    } 
    else 
    {
        std::cout << "Key " << key << " updated successfully.\n";
        std::cout << "Updated hash map:\n";
        for (const auto& pair : new_data) 
        {
            std::cout << "  " << pair.first << " : " << pair.second << std::endl;
        }
        // Call inorder to print the tree after update
        std::cout << "BST after update:\n";
        inorder(root);
    }
}

void deleteNode(std::unique_ptr<BSTNode>& root, int key) 
{
    if (!root)
    {
        std::cout << "Key not found in the tree." << std::endl;
        return;
    } 
    
    if (key < root->key) 
    {
        deleteNode(root->left, key);
    } 
    else if (key > root->key) 
    {
        deleteNode(root->right, key);
    } 
    else 
    {
        // Node with only one child or no child
        if (!root->left) 
        {
            root = std::move(root->right);
        } 
        else if (!root->right) 
        {
            root = std::move(root->left);
        }
        else 
        {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            std::unique_ptr<BSTNode>* minNode = &root->right;
            while ((*minNode)->left) 
            {
                minNode = &((*minNode)->left);
            }

            root->key = (*minNode)->key;
            root->map = (*minNode)->map;

            // Delete the inorder successor
            deleteNode(root->right, (*minNode)->key);
        }
    }

    // Print the tree after deletion
    std::cout << "BST after deletion:\n";
    inorder(root);
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