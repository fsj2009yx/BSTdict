#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include<map>

class MyMap {
public:
    void readCSV(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
        }

        std::string line;
        std::getline(file, line);// 跳过第一行

        std::string value1, value2;
        // Read the file line by line
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            if (std::getline(ss, value1, ',') && std::getline(ss, value2, ',')) {

                value1.erase(std::remove(value1.begin(), value1.end(), '"'), value1.end());
                value2.erase(std::remove(value2.begin(), value2.end(), '"'), value2.end());
                mp.insert(std::make_pair(value1, value2));
            }
        }
        file.close();
    }

    std::vector<std::pair<std::string, std::string>> search(const std::string& key)
    {
        std::vector<std::pair<std::string, std::string>> result;
        auto it = mp.find(key); // 查找key
        if (it != mp.end()) {
            result.push_back(*it); // 使用map内部元素的地址
        }
        return result;
    }
private:
    std::map<std::string, std::string> mp;
};