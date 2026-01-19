#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int findMaxJoltageIndex(std::string input, std::string &digit){
    // std::cout << "input: " << input << std::endl;
    int index = -1;
    for (size_t i = 9; i >= 0; i--)
    {
        index = input.find(std::to_string(i));
        if (index >= 0){
            digit = std::to_string(i);
            return index;
        }
    }
    return -1;
}

int main(void){
    std::ifstream inFile("input.txt");
    std::string fileLine;
    std::vector<int> joltageList;

    if (inFile.is_open()){
        std::cout << "file open success" << std::endl;
        while (std::getline(inFile,fileLine))
        {
            // std::cout << fileLine << std::endl;
            std::string firstDigit, secondDigit;
            // std::string temp = fileLine.substr(5);
            int firstIndex = findMaxJoltageIndex(fileLine.substr(0,fileLine.length()-1), firstDigit);
            // std::cout << "first index: " << firstIndex << std::endl;
            std::string temp = fileLine.substr(firstIndex+1);
            // std::cout << "temp: " << temp << std::endl;
            int secondeIndex = findMaxJoltageIndex(temp, secondDigit);
            // std::cout << "index: " << firstIndex << ", 1st digit: " << firstDigit << ", 2nd digit: " << secondDigit << std::endl;
            int maxJoltage = std::stoi(firstDigit+secondDigit);
            // std::cout << maxJoltage << std::endl;
            joltageList.push_back(maxJoltage);
        }
        
    }
    long sum = 0;
    for(int it : joltageList){
        sum += it;
    }
    std::cout << "Total joltage: " << sum << std::endl;
    inFile.close();
    return 0;
}