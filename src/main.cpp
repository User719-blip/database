#include "../headers/read.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

//TODO add reme and documnetation for the project 
//TODO include check and blances and error handeling for the given code 
int main()
{
    

    map<string, string> result;
    // result["age"] = "int";
    // result["name"] = "string";

    map<string, string> umap1, umap2, umap3;
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

    int keyToSearch = 10;
    std::map<std::string, std::string> *serched = search(root, keyToSearch);


    // Dynamic Update
    int key_to_update = 10; 
   

    
    update(root, key_to_update, result);
    
    deleteNode(root, 10);
    

    std::map<std::string, std::string> *serches = search_map(root,10);
    
    string filename = "files/text.txt";
    commit(filename, result, root);

    retrieve(filename,root);
    
    inorder(root);

    purge(filename);
    return 0;
}