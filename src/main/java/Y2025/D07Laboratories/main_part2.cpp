#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

void fileReader(std::vector<std::string> &strList)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine))
        {
            strList.push_back(fileLine);
        }
    }
    inFile.close();
}

void findLetterSIndex(std::vector<std::string> &strList, std::vector<int> &idxList, int &idx_init)
{
    int len = strList[0].size();
    for (size_t i = 0; i < len; i++)
    {
        if (strList[0].at(i) == 'S')
        {
            idx_init = i;
            idxList.push_back(idx_init);
            return;
        }
    }
}

bool ifIndexNotExist(int idx, std::vector<int> &idxList)
{
    auto it = std::find_if(idxList.begin(), idxList.end(), [idx](int p)
                           { return p == idx; });
    return it == idxList.end();
}

// void recursion(std::string s, int idx, std::vector<int> &newIdxList, long long &totalTimeline)
// {
//     int idxSplit_L, idxSplit_R;

//     if (s.at(idx) == '^')
//     {
//         idxSplit_L = idx - 1;
//         idxSplit_R = idx + 1;
//         if (idxSplit_L >= 0)
//         {
//             newIdxList.push_back(idxSplit_L);
//         }
//         if (idxSplit_R < s.size())
//         {
//             newIdxList.push_back(idxSplit_R);
//         }
//     }
//     else
//     {
//         newIdxList.push_back(idx);
//     }
// }

void recursion_new(std::vector<std::string> &inputList, int &inputRowSize, int &inputColumnSize, int startRow, int &idx_S_init, long long &totalTimeLine)
{
    // std::cout << "i am here" << std::endl;
    if (startRow > inputRowSize - 1)
    {
        return;
    }
    // if (totalTimeLine % 2 == 0)
    // {
    //     std::cout << totalTimeLine << ", start Row: " << startRow << ", index: " << idx_S_init << std::endl;
    // }
    int idxSplit_L, idxSplit_R;

    if (inputList.at(startRow).at(idx_S_init) == '^')
    {
        idxSplit_L = idx_S_init - 1;
        idxSplit_R = idx_S_init + 1;
        totalTimeLine++;

        if (idxSplit_L >= 0)
        {
            recursion_new(inputList, inputRowSize, inputColumnSize, startRow + 2, idxSplit_L, totalTimeLine);
        }
        if (idxSplit_R < inputColumnSize)
        {
            recursion_new(inputList, inputRowSize, inputColumnSize, startRow + 2, idxSplit_R, totalTimeLine);
        }
    }
    else
    {
        recursion_new(inputList, inputRowSize, inputColumnSize, startRow + 2, idx_S_init, totalTimeLine);
    }
}

int main(void)
{

    std::vector<std::string> strList;
    std::vector<int> idxList;
    int idx_init;
    long long totalTimeline = 1;

    fileReader(strList);
    findLetterSIndex(strList, idxList, idx_init);
    int strListRowSize = strList.size();
    int strListColumnSize = strList.at(0).size();

    recursion_new(strList, strListRowSize, strListColumnSize, 2, idx_init, totalTimeline);

    std::cout
        << "part 2 total timeline count: " << totalTimeline << std::endl;

    return 0;
}