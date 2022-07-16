// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <iostream>
#include <string>
#include <vector>

std::string VecToString(const std::vector<int>& intVec)
{
    std::string result = "{";

    if (!intVec.empty()) {
        const size_t end = intVec.size() - 1;
        for (size_t i = 0; i != end; ++i) {
            result += std::to_string(intVec.at(i)) + ", ";
        }
        result += std::to_string(intVec.at(end));
    }

    result += "}";
    return result;
}

int main(int argc, char *argv[])
{
    constexpr int testCases = 15;
    std::vector<int> testVecArr[testCases] = {
        {},
        {-3, 0, 2, 34},
        {1, 7, 9, 13},
        {0, 1, 2, 3},
        {-1, 1, 2, 3},
        {-1, 0, 2, 3},
        {-1, 0, 1, 3},
        {-1, 0, 1, 2},
        {-4, -3, -2, -1},
        {-4, -3, -2, 0},
        {-1, 0, 1, 4},
        {-2, -1, 1, 4},
        {-30, -12, -11, -4, 7, 8, 37},
        {-30, -12, -11, -4, 1, 3, 6},
        {-30, -12, -11, -4, -3, 1, 6, 7}
    };

    for (int i = 0; i < testCases; ++i) {
        printf("FirstValueEqualToIndex %s = %i\n", VecToString(testVecArr[i]).c_str(), FirstValueEqualToIndex(testVecArr[i]));
    }
}
