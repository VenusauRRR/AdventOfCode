#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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
    if (list.size() == 0)
    {
        list.push_back({newStart, newEnd});
        return;
    }
    for (size_t i = 0; i < list.size(); i++)
    {
        if (newStart >= list.at(i).first && newEnd <= list.at(i).second)
        {
        return;
        }
        else if (newStart <= list.at(i).first && newEnd >= list.at(i).first && newEnd <= list.at(i).second)
        {
            list.at(i).first = newStart;
            return;
        }
        else if (newStart <= list.at(i).first && newEnd >= list.at(i).second)
        {
            list.erase(list.begin() + i);
            analyseRangeStartEnd(list, newStart, newEnd);
        }
        else if (newStart >= list.at(i).first && newStart <= list.at(i).second && newEnd > list.at(i).second)
        {
            long long temp = list.at(i).first;
            list.erase(list.begin()+i);
            analyseRangeStartEnd(list, temp, newEnd);
        } else {
            if (i==list.size()-1){
                list.push_back({newStart, newEnd});
                return;
            } else {
                continue;
            }
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
                extractRangeStartEnd(rangeList, fileLine);
            }
            else
            {
                increaseBy1WhenIngredientIsFresh(sum, rangeList, std::stoll(fileLine));
            }
        }
    }

    std::sort(rangeList.begin(), rangeList.end(), [](const std::pair<long long, long long> &a, const std::pair<long long, long long> &b){
        return a.first < b.first;
    });
    std::cout << "sum: " << sum << std::endl;
    inFile.close();
    return 0;
}