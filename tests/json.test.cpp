#include "../headers/read.h"
#include "../headers/create.h"
#include "../src/core.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

// fix update function as it is returing only update value to the tree
// and not the updated tree itself
// and we need a function to get the value of a specific key from a specific map
// and we need a to check the updated map follows a structure of schema PRIORITY
int main()
{
    unique_ptr<BSTNode> root = nullptr;

    map<string, string> result;
    result["age"] = "int";
    result["name"] = "string";

    map<string, string> umap1, umap2, umap3;
    umap1["age"] = "21";
    umap1["name"] = "Abhay";

    umap2["age"] = "22";
    umap2["name"] = "Aryan";

    umap3["age"] = "23";
    umap3["name"] = "Shubham";
    // map<string, string> result = create();
    // map<string, string> umap1 , umap2 , umap3;

    // insert(umap1 , result);
    // insert(umap2 , result);
    // insert(umap3 , result);

    // bool ischeck = check(umap1, result );
    //  cout << "Check result: " << (ischeck ? "True" : "False") << endl;
    //  ischeck = check(umap2, result );
    //  cout << "Check result: " << (ischeck ? "True" : "False")<< endl;
    //  ischeck = check(umap3, result);
    //  cout << "Check result: " << (ischeck ? "True" : "False")<< endl;

    insertNode(root, 10, umap1);
    insertNode(root, 2, umap2);
    insertNode(root, 30, umap3);

    inorder(root);

    // int keyToSearch = 10;
    // std::map<std::string, std::string> *serched = search(root, keyToSearch);

    // if (serched)
    // {
    //     std::cout << "Key " << keyToSearch << " found in the BST. Hash Map:" << std::endl;
    //     for (const auto &pair : *serched)
    //     {
    //         std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    //     }
    // }
    // else
    // {
    //     std::cout << "Key " << keyToSearch << " not found in the BST." << std::endl;
    // }

    // Dynamic Update
    int key_to_update = 10;
    // std::cout << "Enter the key to update: ";
    // std::cin >> key_to_update;

    std::map<std::string, std::string> *old_data = search(root, key_to_update);
    std::map<std::string, std::string> new_data(*old_data);
    for (const auto &pair : new_data)
    {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    // new_data["name"] = (&old_data)["name"];
    // new_data["age"] = (&old_data)["age"];

    char choice;
    do
    {
        std::string field, value;
        std::cout << "Enter field to update: ";
        std::cin >> field;
        std::cout << "Enter new value for " << field << ": ";
        std::cin >> value;
        new_data[field] = value;

        std::cout << "Do you want to add/update another field? (y/n): ";
        std::cin >> choice;

        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            std::cout << "Invalid choice! Please enter 'y' or 'n': ";
            std::cin >> choice;
        }
    } while (choice == 'y' || choice == 'Y');

    // for(const auto& pair: ){
    //     string key = pair.first;
    //     string val = pair.second;

    //     if()
    // }

    std::cout << "After update" << std::endl;
    for (const auto &pair : new_data)
    {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }

    // Updated the key and get the updated map
    std::map<std::string, std::string> updated_map = update(root, key_to_update, new_data);

    if (!updated_map.empty())
    {
        std::cout << "Updated HashMap for key " << key_to_update << ":\n";
        for (const auto &pair : updated_map)
        {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }

    // Display BST after update
    std::cout << "BST after update:\n";
    inorder(root);
    // root = deleteNode(root, 10);
    // std::cout << "After deletion of key 10:" << std::endl;
    // inorder(root);

    return 0;
}
