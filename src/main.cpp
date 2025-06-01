#include "../headers/read.h"
#include "../src/core.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "../src/save.cpp"
#include <vector>

using namespace std;

//modify the commit function to take bst as an args  
//add hashing to text file
//improve structure of the code
int main()
{
    unique_ptr<BSTNode> root = nullptr;

    // map<string, string> result;
    // result["age"] = "int";
    // result["name"] = "string";

    // map<string, string> umap1, umap2, umap3;
    // umap1["age"] = "21";
    // umap1["name"] = "Abhay";

    // umap2["age"] = "22";
    // umap2["name"] = "Aryan";

    // umap3["age"] = "23";
    // umap3["name"] = "Shubham";
    map<string, string> result = create();
    map<string, string> umap1 , umap2 , umap3;

    insert(umap1 , result);
    insert(umap2 , result);
    insert(umap3 , result);
    
    
    insertNode(result,root, 10, umap1);
    insertNode(result,root, 2, umap2);
    insertNode(result, root, 30, umap3);

    inorder(root);

    // int keyToSearch = 10;
    // std::map<std::string, std::string> *serched = search(root, keyToSearch);


    // Dynamic Update
    int key_to_update = 10; 
   

    ///Updated the key and get the updated map
    std::map<std::string, std::string> updated_map = update(root, key_to_update, result);
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
    root = deleteNode(root, 10);
    std::cout << "After deletion of key 10:" << std::endl;
    inorder(root);

    std::map<std::string, std::string> *serches = search_map(root,10);

    std::vector<std::map<std::string, std::string>> hashmaps = {umap1, umap2, umap3};
    
    string filename = "files/text.txt";
    commit(filename,result , root);
    retrieve(filename,result,root);
    
    inorder(root);

  
    return 0;
}