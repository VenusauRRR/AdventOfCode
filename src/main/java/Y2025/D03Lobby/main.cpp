#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int part1_findMaxJoltageIndex(std::string input, std::string &digit)
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

int par1_findMaxJoltage(std::string input)
{
    std::string firstDigit, secondDigit;
    int firstIndex = part1_findMaxJoltageIndex(input.substr(0, input.length() - 1), firstDigit);
    std::string temp = input.substr(firstIndex + 1);
    int secondeIndex = part1_findMaxJoltageIndex(temp, secondDigit);
    int maxJoltage = std::stoi(firstDigit + secondDigit);
    return maxJoltage;
}

int part2_findMaxJoltageIndex(std::string input, std::vector<std::string> &list)
{
    int index = -1;
    for (size_t i = 9; i >= 0; i--)
    {
        index = input.find(std::to_string(i));
        if (index >= 0)
        {
            list.push_back(std::to_string(i));
            // std::cout << "i: " << i << std::endl;
            return index;
        }
    }
    return -1;
}

void par2_findMaxJoltage(std::string input, std::vector<std::string> &list, int &counter)
{
    if (counter <= 0)
    {
        return;
    }
    std::string temp = input.substr(0, input.length() - counter + 1);
    int index = part2_findMaxJoltageIndex(temp, list);
    counter--;
    // std::cout << "temp: " << temp << ", index: " << index << ", count: " << counter << std::endl;
    std::string trimString = input.substr(index+1);
    // std::cout << "trim string: " << trimString << std::endl;
    par2_findMaxJoltage(input.substr(index+1), list, counter);
}

int main(void)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    std::vector<long long> joltageList;

    if (inFile.is_open())
    {
        std::cout << "file open success" << std::endl;
        std::string s;
        while (std::getline(inFile, fileLine))
        {
            int count = 12;
            std::vector<std::string> list;
            list.reserve(12);
            // joltageList.push_back(par1_findMaxJoltage(fileLine));
            par2_findMaxJoltage(fileLine, list, count);
            s = "";
            for (auto it : list)
            {
                s += it;
                // std::cout << "it: " << it << std::endl;
            }
            // std::cout << "s: " << s << std::endl;
            long long maxJoltage = std::stoll(s);
            joltageList.push_back(maxJoltage);
        }
    }
    __uint128_t sum = 0;
    for (auto it : joltageList)
    {
        sum += it;
    }
    std::cout << "Total joltage: " << static_cast<long long>(sum) << std::endl;

    return 0;
}