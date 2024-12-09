#include "../headers/read.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "../headers/create.h"

using namespace std;

void insert(map<string, string>& umap, const map<string, string>& keys)
{
    for (const auto& pair : keys) 
    {
        const string& key = pair.first;
        string value;

        cout << "Enter value for " << key << ": ";
        cin >> value;

        umap[key] = value;
    }

    cout << "Inserted user data:" << endl;
    for (const auto& pair : umap) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}

bool is_int(const string& c) 
{
    istringstream iss(c);
    int number;
    return (iss >> number) && (iss.eof());
}

bool check(map<string, string>& umap, map<string, string>& data) 
{
    if (umap.size() != data.size()) 
    {
        cout << "Size mismatch" << endl;
        return false;
    }

    for (const auto& pair : data) 
    {
        const string& key = pair.first;
        const string& expected_type = pair.second;

        auto it = umap.find(key);
        if (it == umap.end()) 
        {
            cout << "Key " << key << " is missing" << endl;
            return false;
        }

        const string& value = it->second;

        if (expected_type == "int") 
        {
            if (!is_int(value)) 
            {
                cout << "Value " << value << " is not an int" << endl;
                return false;
            }
        } 
        else if (expected_type != "string") 
        {
            cout << "Unknown type: " << expected_type << endl;
            return false;
        }
    }
    return true;
}
