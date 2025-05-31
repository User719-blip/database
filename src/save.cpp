#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>

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
            const std::vector<std::map<std::string, std::string>>& userMaps)
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

    // Write each user map
    for (size_t i = 0; i < userMaps.size(); ++i) 
    {
        file << "-- Hash Map " << i + 1 << " --\n";
        for (const auto& pair : userMaps[i]) 
        {
            file << pair.first << " " << pair.second << "\n";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Schema and hash maps saved successfully.\n";
}



void retrieve(const std::string& filename,
              std::map<std::string, std::string>& schemaMap,
              std::unique_ptr<BSTNode>& root)
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
                insertNode(schemaMap, root, mapCounter++, currentMap);
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