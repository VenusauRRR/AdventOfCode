#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

// void part1_rotateTheSafe(int &init, int &counter, char direction, std::string move)
// {   
//     int steps = std::stoi(move);
//     if (direction == 'L'){
//         init -= steps%100;
//         if (init < 0) init += 100;
//     } else {
//         init += steps%100;
//         if (init > 99) init -= 100;
//     }
//     // std::cout << init << std::endl;
//     if (init == 0) counter++;

// }

void recursion(int &counter, int number){
    if (number-100 < 0){
        return;
    }
    counter++;
    recursion(counter, number-100);
}

void part2_rotateTheSafeAndCountClicks(int &init, int &counter, char direction, std::string move)
{
    int origin = init;
    std::cout << "origin: " << init << std::endl;
    int steps = std::stoi(move);
    std::cout << "steps: " << steps << std::endl;
    if (direction == 'L'){
        init -= steps;
        std::cout << "after steps to LEFT: " << init << std::endl;
        if (origin > steps){
            return;
        } else if (origin == steps){
            init = 0;
            counter++;
        } else{
            init = (init%100 + 100)%100;
            if (origin != 0){
                counter++;
            }
            recursion(counter, abs(steps-origin));
        }
    } else { //direction == 'R'
        init += steps;
        std::cout << "after steps to RIGHT: " << init << std::endl;
        if (steps+origin < 100){
            return;
        } else if (steps+origin==100){
            init=0;
            counter++;
        } else{
            init %= 100;
            recursion(counter,steps+origin);
        }
    }
    std::cout << "count: " << counter << std::endl;
}

int main(void)
{
    std::ifstream inFile("input.txt");
    std::string fileLine;
    int countLeftPointAt0 = 0;
    int init = 50;

    if (inFile.is_open())
    {
        std::cout << "open success" << std::endl;
        while (std::getline(inFile, fileLine))
        {
            // part1_rotateTheSafe(init, countLeftPointAt0, fileLine.at(0), fileLine.substr(1));
            part2_rotateTheSafeAndCountClicks(init, countLeftPointAt0, fileLine.at(0), fileLine.substr(1));
        }
    }
    inFile.close();
    std::cout << "Total count for Point to 0: " << countLeftPointAt0 << std::endl;
    return 0;
}