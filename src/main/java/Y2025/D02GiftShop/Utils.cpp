#include "Utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

void part1_findInvalidID(std::vector<long long> &storeList, std::string startString, std::string endString)
{
    long long start = std::stoll(startString);
    long long end = std::stoll(endString);
    for (long long i = start; i <= end; i++)
    {
        std::string s = std::to_string(i);
        int len = s.length();
        if (len % 2 == 0)
        {
            std::string s1 = s.substr(0, len / 2);
            std::string s2 = s.substr(len / 2);
            if (s1 == s2)
            {
                storeList.push_back(i);
            }
        }
    }
}

void part2_findNewInvalidID(std::vector<long long> &storeList, std::string startString, std::string endString)
{
    long long start = std::stoll(startString);
    long long end = std::stoll(endString);
    // std::cout << start << "-" << end << std::endl;
    bool isValidSubstr = false;
    for (long long i = start; i <= end; i++)
    {
        std::string s = std::to_string(i);
        int len = s.length();
        for (size_t j = 2; j <= len; j++)
        {
            if (len % j == 0 && !isValidSubstr)
            {
                std::string ref = s.substr(0, len / j);
                // std::cout << "i: " << i << ", ref: " << ref << std::endl;
                int k = 1;
                while (k < j)
                {
                    std::string cmp = s.substr(k * len / j, len / j);
                    // std::cout << "ref-cmp: " <<  ref << " - " << cmp << std::endl;
                    if (ref == cmp)
                    {
                        isValidSubstr = true;
                        k++;
                        continue;
                    }
                    isValidSubstr = false;
                    break;
                }
            }
        }
        if (isValidSubstr){
            // std::cout << "Add i to List: " << i << std::endl;
            storeList.push_back(i);
            isValidSubstr = false;
        }
    }
}

void extractStartEndFromRange(std::vector<long long> &storeList, std::string range)
{
    std::string start;
    std::string end;
    size_t index = range.find('-');
    start = range.substr(0, index);
    end = range.substr(index + 1);
    // part1_findInvalidID(storeList, start, end);
    part2_findNewInvalidID(storeList, start, end);
}