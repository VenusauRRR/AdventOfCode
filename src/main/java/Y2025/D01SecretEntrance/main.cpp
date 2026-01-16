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

bool isZero(int number){
    return number==0;
}

void part2_rotateTheSafeAndCountClicks(int &init, int &counter, char direction, std::string move)
{
    int origin = init;
    std::cout << "origin: " << init << std::endl;
    int steps = std::stoi(move);
    std::cout << "steps: " << steps << std::endl;
    if (direction == 'L'){
        init -= steps;
        std::cout << "after steps: " << init << std::endl;
        if (init > 0){
            std::cout << "init >0: " << init << std::endl;
            return;
        } else if (init%100 == 0){
            counter = counter + 1 + (init/100);

            std::cout << "couter when init=0: " << counter << std::endl;
        } else {
            // if (init < 0)
            
            counter = counter + 1 + ((steps-origin)/100);
            if (origin==0){
                counter--;
            }
            init %= 100;
            init += 100;
            std::cout << "init<0: " << init << std::endl;
            std::cout << "counter when init<0: " << counter << std::endl;
        }
    } else {
        init += steps;
        std::cout << "after steps: " << init << std::endl;
        if (init < 100){
            std::cout << "init<100: " << init << std::endl;
            return;
        } else if (init%100==0)
        {
            counter += init/100;
            init = 0;
            std::cout << "couter when init=0: " << counter << std::endl;
            std::cout << "init=0: " << init << std::endl;
        } else {
            // if (init > 100)
            counter = counter + init/100;
            init = init%100;
            std::cout << "init>0: " << init << std::endl;
            std::cout << "counter when init>0: " << counter << std::endl;
        }
    }
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
    std::cout << "Total count for Point to 0: " << countLeftPointAt0 << std::endl;
    return 0;
}