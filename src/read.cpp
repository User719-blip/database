#include "../headers/read.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>


using namespace std;
//pass schema and your map which you created 
void insert(map<string, string>& umap,  map<string, string>& keys)
{
    cout << "---CREATING MAP--" << endl;
    for (const auto& pair : keys) 
    {
        const string& key = pair.first;
        string value;

        cout << "Enter value for " << key << ": ";
        cin >> value;

        umap[key] = value;
    }

    if(check(umap , keys) == false)
    {
        cerr << "Map does not match the Schema" << endl;
        cout << "Please add new map or change schema" << endl;
        umap.clear();

        cout << "Choose 1 to change schema and 2 to change map";
        int choice;
        cin >> choice;
        if(choice == 1)
        {
            keys.clear();
            keys = create();
            insert(umap , keys);
        }
        else insert(umap , keys);
    }
    else
    {
        cout << "Inserted user data:" << endl;
        for (const auto& pair : umap) 
        {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
    // multiple printing due to recusrsion
    cout << "Map is created kindally insert it into Tree by calling insertNode function" <<endl;
    cout << "OR" << endl;
    cout << "Create another Map by using insert function" << endl;

}
// void insert(map<string, string>& umap, map<string, string>& keys)
// {
//     char choice;
//     do {
//         cout << "---CREATING MAP--"<<endl;
//         for (const auto& pair : keys) 
//         {
//             const string& key = pair.first;
//             string value;

//             cout << "Enter value for " << key << ": ";
//             cin >> value;

//             umap[key] = value;
//         }

//         if(!check(umap , keys))
//         {
//             cerr << "Map does not match the Schema" << endl;
//             cout << "Please add new map or change schema" << endl;
//             umap.clear();

//             cout << "Choose 1 to change schema and 2 to change map: " << endl;
//             int schema_choice;
//             cin >> schema_choice;
//             if(schema_choice == 1)
//             {
//                 keys.clear();
//                 keys = create();
//                 continue; // restart loop with new schema
//             }
//             else continue; // restart loop with same schema
//         }
//         else
//         {
//             cout << "Inserted user data:" << endl;
//             for (const auto& pair : umap) 
//             {
//                 cout << pair.first << ": " << pair.second << endl;
//             }
//         }
//         cout << "Map is created. Kindly insert it into Tree by calling insertNode function." << endl;
//         cout << "OR" << endl;
//         cout << "Create another Map by using insert function." << endl;

//         cout << "Do you want to create another map with the same schema? (y/n): ";
//         cin >> choice;
//         if (choice == 'y' || choice == 'Y') {
//             umap.clear(); // clear for new input
//         }
//     } while (choice == 'y' || choice == 'Y');
// }
bool is_int(const string& c) 
{
    istringstream iss(c);
    int number;
    return (iss >> number) && (iss.eof());
}

bool is_bool(const string& value) {
    string lower;
    for (char c : value) lower += tolower(c);
    return lower == "true" || lower == "false";
}

bool is_filepath(const string& value) {
    // Basic check: contains at least one slash or backslash
    return value.find('/') != string::npos || value.find('\\') != string::npos;
}

bool check(const map<string, string>& umap, const map<string, string>& data) 
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
        else if (expected_type == "bool")
        {
            if (!is_bool(value))
            {
                cout << "Value " << value << " is not a bool" << endl;
                return false;
            }
        }
        else if (expected_type == "filepath")
        {
            if (!is_filepath(value))
            {
                cout << "Value " << value << " is not a valid file path" << endl;
                return false;
            }
        }
        else if (expected_type == "string") 
        {
            // Accept anything that is not int, bool, or filepath
            if (is_int(value) || is_bool(value) || is_filepath(value))
            {
                cout << "Value " << value << " is not a valid string (looks like int, bool, or filepath)" << endl;
                return false;
            }
        }
        else 
        {
            cout << "Unknown type: " << expected_type << endl;
            return false;
        }
    }
    return true;
}