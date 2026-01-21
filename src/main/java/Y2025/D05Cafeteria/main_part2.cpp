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

void increaseBy1WhenIngredientIsFresh(int &sum, std::vector<std::pair<long long, long long>> &list, long long nr){
    for(auto it: list){
        if (nr >= it.first && nr <= it.second){
            sum += 1;
            return;
        }
    }
}

void analyseRangeStartEnd(std::vector<std::pair<long long, long long>> &list, long long newStart, long long newEnd)
{
    
        std::cout << "list before: " << std::endl;
        printList(list);
        std::cout << "size: " << list.size() << std::endl;
    if (list.size() == 0)
    {
        list.push_back({newStart, newEnd});
         std::cout << "list after: " << std::endl;
            printList(list);
        return;
    }
    for (size_t i = 0; i < list.size(); i++)
    {
        std::cout << newStart << "," << newEnd << std::endl;
        std::cout << list.at(i).first << std::endl;
        std::cout << list.at(i).second << std::endl;
        std::cout << (newStart > list.at(i).first) << std::endl;
        std::cout << (newStart - list.at(i).second > 0)  << std::endl;
        std::cout << (newEnd > list.at(i).second) << std::endl;
        if (newStart >= list.at(i).first && newEnd <= list.at(i).second)
        {
        std::cout << "i: " << i << ", newStart: " << newStart << ", newEnd: " << newEnd << std::endl;
        std::cout << "list for x < start-end < y: " << std::endl;
        printList(list);
        return;
        }
        else if (newStart <= list.at(i).first && newEnd >= list.at(i).first && newEnd <= list.at(i).second)
        {
            list.at(i).first = newStart;
             std::cout << "list for start < x < end < y: " << std::endl;
            printList(list);
            return;
        }
        else if (newStart <= list.at(i).first && newEnd >= list.at(i).second)
        {
            list.erase(list.begin() + i);
            std::cout << "list for start < x - y > end: " << std::endl;
            printList(list);
            analyseRangeStartEnd(list, newStart, newEnd);
        }
        else if (newStart >= list.at(i).first && newStart <= list.at(i).second && newEnd > list.at(i).second)
        {
            long long temp = list.at(i).first;
            list.erase(list.begin()+i);
            std::cout << "list for x < start < y < end: " << std::endl;
            printList(list);
            std::cout << "temp: " << temp << ", end: " << newEnd << std::endl;
            analyseRangeStartEnd(list, temp, newEnd);
        } else {
            if (i==list.size()-1){
                std::cout << "add push back: " << newStart << ", " << newEnd << std::endl;
                list.push_back({newStart, newEnd});
                return;
            } else {
                continue;
            }
        }
    }
    
    // printList(list);
    // std::cout << "first: " << list.end().base()->first << ", second: " << list.end().base()->second << std::endl;
}

void extractRangeStartEnd(std::vector<std::pair<long long, long long>> &list, const std::string &input)
{
    std::stringstream ss(input);
    std::string startStr, endStr;
    std::getline(ss, startStr, '-');
    std::getline(ss, endStr, '-');

    std::cout << startStr << "---" << endStr << std::endl;
    analyseRangeStartEnd(list, std::stoll(startStr), std::stoll(endStr));
}

int main(void)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    bool isID = false;
    std::vector<std::pair<long long, long long>> rangeList;
    int sum = 0;

    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine))
        {
            if (fileLine == "" && isID == false)
            {
                isID = true;
                continue;
            }
            if (isID != true)
            {
                std::cout << "range: " << fileLine << std::endl;
                extractRangeStartEnd(rangeList, fileLine);
            }
            else
            {
                std::cout << "id: " << fileLine << std::endl;
                increaseBy1WhenIngredientIsFresh(sum, rangeList, std::stoll(fileLine));
            }
        }
    }

    std::sort(rangeList.begin(), rangeList.end(), [](const std::pair<long long, long long> &a, const std::pair<long long, long long> &b){
        return a.first < b.first;
    });
    for (auto it : rangeList)
    {
        std::cout << "(" << it.first << ", " << it.second << ")" << " ";
    }
    std::cout << std::endl;
    std::cout << "sum: " << sum << std::endl;
    inFile.close();
    return 0;
}