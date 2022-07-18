// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

std::string VecToString(const std::vector<int>& vec)
{
    std::string result = "{";

    if (!vec.empty()) {
        const size_t end = vec.size() - 1;
        for (size_t i = 0; i != end; ++i) {
            result += std::to_string(vec.at(i)) + ", ";
        }
        result += std::to_string(vec.at(end));
    }

    result += "}";
    return result;
}

std::string VecToString(const std::vector<size_t>& vec)
{
    std::string result = "{";

    if (!vec.empty()) {
        const size_t end = vec.size() - 1;
        for (size_t i = 0; i != end; ++i) {
            result += std::to_string(vec.at(i)) + ", ";
        }
        result += std::to_string(vec.at(end));
    }

    result += "}";
    return result;
}

std::vector<int> GenerateTestVec()
{
    constexpr int size = 100;
    constexpr int range = 100; // Must be at least half of size to produce enough unique values to fill the set
    std::unordered_set<int> data;

    while (data.size() < size) {
        const int randTemp = rand() % (2 * range + 1) - range; // -range to range
        data.insert(randTemp); // Every inserted int is unique
    }

    std::vector<int> result(data.begin(), data.end());
    std::sort(result.begin(), result.end());

    return result;
}

void BenchWithTestVec()
{
    constexpr int testDataSize = 1000000;
    std::vector<std::vector<int>> testData;
    testData.reserve(testDataSize);

    for (int i = 0; i < testDataSize; ++i) {
        testData.push_back(GenerateTestVec());
    }

    int64_t start = clock();

    for (int i = 0; i < testDataSize; ++i) {
        FirstValueEqualToIndex(testData.at(i));
    }

    int64_t end = clock();
    printf("runtime = %lius\n", (end - start) * 1000000 / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[])
{
    const int64_t nTime = time(nullptr);
    srand(nTime);

    constexpr int testCases = 2;
    const std::vector<int> testVecArr[testCases] = {
        GenerateTestVec(),
        GenerateTestVec()
    };

    for (int i = 0; i < testCases; ++i) {
        printf("FirstValueEqualToIndex %s = %i\n", VecToString(testVecArr[i]).c_str(), FirstValueEqualToIndex(testVecArr[i]));
    }

    const std::string testStr = "abracadabra";
    const std::string subStr = "abr";

    const std::vector<size_t> matches = FindSubStrMatches(testStr, subStr);
    printf("Found substring match at positions = %s\n", VecToString(matches).c_str());
}
