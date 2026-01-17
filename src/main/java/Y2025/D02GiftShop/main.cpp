#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Utils.hpp"

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
                rangelist.push_back(token); //read individual range to a list
            }
        }
        std::cout << "done" << std::endl;
        
    }
    for(std::string it : rangelist){
        extractStartEndFromRange(invalidIDList, it);    //extract start and end from each range
    }

    long long sum = 0;

    for(long long it : invalidIDList){
        sum += it;
    }

    std::cout << "Total sum of all invalid IDs: " << sum << std::endl;

    return 0;
}