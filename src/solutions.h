// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <list>
#include <string>
#include <vector>

// Given an ordered array of distinct integer numbers, return an element whose value is equal to its index, or -1 if none is found with those conditions.
int FirstValueEqualToIndex(const std::vector<int>& intVec);

// Given an input text string and a simple text pattern, find the starting indices of all matches of the pattern in the input text string.
std::list<size_t> FindSubStrMatches(const std::string& str, const std::string& substr);

// Given an array of integer numbers, arrange the elements of the array in a way that forms the highest possible number. For example, given [10, 7, 76, 415], you should return 77641510.
uint64_t LargestIntFromArrangement(const std::vector<uint32_t>& intVec);
