#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

void printList(std::vector<std::pair<long long, long long>> &list){
      for (auto it : list)
    {
        std::cout << "(" << it.first << ", " << it.second << ")" << " ";
    }
    std::cout << std::endl;
}

void analyseRangeStartEnd(std::vector<std::pair<long long, long long>> &list, long long newStart, long long newEnd)
{
    std::sort(list.begin(), list.end(), [](const std::pair<long long, long long> &a, const std::pair<long long, long long> &b){
        return a.first < b.first;
    });
    if (list.size() == 0)
    {
        list.push_back({newStart, newEnd});
        return;
    }
        for (size_t i = 0; i < list.size()-1; i++)
    {
        if (list.at(i).second < list.at(i+1).first){
            continue;
        }
        return;
    }
    for (size_t i = 0; i < list.size(); i++)
    {
        if (newEnd + 1 == list.at(i).first){
            long long temp = list.at(i).second;
            list.erase(list.begin() + i);
            return analyseRangeStartEnd(list, newStart, temp);
        } else if (newEnd == list.at(i).first){
            list.at(i).first = newStart;
            return;
        } else if (newEnd < list.at(i).first){
            list.push_back({newStart, newEnd});
            return;
        }  else if (list.at(i).first<=newStart && newEnd <= list.at(i).second){
            return;
        } else if (newStart <= list.at(i).first && list.at(i).first<=newEnd && list.at(i).second >= newEnd){
            list.at(i).first = newStart;
            return;
        }else if (list.at(i).first <= newStart && newStart <= list.at(i).second && list.at(i).second < newEnd){
            long long temp = list.at(i).first;
            list.erase(list.begin() + i);
            return analyseRangeStartEnd(list, temp, newEnd);
        } else if (list.at(i).second + 1 == newStart){
            long long temp = list.at(i).first;
            list.erase(list.begin() + i);
            return analyseRangeStartEnd(list, temp, newEnd);
        } else if (list.at(i).second < newStart){
            if (i == list.size()-1){
                list.push_back({newStart, newEnd});
                return;
            }
        } else if ( newStart < list.at(i).first && list.at(i).second < newEnd){
            list.erase(list.begin() + i);
            return analyseRangeStartEnd(list, newStart, newEnd);
        }
    }
}

void extractRangeStartEnd(std::vector<std::pair<long long, long long>> &list, const std::string &input)
{
    std::stringstream ss(input);
    std::string startStr, endStr;
    std::getline(ss, startStr, '-');
    std::getline(ss, endStr, '-');

    analyseRangeStartEnd(list, std::stoll(startStr), std::stoll(endStr));
}

int main(void)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    bool isID = false;
    std::vector<std::pair<long long, long long>> rangeList;
    long long sum = 0;

    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine) && fileLine != "")
        {
            
            extractRangeStartEnd(rangeList, fileLine);
        }
    }

    std::cout << std::endl;
    std::sort(rangeList.begin(), rangeList.end(), [](const std::pair<long long, long long> &a, const std::pair<long long, long long> &b){
        return a.first < b.first;
    });
    for (auto it : rangeList)
    {
        if (it.first == it.second){
            std::cout << it.first << " : same : " << it.second << std::endl; 
        }
        sum += it.second - it.first +1;
    }
    std::cout << "Part 2 sum: " << sum << std::endl;
    inFile.close();
    return 0;
}