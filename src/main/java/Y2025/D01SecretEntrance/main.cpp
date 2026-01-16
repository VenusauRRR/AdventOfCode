#include <iostream>
#include <fstream>
#include <string>

void part1_rotateTheSafe(int &init, int &counter, char direction, std::string move)
{
    int temp = init;
    int steps = std::stoi(move);
    std::cout << "steps: " << steps << std::endl;
    std::cout << "init: " << init << std::endl;
    if (direction == 'L')
    {
        init -= steps;
        std::cout << "init Left 1: " << init << std::endl;
        if (init < 0){
            init %= 100;
            init += 100;
            std::cout << "init Left 2: " << init << std::endl;
        }
    }
    else
    {
        init += steps; 
        std::cout << "init Right 1: " << init << std::endl;
        if (init >= 100){
            init %= 100;
            std::cout << "init Right 2: " << init << std::endl;
        }
    }
    // std::cout << init << std::endl;
    if (init == 0)
        counter++;
    std::cout << "count: " << counter << std::endl;
    std::cout << "init end: " << init << std::endl;
}

// void part2_rotateTheSafeAndCountClicks(int &init, int &counter, char direction, std::string move)
// {
//     int temp = init;
//     std::cout << "init: " << temp << std::endl;
//     int steps = std::stoi(move);
//     std::cout << "step: " << steps << std::endl;
//     if (direction == 'L')
//     {
//         init -= steps;
//         if (init < 0)
//         {
//             counter += 1 + (steps - temp) / 100;
//             if (temp == 0)
//             {
//                 counter--;
//             }
//             std::cout << "count L: " << counter << std::endl;
//             init %= 100;
//             init += 100;
//         }
//     }
//     else
//     {
//         init += steps;
//         if (init > 99)
//         {
//             std::cout << "here init: " << init << std::endl;
//             std::cout << "count here: " << counter << std::endl;
//             counter += 1 + (steps - (100 - temp)) / 100;
//             if (init == 100){
//                 counter--;
//             }
//             std::cout << "count R: " << counter << std::endl;
//             init %= 100;
//         }
//     }
//     if (init == 0)
//     {
//         counter++;
//         std::cout << "count at 0: " << counter << std::endl;
//     }
//     std::cout << "after: " << init << std::endl;
// }

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
            part1_rotateTheSafe(init, countLeftPointAt0, fileLine.at(0), fileLine.substr(1));
            // part2_rotateTheSafeAndCountClicks(init, countLeftPointAt0, fileLine.at(0), fileLine.substr(1));
            std::cout << std::endl;
        }
    }
    std::cout << "Total count for Point to 0: " << countLeftPointAt0 << std::endl;
    return 0;
}