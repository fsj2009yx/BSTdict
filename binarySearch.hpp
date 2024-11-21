#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include<map>
#include<algorithm>
class binarySearch {
public:
    void readCSV(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
        }

        std::string line;
        std::getline(file, line);// ������һ��

        std::string value1, value2;
        // Read the file line by line
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            if (std::getline(ss, value1, ',') && std::getline(ss, value2, ',')) {

                value1.erase(std::remove(value1.begin(), value1.end(), '"'), value1.end());
                value2.erase(std::remove(value2.begin(), value2.end(), '"'), value2.end());
                data.push_back(std::make_pair(value1, value2));
            }
        }
        //����key�ĵ��������Ա����ʹ�ö��ֲ���
        std::sort(data.begin(), data.end(), [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
            return a.first < b.first;
        });
        file.close();
    }

    //����ƥ�����������е�����
    std::vector<std::pair<std::string*,std::string*>> search(const std:: string& key) {
        int mid;
        int left = 0;
        int right = data.size();
        std::vector<std::pair<std::string*, std::string*>> result;
        while (left < right)
        {
            mid = left + (right - left) / 2;
            if (data[mid].first == key)
            {
                result.push_back(make_pair(&data[mid].first, &data[mid].second));
                return result; // �ҵ�
            }
            else if (data[mid].first < key) // ˵�����ұ�
            {
                left = mid + 1;
            }
            else // ˵�������
            {
                if (data[mid].first.find(key) == 0)
                {
                    result.push_back(make_pair(&data[mid].first, &data[mid].second));
                }
                right = mid;
            }
        }
        //û���ҵ�������result
        return result;
    }
private:
    std::vector<std::pair<std::string, std::string>> data;
};