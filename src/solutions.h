// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <list>
#include <string>
#include <vector>

// Given an ordered array of distinct integer numbers, return an element whose value is equal to its index, or -1 if none is found with those conditions.
int FirstValueEqualToIndex(const std::vector<int>& intVec);

// Given an input text string and a simple text pattern, find the starting indices of all matches of the pattern in the input text string.
std::list<size_t> FindSubStrMatches(const std::string& str, const std::string& substr);
