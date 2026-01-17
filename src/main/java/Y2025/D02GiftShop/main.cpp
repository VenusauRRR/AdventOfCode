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
    // std::cout << "start: " << start << ", end: " << end << std::endl;
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
    // std::cout << s1 << "," << s2 << std::endl;
}

int main(void){
    std::ifstream inFile("input.txt");
    std::string fileLine;
    std::vector<std::string> rangelist;
    std::vector<long long> invalidIDList;
    std::string temp;

    if (inFile.is_open()){
        std::cout << "open file success" << std::endl;
        while (std::getline(inFile,fileLine))
        {
            std::stringstream ss(fileLine);
            std::string token;
            while (std::getline(ss,token,','))
            {
                rangelist.push_back(token);
            }
        }
        std::cout << "done" << std::endl;
        
    }
    for(std::string it : rangelist){
        // std::cout << it << std::endl;
        extractStartEndFromRange(invalidIDList, it);
    }

    long long sum = 0;

    for(long long it : invalidIDList){
        // std::cout << it << std::endl;
        sum += it;
    }

    std::cout << "Total sum of all invalid IDs: " << sum << std::endl;

    return 0;
}