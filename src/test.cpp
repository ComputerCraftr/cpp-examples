// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

template <typename T>
static std::string VecToString(const std::vector<T>& vec)
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

template <typename T>
static std::string LstToString(const std::list<T>& lst)
{
    std::string result = "{";

    if (!lst.empty()) {
        std::list<size_t>::const_iterator lastElem = lst.cend();
        --lastElem;
        for (std::list<size_t>::const_iterator it = lst.cbegin(); it != lastElem; ++it) {
            result += std::to_string(*it) + ", ";
        }
        result += std::to_string(lst.back());
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

    //const std::string testStr = "aaaabaaasaabaaaabaabasaa";
    //const std::string subStr = "abaa";
    //const std::string testStr = "PARTICIPATE IN PARTICIPATE PARTICIPATE PARTICIPATE IN PARACHUTE PARACHUTE PARACHUTEPARTICIPATE IN PARACHUTEPARTICIPATE IN PARACHUTE PARACHUTE PARACHUTE";
    //const std::string subStr = "PARTICIPATE IN PARACHUTE";
    //const std::string testStr = "AABAACAADAABAABA";
    //const std::string subStr = "AABA";
    //const std::string testStr = "abracadabra";
    //const std::string subStr = "abr";
    const std::string testStr = "mmommommy";
    const std::string subStr = "mommy";

    const std::list<size_t> matches = FindSubStrMatches(testStr, subStr);
    printf("Found substring match at positions = %s\n", LstToString(matches).c_str());
}
