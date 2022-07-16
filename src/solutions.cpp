// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

// Given an ordered array of distinct integer numbers, return an element whose value is equal to its index, or -1 if none is found with those conditions.
//
// This function will scan through the elements in the vector container starting from the first non negative element to check if
// any values are equal to their index number. In the worst case scenario, each element must be checked at least once, resulting in
// a time complexity of O(n) to perform a linear search. However, we can take advantage of the fact that the input vector will
// already be sorted from least to greatest and skip checking any negative values which will never be equal to their index number.
// A const reference to the vector is used to avoid making a copy of a potentially large object. Special consideration needs to be
// taken in case the vector size is larger than the maximum int value to avoid signed integer overflow, which is undefined behavior.
int FirstValueEqualToIndex(const std::vector<int>& intVec)
{
    // No value equal to index
    if (intVec.empty()) {
        return -1;
    }

    // One beyond either the last element index or the maximum int value because no element can be equal to its index number at or beyond this point
    const uint64_t size = std::min(static_cast<uint64_t>(intVec.size()), static_cast<uint64_t>(std::numeric_limits<int>::max()) + 1);
    // Either the last element index or the maximum int value
    int end = size - 1;
    // First non negative element index
    int start = 0;

    // If the last element is less than its index, then every other element must be less than it and therefore will not match
    if (intVec.at(end) < end) {
        return -1;
    }

    // Perform an O(log n) binary search to find the first possible element value which may match its index number (skip negatives)
    if (intVec.at(start) < 0) {
        int middle = 0;
        while (start != end) {
            middle = (start + end) / 2;
            if (intVec.at(middle) < 0) {
                start = middle + 1;
            } else {
                end = middle;
            }
        }
        // Reset end
        end = size - 1;
        // At this point, start is either the index of 0 or the first positive element
    }

    // Perform an O(n) linear search to check if any element values match their index numbers
    int index = start;
    while (true) {
        // If any element value is greater than its index number, then none of the remaining elements will match because they all must be greater than it (no duplicates)
        if (intVec.at(index) > index) {
            return -1;
        } else if (intVec.at(index) == index) { // Match found
            return index;
        } else if (index == end) { // No match found
            return -1;
        }

        ++index;
    }
}
