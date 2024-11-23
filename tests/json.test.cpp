#include "../headers/read.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>
//#include "../src/main.cpp"
using namespace std;

// Example usage
int main() 
{   
    map<string,string> umap;
    map<string, string> map ;// Expected data types; // Correct spelling
   insert(map); // Pass the map variable to the insert function
    bool result = check(umap ,map);
    cout << "Check result: " << (result ? "Passed" : "Failed") << endl;
    return 0;
}
