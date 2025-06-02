#ifndef READ_H
#define READ_H
// we use this header file coz during test json.test.cpp\
// was calling read.cpp ie circular inclution occuing btween both files
// to avoid this we created a header files
#include <map>
#include <string>
#include <memory> 

struct BSTNode //
{
    int key;
    std::map<std::string, std::string> map;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;

    BSTNode(int k, std::map<std::string, std::string>& m) : key(k), map(m) {} //removing reffrencve from here *m to &m
};

extern std::unique_ptr<BSTNode> root;


void insert(std::map<std::string, std::string>& umap ,   std::map<std::string, std::string>& keys);

bool check(const std::map<std::string,std::string> &umap , const std::map<std::string,std::string> &data);

void insertNode(std::map<std::string , std::string>result,std::unique_ptr<BSTNode>& root, int key, std::map<std::string, std::string>& map); //removing reffrence from here *map to &map

std::map<std::string, std::string> create();

void inorder(const std::unique_ptr<BSTNode>& root) ;

std::map<std::string, std::string>* search(const std::unique_ptr<BSTNode>& root, int key) ;

void update(std::unique_ptr<BSTNode>& root, int key, std::map<std::string, std::string>& schema);

void purge(const std::string& filename);

void deleteNode(std::unique_ptr<BSTNode>& root, int key) ;

std::map<std::string, std::string>* search_map(const std::unique_ptr<BSTNode>& root, int key) ;

void commit(const std::string& filename,const std::map<std::string, std::string>& schemaMap,const std::unique_ptr<BSTNode>& root);

void retrieve(const std::string& filename,std::unique_ptr<BSTNode>& root);
#endif 
