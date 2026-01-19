#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int top_L(const std::vector<std::string> &list, int row, int col)
{
    if (row == 0 || col == 0)
    {
        return 0;
    }
    char x = list.at(row - 1).at(col - 1);
    return (x == '@') ? 1 : 0;
}

int top_Mid(const std::vector<std::string> &list, int row, int col)
{
    if (row == 0)
    {
        return 0;
    }
    char x = list.at(row - 1).at(col);
    return x == '@' ? 1 : 0;
}

int top_R(const std::vector<std::string> &list, const int &lineLenght, int row, int col)
{
    if (row == 0 || col == lineLenght - 1)
    {
        return 0;
    }
    char x = list.at(row - 1).at(col + 1);
    return x == '@' ? 1 : 0;
}

int left(const std::vector<std::string> &list, int row, int col)
{
    if (col == 0)
    {
        return 0;
    }
    char x = list.at(row).at(col - 1);
    return x == '@' ? 1 : 0;
}

int right(const std::vector<std::string> &list, const int &lineLenght, int row, int col)
{
    if (col == lineLenght - 1)
    {
        return 0;
    }
    char x = list.at(row).at(col + 1);
    return x == '@' ? 1 : 0;
}

int bottom_L(const std::vector<std::string> &list, const int &lineLenght, int row, int col)
{
    if (row == list.size() - 1 || col == 0)
    {
        return 0;
    }
    char x = list.at(row + 1).at(col - 1);
    return x == '@' ? 1 : 0;
}

int bottom_Mid(const std::vector<std::string> &list, int row, int col)
{
    if (row == list.size() - 1)
    {
        return 0;
    }
    char x = list.at(row + 1).at(col);
    return x == '@' ? 1 : 0;
}

int bottom_R(const std::vector<std::string> &list, const int &lineLenght, int row, int col)
{
    if (row == list.size() - 1 || col == lineLenght - 1)
    {
        return 0;
    }
    char x = list.at(row + 1).at(col + 1);
    return x == '@' ? 1 : 0;
}

int isValidRollPaper(const std::vector<std::string> &list, const int &lineLenght, int row, int col)
{
    int sum = 0;
    sum += top_L(list, row, col) +
           top_Mid(list, row, col) +
           top_R(list, lineLenght, row, col) +
           left(list, row, col) +
           right(list, lineLenght, row, col) +
           bottom_L(list, lineLenght, row, col) +
           bottom_Mid(list, row, col) +
           bottom_R(list, lineLenght, row, col);
    return (sum < 4) ? 1 : 0;
}

void updateList(int &sum, std::vector<std::string> &list, const int &lineLenght, int row, int col)
{
    if (isValidRollPaper(list, lineLenght, row, col) == 1)
    {
        sum += 1;
        list.at(row).at(col)='.';
    }
}

void loop(int &totalSum, std::vector<std::string> &list, const int &lineLenght)
{
    int check = 0;
    for (size_t i = 0; i < list.size(); i++)
    {
        for (size_t j = 0; j < lineLenght; j++)
        {
            if (list.at(i).at(j) == '@')
            {
                updateList(check, list, lineLenght, i, j);
            }
        }
    }
    std::cout << "check: " << check << std::endl;
    if (check == 0){
        return;
    }
    totalSum += check;
    loop(totalSum, list, lineLenght);
}

int main(void)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    int len = 0;
    int totalSum = 0;
    std::vector<std::string> list;

    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine))
        {
            list.push_back(fileLine);
        }
        std::cout << "done" << std::endl;
    }
    len = list.at(0).length();
    loop(totalSum, list, len);
    std::cout << "total paper roll: " << totalSum << std::endl;
    inFile.close();
    return 0;
}