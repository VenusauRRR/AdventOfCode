#include "Utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

void findInvalidID(std::vector<long long> &storeList, std::string startString, std::string endString){
    long long start = std::stoll(startString);
    long long end = std::stoll(endString);
    for(long long i = start; i <= end; i++){
        std::string s = std::to_string(i);
        int len = s.length();
        if (len%2==0){
            std::string s1 = s.substr(0,len/2);
            std::string s2 = s.substr(len/2);
            if (s1==s2){
                storeList.push_back(i);
            }
        }
    }
}

void extractStartEndFromRange(std::vector<long long> &storeList, std::string range){
    std::string start;
    std::string end;
    size_t index = range.find('-');
    start = range.substr(0,index);
    end = range.substr(index+1);
    findInvalidID(storeList, start, end);
}