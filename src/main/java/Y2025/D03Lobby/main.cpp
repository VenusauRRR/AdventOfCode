#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int findMaxJoltageIndex(std::string input, std::string &digit)
{
    int index = -1;
    for (size_t i = 9; i >= 0; i--)
    {
        index = input.find(std::to_string(i));
        if (index >= 0)
        {
            digit = std::to_string(i);
            return index;
        }
    }
    return -1;
}

int findMaxJoltage(std::string input)
{
    std::string firstDigit, secondDigit;
    int firstIndex = findMaxJoltageIndex(input.substr(0, input.length() - 1), firstDigit);
    std::string temp = input.substr(firstIndex + 1);
    int secondeIndex = findMaxJoltageIndex(temp, secondDigit);
    int maxJoltage = std::stoi(firstDigit + secondDigit);
    return maxJoltage;
}

int main(void)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    std::vector<int> joltageList;

    if (inFile.is_open())
    {
        std::cout << "file open success" << std::endl;
        while (std::getline(inFile, fileLine))
        {
            joltageList.push_back(findMaxJoltage(fileLine));
        }
    }
    long sum = 0;
    for (int it : joltageList)
    {
        sum += it;
    }
    std::cout << "Total joltage: " << sum << std::endl;

    return 0;
}