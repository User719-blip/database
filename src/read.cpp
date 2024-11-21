#include <map>
//we switched from unordred_map to map coz order is importnat during 
//procees of checking consistancy
#include <iostream>
#include <string>
#include "../headers/read.h"

using namespace std;

void insert(map<string, string>& umap) 
{
    string name, age, city;
    cout << "Enter name: ";
    cin >> name;

    cout << "Enter age: ";
    cin >> age;

    cout << "Enter city: ";
    cin >> city;

    umap["name"] = name;
    umap["city"] = city;
    umap["age"] = age;

    for (const auto& pair : umap) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}

