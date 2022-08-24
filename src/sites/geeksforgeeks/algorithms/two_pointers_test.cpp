#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>

#include "test_util.h"

// Notes:
// - Is easy to understand.
// - Solves problem within linear time complexity.
// - Techniques:
//   + Collision: 1 array. Each pointer moves from each side to the middle.
//   + Forward: 1 array. Both pointers move forward.
//   + Parallel: 2 arrays. Each array is assigned a pointer.

BOOST_AUTO_TEST_SUITE(test_two_pointers)

void print(std::vector<int>& numbers) {
	for (int number : numbers) {
		std::cout << number << " ";
	}
	std::cout << "\n";
}

// "Two Sum" problem (LeetCode #167)
// Problem:
// - Given a sorted array of integers.
// - Find two numbers such that they added up to a specific target number.
// - Return the indices added by 1.
// Input: numbers = { 2, 7, 11, 15 }, target = 9
// Output: { 1, 2 }

BOOST_AUTO_TEST_SUITE(two_sum_suite)

std::vector<int> twoSum(std::vector<int>& numbers, int target) {
	int start = 0;
	int end = numbers.size() - 1;
	while (start < end) {
		int sum = numbers[start] + numbers[end];
		if (sum == target) {
			return { start + 1, end + 1};
		} else if (sum > target) {
			--end;
		} else {
			++start;
		}
	}
	return { -1, -1 };
}

BOOST_AUTO_TEST_CASE(two_sum_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> arr = { 2, 7, 11, 15 };
		int target = 9;
		std::vector<int> res = twoSum(arr, target);
		print(res);
	}

	{ // Test 2
		std::vector<int> arr = { 2, 3, 4 };
		int target = 6;
		std::vector<int> res = twoSum(arr, target);
		print(res);
	}

	{ // Test 3
		std::vector<int> arr = { -1, 0 };
		int target = -1;
		std::vector<int> res = twoSum(arr, target);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()