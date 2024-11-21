#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

void trim(string &str) 
{
    // Trim leading and trailing whitespaces
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) { return !isspace(ch); }));
    str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), str.end());
}

map<string, string> parseJson(const string &jsonStr) {
    map<string, string> data;
    stringstream ss(jsonStr);
    string line;

    while (getline(ss, line)) {
        trim(line);
        if (line.empty() || line[0] == '{' || line[0] == '}') {
            continue;
        }

        auto colonPos = line.find(':');
        string key = line.substr(0, colonPos);
        string value = line.substr(colonPos + 1);

        // Remove quotes and commas from key and value
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());

        trim(key);
        trim(value);

        data[key] = value;
    }
    return data;
}

