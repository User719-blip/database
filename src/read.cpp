#include <map>
//we switched from unordred_map to map coz order is importnat during 
//procees of checking consistancy
#include <iostream>
#include <sstream>
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

bool is_int(const string&c)
{
    istringstream iss(c);
    int number;
    return (iss>>number) && (iss.eof());
}

bool check(std::map<std::string,std::string> &umap , std::map<std::string,std::string> &data)
{
    if (umap.size() != data.size()) 
    {
    cout<<"size mismatch :"<<endl;
    return false;
    }
    //extracr key and expected outcome from data map
    for(auto &pair : data)
    {
        const string& key = pair.first;
        const string& outcome = pair.second;
        //check if key exist in umap
        auto it = umap.find(key); //take key of umap
        if(it == umap.end())
        {
            cout<<"key "<<key<<" is missing"<<endl;
            return false;
        }

        const string&value = it->second;
        //check if value is equal to expected outcome
        if(outcome == "string")
        {
            if (outcome == "int")
            {
                if(!is_int(value)) 
                {
                    cout<<"value"<<value<<"is not int";
                    return false;
                }
            }
            else 
            {
                cout<<"Unknown type"<< outcome ;
                return false;
            }
        }
    }
    return true;
}
