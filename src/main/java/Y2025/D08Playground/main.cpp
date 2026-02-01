#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

// #include "utils.hpp"

struct JunctionBox
{
    int x;
    int y;
    int z;
};

double boxDistance(JunctionBox &a, JunctionBox &b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
}

struct Distance
{
    JunctionBox b1;
    JunctionBox b2;
    double distance;
};

struct Circuit
{
    std::vector<JunctionBox> boxes;
};

void printCircuitList(std::vector<JunctionBox> &list)
{
    std::cout << "Circuit: " << std::endl;
    for (auto it : list)
    {
        std::cout << "         " << it.x << "," << it.y << "," << it.z << std::endl;
    }
}

void calcuateSeperateTable(std::vector<Distance> &list1, std::vector<JunctionBox> &list2)
{
    for (size_t i = 0; i < list2.size(); i++)
    {
        for (size_t j = i + 1; j < list2.size(); j++)
        {
            Distance d;
            d.b1 = list2.at(i);
            d.b2 = list2.at(j);
            d.distance = boxDistance(d.b1, d.b2);
            list1.push_back(d);
        }
    }
}

bool isBoxSame(JunctionBox a, JunctionBox b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

void formCircuitList(std::vector<Circuit> &circuitList, std::vector<Distance> &distanceList)
{
    bool isConnected = false;
    for (size_t i = 0; i < 10; i++)
    {
        if (circuitList.size() == 0)
        {
            Circuit c;
            c.boxes.push_back(distanceList.at(0).b1);
            c.boxes.push_back(distanceList.at(0).b2);
            circuitList.push_back(c);
            continue;
        }
        Distance d = distanceList.at(i);
        std::cout << "b1: " << d.b1.x << "," << d.b1.y << "," << d.b1.z << std::endl;
        std::cout << "b2: " << d.b2.x << "," << d.b2.y << "," << d.b2.z << std::endl;
        for (size_t j = 0; j < circuitList.size(); j++)
        {
            for (size_t k = 0; k < circuitList.at(j).boxes.size(); k++)
            {
                // printCircuitList(circuitList.at(j).boxes);
                if (isBoxSame(circuitList.at(j).boxes.at(k), d.b1))
                {
                    circuitList.at(j).boxes.push_back(d.b2);
                    isConnected = true;
                    break;
                }
                else if (isBoxSame(circuitList.at(j).boxes.at(k), d.b2))
                {
                    circuitList.at(j).boxes.push_back(d.b1);
                    isConnected = true;
                    break;
                }
            }
            if (isConnected)
            {
                break;
            }
        }

        if (isConnected)
        {
            isConnected = false;
        }
        else
        {
            Circuit c;
            c.boxes.push_back(distanceList.at(i).b1);
            c.boxes.push_back(distanceList.at(i).b2);
            circuitList.push_back(c);
        }
        // std::cout << "Circuit after: " << std::endl;
        // for (size_t i = 0; i < circuitList.size(); i++)
        // {
        //     for (size_t j = 0; j < circuitList.at(i).boxes.size(); j++)
        //     {
        //         std::cout << "(" << circuitList.at(i).boxes.at(j).x << ","
        //                   << circuitList.at(i).boxes.at(j).y << ","
        //                   << circuitList.at(i).boxes.at(j).z << ")" << ",";
        //     }
        //     std::cout << "*" << std::endl;
        // }
    }
}

int main(void)
{
    std::vector<JunctionBox> junctionBoxList;
    std::vector<Distance> distanceList;
    std::vector<Circuit> circuitList;

    std::ifstream inFile("testinput.txt");
    std::string fileLine;
    std::string x, y, z;

    if (inFile.is_open())
    {
        while (std::getline(inFile, fileLine))
        {
            std::stringstream ss(fileLine);
            std::getline(ss, x, ',');
            std::getline(ss, y, ',');
            std::getline(ss, z, ',');
            junctionBoxList.push_back({std::stoi(x), std::stoi(y), std::stoi(z)});
        }
    }

    // printCircuitList(junctionBoxList);

    calcuateSeperateTable(distanceList, junctionBoxList);

    std::sort(distanceList.begin(), distanceList.end(), [](const Distance &a, const Distance &b)
              { return a.distance < b.distance; });
    // std::cout << "Distance:-" << std::endl;
    // for (auto it : distanceList)
    // {
    //     std::cout << "(" << it.b1.x << "," << it.b1.y << "," << it.b1.z << ")";
    //     std::cout << "(" << it.b2.x << "," << it.b2.y << "," << it.b2.z << ")"
    //               << it.distance << std::endl;
    // }

    std::vector<Distance> d2;

    for (size_t i = 0; i < 10; i++)
    {
        d2.push_back(distanceList.at(i));
    }

    // std::cout << "Distance:-" << std::endl;
    // for (auto it : d2)
    // {
    //     std::cout << "(" << it.b1.x << "," << it.b1.y << "," << it.b1.z << ")";
    //     std::cout << "(" << it.b2.x << "," << it.b2.y << "," << it.b2.z << ")"
    //               << it.distance << std::endl;
    // }
    formCircuitList(circuitList, d2);

    std::sort(circuitList.begin(), circuitList.end(), [](const Circuit &a, const Circuit &b)
              { return a.boxes.size() > b.boxes.size(); });

    // std::cout << "Circuit List:-" << std::endl;
    // for (size_t i = 0; i < circuitList.size(); i++)
    // {
    //     for (size_t j = 0; j < circuitList.at(i).boxes.size(); j++)
    //     {
    //         std::cout << "(" << circuitList.at(i).boxes.at(j).x << ","
    //                   << circuitList.at(i).boxes.at(j).y << ","
    //                   << circuitList.at(i).boxes.at(j).z << ")" << ",";
    //     }
    //     std::cout << "*" << std::endl;
    // }

    int sum = 0;
    for (auto it : circuitList)
    {
        sum += it.boxes.size();
    }

    std::cout << "Total junction boxes: " << junctionBoxList.size() << std::endl;
    std::cout << "Sum junction boxes in all circuilts: " << sum << std::endl;
    std::cout << "Multipy first 3 largest circuits: "
              << circuitList.at(0).boxes.size() * circuitList.at(1).boxes.size() * circuitList.at(2).boxes.size()
              << std::endl;

    return 0;
}