#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream> // for std::istringstream
#include <functional> //for std function u
#include <memory> // for std::unique_ptr
#include "../headers/read.h"
// Forward declaration of BSTNode
// struct BSTNode //
// {
//     int key;
//     std::map<std::string, std::string> map;
//     std::unique_ptr<BSTNode> left;
//     std::unique_ptr<BSTNode> right;

//     BSTNode(int k, std::map<std::string, std::string>& m) : key(k), map(m) {} //removing reffrencve from here *m to &m
// };

// void commit(const std::string& filename, const std::vector<std::map<std::string, std::string>>& maps)
// {

//     std::ofstream file(filename, std::ios::out | std::ios::trunc);
    
//     // std::ofstream file(filename, std::ios::app); 

//     if (file.is_open())
//     {
//         //size_t is unsigned long var type which is returned by map.size fun so i need to be of that type
//         for (size_t i = 0; i < maps.size(); ++i)
//         {
//             file << "--- Hash Map " << i + 1 << " ---\n"; // Separator for each map
//             for (const auto& pair : maps[i])
//             {
//                 file << pair.first << " " << pair.second << "\n";
//             }
//             file << "\n"; 
//         }
//         file.close();
//         std::cout << "All hash maps saved to file successfully.\n";
//     }
//     else
//     {
//         std::cerr << "Error: Unable to open the file.\n";
//     }
// }

void commit(const std::string& filename,
            const std::map<std::string, std::string>& schemaMap,
            const std::unique_ptr<BSTNode>& root)
{
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file.\n";
        return;
    }

    // Write schema section
    file << "-- schema --\n";
    for (const auto& pair : schemaMap)
    {
        file << pair.first << " " << pair.second << "\n";
    }
    file << "\n";

    // Helper lambda for in-order traversal and writing maps
    std::function<void(const std::unique_ptr<BSTNode>&, int&)> inorderWrite;
    inorderWrite = [&](const std::unique_ptr<BSTNode>& node, int& counter)
    {
        if (!node) return;
        inorderWrite(node->left, counter);

        file << "-- Hash Map " << ++counter << " --\n";
        file << "Key: " << node->key << "\n";
        for (const auto& pair : node->map)
        {
            file << pair.first << " " << pair.second << "\n";
        }
        file << "\n";

        inorderWrite(node->right, counter);
    };

    int counter = 0;
    inorderWrite(root, counter);

    file.close();
    std::cout << "Schema and BST hash maps saved successfully.\n";
}



void retrieve(const std::string& filename,std::map<std::string, std::string>& schemaMap,std::unique_ptr<BSTNode>& root)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for reading.\n";
        return;
    }

    std::string line;
    std::map<std::string, std::string> currentMap;
    bool readingSchema = false;
    bool readingUserMap = false;
    int mapCounter = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.find("-- schema --") != std::string::npos) {
            readingSchema = true;
            readingUserMap = false;
            continue;
        }
        else if (line.find("-- Hash Map") != std::string::npos) {
            if (!currentMap.empty()) {
                insertNode(schemaMap, root, mapCounter, currentMap);
                ++mapCounter;
                currentMap.clear();
            }
            readingSchema = false;
            readingUserMap = true;
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;
        iss >> key;
        getline(iss, value);
        if (!value.empty() && value[0] == ' ') value.erase(0, 1);

        if (readingSchema) {
            schemaMap[key] = value;
        } else if (readingUserMap) {
            currentMap[key] = value;
        }
    }

    // Insert the last map if any
    if (!currentMap.empty()) {
        insertNode(schemaMap, root, mapCounter++, currentMap);
    }

    file.close();
}