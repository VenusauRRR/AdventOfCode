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
        //convert the integer to a string
        std::string s = std::to_string(i);
        int len = s.length();
        if (len % 2 == 0)
        {
            //split the string into 2 and compare if the substrings are equal
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
    bool isValidSubstr = false;
    for (long long i = start; i <= end; i++)
    {
        std::string s = std::to_string(i);
        int len = s.length();
        for (size_t j = 2; j <= len; j++)  //divide the string from 2 to max as its length
        {
            //if the string length after division is even, go further
            //stop the for loop if the inValidID is found already, ie isValidSubstr = true
            if (len % j == 0 && !isValidSubstr)
            {
                std::string ref = s.substr(0, len / j);
                int k = 1;
                while (k < j)
                {
                    //compare each substring with the first substring, ie. ref
                    std::string cmp = s.substr(k * len / j, len / j);
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
            storeList.push_back(i);
            isValidSubstr = false;
        }
    }
}

void extractStartEndFromRange(std::vector<long long> &storeList, std::string range)
{
    std::string start;
    std::string end;
    //extract the start and end by finding the index of delimilator
    size_t index = range.find('-');
    start = range.substr(0, index);
    end = range.substr(index + 1);
    // part1_findInvalidID(storeList, start, end);
    part2_findNewInvalidID(storeList, start, end);
}