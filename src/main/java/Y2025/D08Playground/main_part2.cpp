#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

#define connectionPairs 0
#define inputDataPath "input.txt"

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

void updateCircuitList(std::vector<Circuit> &circuitList, std::vector<Distance> &distanceList, Distance &last2Boxes)
{
    Circuit *circuit_1, *circuit_2;
    size_t circuitNr_1, circuitNr_2 = -1;
    size_t prevTotalCircuitSize = 0;
    size_t prevSingleCircuitSize = 0;
    bool isSingleCircuitFormed = false;
    bool isLast2BoxesFound = false;

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
                    circuit_1 = &circuitList.at(j);
                    circuitNr_1 = j;
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
                    circuit_2 = &circuitList.at(j);
                    circuitNr_2 = j;
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
            if (circuitNr_1 != circuitNr_2)
            {
                Circuit temp;
                for (size_t i = 0; i < circuit_1->boxes.size(); i++)
                {
                    temp.boxes.push_back(circuit_1->boxes.at(i));
                }
                for (size_t i = 0; i < circuit_2->boxes.size(); i++)
                {
                    temp.boxes.push_back(circuit_2->boxes.at(i));
                }
                if (circuitNr_1 > circuitNr_2)
                {
                    circuitList.erase(circuitList.begin() + circuitNr_1);
                    circuitList.erase(circuitList.begin() + circuitNr_2);
                }
                else
                {
                    circuitList.erase(circuitList.begin() + circuitNr_2);
                    circuitList.erase(circuitList.begin() + circuitNr_1);
                }
                circuitList.push_back(temp);
            }
        }
        else if ((isBox1Found || isBox2Found))
        {
            if (isBox1Found)
            {
                circuit_1->boxes.push_back(distanceList.at(i).b2);
            }
            else
            {
                circuit_2->boxes.push_back(distanceList.at(i).b1);
            }
        }
        else
        {
            Circuit temp;
            temp.boxes.push_back(distanceList.at(i).b1);
            temp.boxes.push_back(distanceList.at(i).b2);
            circuitList.push_back(temp);
        }

        // Part 2: find the last pair of junction boxes that connect all the junction boxes to a single circuit
        if (circuitList.size() == 1 && circuitList.at(0).boxes.size() == prevSingleCircuitSize)
        {
            continue;
        }
        else
        {
            last2Boxes = distanceList.at(i);
        }
        prevSingleCircuitSize = circuitList.at(0).boxes.size();
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

    Distance last2Boxes;

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

    calcuateSeperateTable(distanceList, junctionBoxList);

    std::sort(distanceList.begin(), distanceList.end(), [](const Distance &a, const Distance &b)
              { return a.distance < b.distance; });

    std::vector<Distance> d2;

    for (size_t i = 0; i < connectionPairs; i++)
    {
        d2.push_back(distanceList.at(i));
    }

    updateCircuitList(circuitList, distanceList, last2Boxes);

    std::sort(circuitList.begin(), circuitList.end(), [](const Circuit &a, const Circuit &b)
              { return a.boxes.size() > b.boxes.size(); });

    int sum = 0;
    for (auto it : circuitList)
    {
        sum += it.boxes.size();
    }

    unsigned int multipyXcoordinates = (last2Boxes.b1->x) * (last2Boxes.b2->x);

    std::cout << "Last 2 boxes: (" << last2Boxes.b1->x << "," << last2Boxes.b1->y << "," << last2Boxes.b1->z << ")"
              << "(" << last2Boxes.b2->x << "," << last2Boxes.b2->y << "," << last2Boxes.b2->z << ")" << last2Boxes.distance << std::endl;
    std::cout << "multipy 2 X coordinates: " << multipyXcoordinates << std::endl;

    return 0;
}