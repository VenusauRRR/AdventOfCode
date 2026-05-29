#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef struct {
    int nr1;
    int nr2;
    int nr3;
    char sign;
} Formula;

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

void fileReader(std::vector <std::string> &rows)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine))
        {
            rows.push_back(fileLine);
        }
    }
    inFile.close();
}

void findSymbolAndItsIndex(std::string &signRow, std::vector <char> &rowSign){
    int len = signRow.length();
    for (size_t i = 0; i < len; i++)
    {
        if (signRow.at(i)!=' '){
            rowSign.push_back(signRow.at(i));
        }
    }
}

void convertStringToNumber(std::vector <std::string> &rows, std::vector <int> &nrList){
    int len = rows[0].size();
    int row_size = rows.size()-2;
    for (size_t i = 0; i < len; i++)
    {
        std::string s = "";
        long long temp = 0;
        for (size_t j = 0; j <= row_size; j++)
        {
            s = s + rows[j].at(i);
        }
        std::cout << s << std::endl;
        if (isDigit(s)){
            temp = std::stoll(s);
            std::cout << "temp: " << temp << std::endl;
            nrList.push_back(temp);
        } else {
            nrList.push_back(0);
        }
        s = "";
    }
}

unsigned long long doCalculation(std::vector <int> &nrList, std::vector <char> &rowSign){
    int nr_size = nrList.size();
    long long sum = 0;
    int sign_idx = 0;
    long long temp = (rowSign.at(sign_idx) == '+') ? 0 : 1;
    for (size_t i = 0; i < nr_size; i++)
        {
            if (nrList.at(i) != 0 && i != (nr_size -1) ){
                if (rowSign.at(sign_idx) == '+'){
                    temp += nrList.at(i);
                } else {
                    temp *= nrList.at(i);
                }
            } else if (i == nr_size - 1){
                if (rowSign.at(sign_idx) == '+'){
                    temp += nrList.at(i);
                } else {
                    temp *= nrList.at(i);
                }
                sum += temp;
            }
            
            else{
                sum += temp;
                sign_idx++;
                temp = (rowSign.at(sign_idx) == '+') ? 0 : 1;
            }
        }

    return sum;
}

int main(void)
{
    std::vector <std::string> rows;
    std::vector <char> rowSign;
    std::vector <long> rowSign_idx;
    std::vector <int> nrList;
    
    fileReader(rows);
    findSymbolAndItsIndex(rows[rows.size()-1], rowSign);
    convertStringToNumber(rows, nrList);

    long long sum = doCalculation(nrList, rowSign);
    std::cout << "Part 2 sum: " << sum << std::endl;

}