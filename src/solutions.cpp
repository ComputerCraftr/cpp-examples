// Copyright (c) 2022 John "ComputerCraftr" Studnicka

#include <solutions.h>

#include <algorithm>
#include <cstdint>
#include <limits>
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
