// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_set>
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

std::vector<int> GenerateTestVec()
{
    constexpr int size = 100;
    constexpr int range = 100; // Must be at least half of size to produce enough unique values to fill the set
    std::unordered_set<int> data;

    int randTemp = 0;
    while (data.size() < size) {
        randTemp = rand() % (2 * range + 1) - range; // -range to range
        data.insert(randTemp); // Every inserted int is unique
    }

    std::vector<int> result(data.begin(), data.end());
    std::sort(result.begin(), result.end());

    return result;
}

int main(int argc, char *argv[])
{
    const int64_t nTime = time(nullptr);
    srand(nTime);

    constexpr int testCases = 18;
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
        {-30, -12, -11, -4, -3, 1, 6, 7},
        {},
        GenerateTestVec(),
        GenerateTestVec()
    };

    for (int i = 0; i <= std::numeric_limits<int8_t>::max(); ++i) {
        testVecArr[15].push_back(i - 1);
    }
    testVecArr[15].push_back(static_cast<int>(std::numeric_limits<int8_t>::max()) + 1);

    for (int i = 0; i < testCases; ++i) {
        printf("FirstValueEqualToIndex %s = %i\n", VecToString(testVecArr[i]).c_str(), FirstValueEqualToIndex(testVecArr[i]));
    }
}
