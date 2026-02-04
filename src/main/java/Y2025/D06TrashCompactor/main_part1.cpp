#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Row
{
    std::vector<int> numbers;
};

bool isDigit(std::string sign)
{
    try
    {
        std::stoi(sign);
        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
}

// void printList(std::vector<Row> &list)
// {
//     for (auto it : list)
//     {
//         for (size_t i = 0; i < it.numbers.size(); i++)
//         {
//             std::cout << it.numbers.at(i) << " ";
//         }
//         std::cout << std::endl;
//     }
// }

void fileReader(std::vector<Row> &list, std::vector<std::string> &signList)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine))
        {
            std::stringstream ss(fileLine);
            std::string token;
            Row r;
            while (ss >> token)
            {
                if (isDigit(token) == false)
                {
                    signList.push_back(token);
                }
                else
                {
                    r.numbers.push_back(std::stoi(token));
                }
            }
            if (isDigit(token) == true){
                list.push_back(r);
            }
        }
    }
}

int main(void)
{
    std::vector<Row> rowList;
    std::vector<std::string> signList;
    fileReader(rowList, signList);
    int col = signList.size();
    int row = rowList.size();
    long long sum = 0;
    for (size_t i = 0; i < col; i++)
    {
        long long tempSum = 0;
        if (signList.at(i) == "*")
        {
            tempSum ++;
            for (size_t j = 0; j < row; j++)
            {
                tempSum *= rowList.at(j).numbers.at(i);
            }
        }
        else
        {
            for (size_t j = 0; j < row; j++)
            {
                tempSum += rowList.at(j).numbers.at(i);
            }
        }

        sum += tempSum;

    }
    std::cout << "part 1 sum: " << sum << std::endl;
    return 0;
}