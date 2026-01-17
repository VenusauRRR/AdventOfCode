#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

void part1_findInvalidID(std::vector<long long> &storeList, std::string startString, std::string endString);
void part2_findNewInvalidID(std::vector<long long> &storeList, std::string startString, std::string endString);

void extractStartEndFromRange(std::vector<long long> &storeList, std::string range);

#endif