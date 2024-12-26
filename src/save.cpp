#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>

void commit(const std::string& filename, const std::vector<std::map<std::string, std::string>>& maps)
{

    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    
    // std::ofstream file(filename, std::ios::app); 

    if (file.is_open())
    {
        //size_t is unsigned long var type which is returned by map.size fun so i need to be of that type
        for (size_t i = 0; i < maps.size(); ++i)
        {
            file << "--- Hash Map " << i + 1 << " ---\n"; // Separator for each map
            for (const auto& pair : maps[i])
            {
                file << pair.first << " " << pair.second << "\n";
            }
            file << "\n"; 
        }
        file.close();
        std::cout << "All hash maps saved to file successfully.\n";
    }
    else
    {
        std::cerr << "Error: Unable to open the file.\n";
    }
}


void retrive(const std::string& filename)
{
   std::ifstream file(filename);

   if(file.is_open())
   {
    std::string line;

    while(getline(file ,line))
    {
      std::cout << line << std::endl;   
    }
    file.close();
   }

   else
   {
    std::cerr << "Error: Unable to open a file.\n";
   }
}

