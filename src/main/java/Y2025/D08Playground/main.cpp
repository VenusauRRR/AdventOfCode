#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

#define connectionPairs 10
#define inputDataPath "testinput.txt"

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
    JunctionBox *b1;
    JunctionBox *b2;
    double distance;
};

struct Circuit
{
    std::vector<JunctionBox *> boxes;
};

void printCircuitList(std::vector<JunctionBox> &list)
{
    std::cout << "Circuit: " << std::endl;
    for (auto it : list)
    {
        std::cout << "         " << it.x << "," << it.y << "," << it.z << std::endl;
    }
}

void calcuateSeperateTable(std::vector<Distance> &distanceList, std::vector<JunctionBox> &boxList)
{
    for (size_t i = 0; i < boxList.size(); i++)
    {
        for (size_t j = i + 1; j < boxList.size(); j++)
        {
            Distance d;
            d.b1 = &boxList.at(i);
            d.b2 = &boxList.at(j);
            d.distance = boxDistance(*(d.b1), *(d.b2));
            distanceList.push_back(d);
        }
    }
}

bool isBoxExist(JunctionBox *target, JunctionBox *box)
{
    if (target == box)
    {
        return true;
    }
    else
    {
        return false;
    };
}

void updateCircuitList(std::vector<Circuit> &circuitList, std::vector<Distance> &distanceList)
{
    Circuit *circuit_box1, *circuit_box2;

    for (size_t i = 0; i < distanceList.size(); i++)
    {

        if (circuitList.size() == 0)
        {
            Circuit temp;
            temp.boxes.push_back(distanceList.at(i).b1);
            temp.boxes.push_back(distanceList.at(i).b2);
            circuitList.push_back(temp);
            continue;
        }

        bool isBox1Found = false;
        bool isBox2Found = false;

        for (size_t j = 0; j < circuitList.size(); j++)
        {
            for (size_t k = 0; k < circuitList.at(j).boxes.size(); k++)
            {
                if (isBoxExist(circuitList.at(j).boxes.at(k), distanceList.at(i).b1))
                {
                    circuit_box1 = &circuitList.at(j);
                    isBox1Found = true;
                    break;
                }
            }
            if (isBox1Found)
            {
                break;
            }
        }

        for (size_t j = 0; j < circuitList.size(); j++)
        {
            for (size_t k = 0; k < circuitList.at(j).boxes.size(); k++)
            {
                if (isBoxExist(circuitList.at(j).boxes.at(k), distanceList.at(i).b2))
                {
                    circuit_box2 = &circuitList.at(j);
                    isBox2Found = true;
                    break;
                }
            }
            if (isBox2Found)
            {
                break;
            }
        }

        if (isBox1Found && isBox2Found)
        {
            continue;
        }
        else if ((isBox1Found || isBox2Found))
        {
            if (isBox1Found)
            {
                circuit_box1->boxes.push_back(distanceList.at(i).b2);
            }
            else
            {
                circuit_box2->boxes.push_back(distanceList.at(i).b1);
            }
        }
        else
        {
            Circuit temp;
            temp.boxes.push_back(distanceList.at(i).b1);
            temp.boxes.push_back(distanceList.at(i).b2);
            circuitList.push_back(temp);
        }
    }
}

int main(void)
{
    std::vector<JunctionBox> junctionBoxList;
    std::vector<Distance> distanceList;
    std::vector<Circuit> circuitList;

    std::ifstream inFile(inputDataPath);
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
    //     std::cout << "(" << it.b1->x << "," << it.b1->y << "," << it.b1->z << ")";
    //     std::cout << "(" << it.b2->x << "," << it.b2->y << "," << it.b2->z << ")"
    //               << it.distance << std::endl;
    // }

    std::vector<Distance> d2;

    for (size_t i = 0; i < connectionPairs; i++)
    {
        d2.push_back(distanceList.at(i));
    }

    std::cout << "Distance:-" << std::endl;
    for (auto it : d2)
    {
        std::cout << "(" << it.b1->x << "," << it.b1->y << "," << it.b1->z << ")";
        std::cout << "(" << it.b2->x << "," << it.b2->y << "," << it.b2->z << ")"
                  << it.distance << std::endl;
    }

    updateCircuitList(circuitList, d2);

    // formCircuitList(circuitList, d2);

    std::sort(circuitList.begin(), circuitList.end(), [](const Circuit &a, const Circuit &b)
              { return a.boxes.size() > b.boxes.size(); });

    std::cout << "Circuit List:-" << std::endl;
    for (size_t i = 0; i < circuitList.size(); i++)
    {
        for (size_t j = 0; j < circuitList.at(i).boxes.size(); j++)
        {
            std::cout << "(" << circuitList.at(i).boxes.at(j)->x << ","
                      << circuitList.at(i).boxes.at(j)->y << ","
                      << circuitList.at(i).boxes.at(j)->z << ")" << ",";
        }
        std::cout << "*" << std::endl;
    }

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