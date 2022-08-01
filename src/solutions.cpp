// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

// Given an ordered array of distinct integer numbers, return an element whose value is equal to its index, or -1 if none is found with those conditions.
//
// This function will scan through the elements in a vector container to find a value equal to its index number. A binary search
// is used on the sorted vector to determine if any matching values exist and where they are located. The function argument is
// a const reference to the vector to avoid making a copy of a potentially large object. Special consideration needs to be taken
// in case the vector size is larger than the maximum int value to avoid signed integer overflow, which is undefined behavior.
//
// Worst case time complexity: O(log n)
int FirstValueEqualToIndex(const std::vector<int>& intVec)
{
    // One beyond either the last element index or the maximum int value
    const uint64_t size = std::min(static_cast<uint64_t>(intVec.size()), static_cast<uint64_t>(std::numeric_limits<int>::max()) + 1);
    // Either the last element index or the maximum int value because no element can be equal to its index number beyond this point
    int end = size - 1;

    // If the array is empty, then there are no matching values
    // If the last element is less than its index, then every other element must be less than it and therefore will not match
    if (size == 0 || intVec.at(end) < end) {
        return -1;
    }

    // Perform an O(log n) binary search and find the leftmost matching element
    // start = left boundary, middle = middle of array, end = right boundary
    int start = 0;
    while (start != end) {
        // The array is cut in half on each loop
        const int middle = (start + end) / 2;
        if (intVec.at(middle) < middle) {
            // Answer must be in right half
            start = middle + 1;
        } else {
            // Answer must be in left half
            end = middle;
        }
    }

    // Check for match
    if (intVec.at(start) == start) {
        return start;
    } else {
        return -1;
    }
}

// Given an input text string and a simple text pattern, find the starting indices of all matches of the pattern in the input text string.
//
// This function uses the KMP algorithm to find all matches for a substring in a given string. Before scanning the string for
// matches, a partial match table is initialized from the substring so that repeated comparisons can be skipped. The function
// arguments are passed as const references for space efficiency. A list is returned instead of a vector to avoid potentially
// time consuming reallocation operations.
//
// Worst case time complexity: O(n + m) where n is the length of str and m is the length of subStr
std::list<size_t> FindSubStrMatches(const std::string& str, const std::string& subStr)
{
    std::list<size_t> matchingIndices;

    // Can only work with string lengths up to the maximum int64_t value
    const int64_t strLen = std::min(static_cast<int64_t>(str.length()), std::numeric_limits<int64_t>::max());
    const int64_t subStrLen = std::min(static_cast<int64_t>(subStr.length()), std::numeric_limits<int64_t>::max());

    // If either string is empty or subStr is longer than str, then there will be no matches
    if (strLen == 0 || subStrLen == 0 || subStrLen > strLen) {
        return matchingIndices;
    }

    // Keep track of which index we are checking
    int64_t posStr = 0;
    int64_t posSubStr = 0;
    std::vector<int64_t> matchTable;

    // Compute partial match table to optimize searching - this is a deterministic finite automaton which recognizes subStr
    {
        // The partial match table must be computed for every character in subStr plus one extra
        matchTable.reserve(subStrLen + 1);

        // Keep track of how far we have gotten in the table and subStr
        int64_t posTable = 1;
        int64_t posSubStrNext = 0;

        // If the first character doesn't match, then we simply move onto the next character in str
        matchTable.push_back(-1);

        // Fill the rest of the table
        while (posTable < subStrLen) {
            if (subStr.at(posTable) == subStr.at(posSubStrNext)) {
                matchTable.push_back(matchTable.at(posSubStrNext));
            } else {
                matchTable.push_back(posSubStrNext);
                while (posSubStrNext >= 0 && subStr.at(posTable) != subStr.at(posSubStrNext)) {
                    posSubStrNext = matchTable.at(posSubStrNext);
                }
            }

            // Move onto the next character in subStr
            ++posTable;
            ++posSubStrNext;
        }

        // The last element is never -1
        matchTable.push_back(posSubStrNext);
    }

    // Search str for matches - instead of rechecking characters multiple times, a sliding "window" is used while checking against subStr
    while (posStr < strLen) {
        if (str.at(posStr) == subStr.at(posSubStr)) {
            // Current character matches, move onto the next
            ++posStr;
            ++posSubStr;
            if (posSubStr == subStrLen) {
                // Found matching occurrence of subStr
                // Unlike a vector, adding elements to the end of a linked list is always an O(1) constant time operation
                matchingIndices.push_back(posStr - posSubStr);
                // The table cannot return -1 here
                posSubStr = matchTable.at(posSubStr);
            }
        } else {
            // Current character doesn't match, reset position in subStr based on partial match table
            posSubStr = matchTable.at(posSubStr);
            // If the current table value is -1 or 0, then we need to start matching from the beginning of subStr
            if (posSubStr < 0) {
                ++posStr;
                ++posSubStr;
            }
        }
    }

    return matchingIndices;
}
