#ifndef READ_H
#define READ_H
// we use this header file coz during test json.test.cpp\
// was calling read.cpp ie circular inclution occuing btween both files
// to avoid this we created a header files
#include <map>
#include <string>

void insert(std::map<std::string, std::string>& umap ,  const std::map<std::string, std::string>& keys);

bool check(std::map<std::string,std::string> &umap , std::map<std::string,std::string> &data);

//#include "../src/read.cpp"

#endif 
