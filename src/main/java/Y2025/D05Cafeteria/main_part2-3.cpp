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
    std::cout << "start: " << newStart << ": end: " << newEnd << std::endl;
        // std::cout << "list before: " << std::endl;
        // printList(list);
        // std::cout << "size: " << list.size() << std::endl;
    if (list.size() == 0)
    {
        list.push_back({newStart, newEnd});
        //  std::cout << "list after: " << std::endl;
        //     printList(list);
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
            std::cout << "yes" << std::endl;
            long long temp = list.at(i).second;
            list.erase(list.begin() + i);
            analyseRangeStartEnd(list, newStart, temp);
        } else if (newEnd == list.at(i).first){
            list.at(i).first = newStart;
        } else if (newEnd <= list.at(i).first){
            list.push_back({newStart, newEnd});
            return;
        } else if (newStart <= list.at(i).first && list.at(i).first<=newEnd && list.at(i).second >= newEnd){
            list.at(i).first = newStart;
        } else if (list.at(i).first>newStart && list.at(i).second > newEnd){
            return;
        } else if (list.at(i).first < newStart && newStart <= list.at(i).second && list.at(i).second < newEnd){
            long long temp = list.at(i).first;
            list.erase(list.begin() + i);
            std::cout << "here" << std::endl;
            analyseRangeStartEnd(list, temp, newEnd);
        } else if (list.at(i).second < newStart){
            if (i == list.size()-1){
                list.push_back({newStart, newEnd});
                return;
            }
        } else if (list.at(i).second + 1 == newStart){
            long long temp = list.at(i).first;
            list.erase(list.begin() + i);
            analyseRangeStartEnd(list, temp, newEnd);
        } else if ( newStart < list.at(i).first && list.at(i).second < newEnd){
            list.erase(list.begin() + i);
            analyseRangeStartEnd(list, newStart, newEnd);
        }
    }
    printList(list);
    std::cout << "hello" << std::endl;
}

void extractRangeStartEnd(std::vector<std::pair<long long, long long>> &list, const std::string &input)
{
    std::stringstream ss(input);
    std::string startStr, endStr;
    std::getline(ss, startStr, '-');
    std::getline(ss, endStr, '-');

    std::cout << startStr << "---" << endStr << std::endl;
    analyseRangeStartEnd(list, std::stoll(startStr), std::stoll(endStr));
    printList(list);
}

int main(void)
{
    std::ifstream inFile("testinput.txt");
    std::string fileLine;
    bool isID = false;
    std::vector<std::pair<long long, long long>> rangeList;
    int sum = 0;

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
        // std::cout << "(" << it.first << ", " << it.second << ")" << " ";
        sum += it.second - it.first +1;
    }
    std::cout << "sum: " << sum << std::endl;
    inFile.close();
    return 0;
}