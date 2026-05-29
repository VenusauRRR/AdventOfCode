// #ifndef UTILS_HPP
// #define UTILS_HPP

// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <algorithm>

// struct JunctionBox
// {
//     int x;
//     int y;
//     int z;
// };

// struct Distance
// {
//     JunctionBox b1;
//     JunctionBox b2;
//     double distance;
// };

// bool isBoxSame(JunctionBox a, JunctionBox b)
// {
//     return a.x == b.x && a.y == b.y && a.z == b.z;
// }

// class Circuit
// {
// private:
//     std::vector<JunctionBox> junctionBoxes;

// public:
//     Circuit() {};

//     void addBox(JunctionBox &b)
//     {
//         junctionBoxes.push_back(b);
//     }

//     void printCircuitList()
//     {
//         std::cout << "Circuit:-" << std::endl;
//         for (auto it : junctionBoxes)
//         {
//             std::cout << it.x << "," << it.y << "," << it.z << std::endl;
//         }
//     }

//     std::vector<JunctionBox> *getAllBoxes()
//     {
//         return &junctionBoxes;
//     }

//     JunctionBox getBox(int index)
//     {
//         return junctionBoxes.at(index);
//     }
// };

// class DistanceCollection
// {
// private:
//     std::vector<Distance> distanceList;

// public:
//     void sortDistanceByAscending()
//     {
//         std::sort(distanceList.begin(), distanceList.end(), [](Distance &a, Distance &b)
//                   { return a.distance < b.distance; });
//     }

//     void printDistanceCollection()
//     {
//         std::cout << "Distance collection:-" << std::endl;
//         for (auto it : distanceList)
//         {
//             std::cout << "(" << it.b1.x << "," << it.b1.y << "," << it.b1.z << ")";
//             std::cout << "(" << it.b2.x << "," << it.b2.y << "," << it.b2.z << ")";
//             std::cout << "=" << it.distance << std::endl;
//         }
//     }

//     void formCircuit(std::vector<Circuit> &circuitList, Distance a)
//     {
//         for (size_t i = 0; i < circuitList.size(); i++)
//         {
//             for (size_t j = 0; j < circuitList.at(i).getAllBoxes()->size(); j++)
//             {
//                 if (isBoxSame(a.b1, circuitList.at(i).getBox(j)))
//                 {
//                     circuitList.at(i).addBox(a.b1);
//                     return;
//                 }
//                 else if (isBoxSame(a.b1, circuitList.at(i).getBox(j)))
//                 {
//                     circuitList.at(i).addBox(a.b2);
//                     return;
//                 }
//             }+
//         }
//     }
// };

// #endif