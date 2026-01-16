#include <iostream>
#include <fstream>
#include <string>

void part1_rotateTheSafe(int &init, int &counter, char direction, std::string move){
    if (direction == 'L'){
        init -= std::stoi(move)%100;
        if (init < 0) init += 100;
    } else {
        init += std::stoi(move)%100;
        if (init > 99) init -= 100;
    }
    // std::cout << init << std::endl;
    if (init == 0) counter++;
}

int main(void){
    std::ifstream inFile("input.txt");
    std::string fileLine;
    int countLeftPointAt0 = 0;
    int init = 50;

    if (inFile.is_open()){
        std::cout << "open success" << std::endl;
        while (std::getline(inFile,fileLine))
        {
            part1_rotateTheSafe(init,countLeftPointAt0,fileLine.at(0),fileLine.substr(1));
        }   
    }
    std::cout << "Part 1: Total count for Point to 0: " << countLeftPointAt0 << std::endl;
    return 0;
}