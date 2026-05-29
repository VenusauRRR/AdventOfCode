#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

void fileReader(std::vector<std::string> &strList){
    std::ifstream inFile("testinput.txt");
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

void findLetterSIndex(std::vector<std::string> &strList, std::vector<int> &idxList, int &idx_init){
    int len = strList[0].size();
    for (size_t i = 0; i < len; i++)
    {
        if (strList[0].at(i) == 'S'){
            idx_init = i;
            idxList.push_back(idx_init);
            return;
        }
    }
}

bool ifIndexNotExist(int idx, std::vector<int> &idxList){
        auto it = std::find_if(idxList.begin(),idxList.end(),[idx](int p){
        return p == idx;
    });
    return it == idxList.end();
}

void recursion(std::string s, int idx, std::vector<int> &newIdxList, long long &totalTimeline){
    int idxSplit_L, idxSplit_R;

    if (s.at(idx) == '^'){
        idxSplit_L = idx -1;
        idxSplit_R = idx +1;
        if (idxSplit_L >= 0){
            newIdxList.push_back(idxSplit_L);
        }
        if (idxSplit_R < s.size()){
            newIdxList.push_back(idxSplit_R);
        }
    } else {
        newIdxList.push_back(idx);
    }
}

int main(void){

    std::vector<std::string> strList;
    std::vector<int> idxList;
    long long countSplit = 0;
    int idx_init;
    long long totalTimeline = 1;

    fileReader(strList);
    findLetterSIndex(strList, idxList, idx_init);

    for (size_t i = 2; i < strList.size(); i=i+2)
    {
        std::vector<int> newIdxList;
        for (size_t j = 0; j < idxList.size(); j++)
        {
            recursion(strList[i], idxList[j], newIdxList, totalTimeline);
        }
        idxList.clear();
        idxList = newIdxList;
        newIdxList.clear();
        // std::cout << "split: ";
        // for (size_t i = 0; i < idxList.size(); i++)
        // {
        //     std::cout << idxList.at(i) << ", ";
        // }
        // std::cout << std::endl;
        
    }
    std::cout << "part 1 count: " << countSplit << std::endl;
    std::cout << "part 2 total timeline count: " << idxList.size() << std::endl;
    //testing

    return 0;
}