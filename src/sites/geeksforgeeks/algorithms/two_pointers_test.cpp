#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <algorithm>

#include "test_util.h"

// Notes:
// - Is easy to understand.
// - Solves problem within linear time complexity.
// - Techniques:
//   + Collision: 1 array. Each pointer moves from each side to the middle.
//   + Forward: 1 array. Both pointers move forward.
//   + Parallel: 2 arrays. Each array is assigned a pointer.

BOOST_AUTO_TEST_SUITE(test_two_pointers)

void print(std::vector<int>& arr) {
	for (int item : arr) {
		std::cout << item << " ";
	}
	std::cout << "\n";
}

void print(std::vector<std::vector<int>>& arr2d) {
	for (std::vector<int>& arr : arr2d) {
		print(arr);
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

// "Three Sum" problem (LeetCode #15)
// Problem:
// - Given an integer array A.
// - Returns all the triplets A[i], A[j], and A[k] such that:
//   + i != j, i != k, and j != k
//   + A[i] + A[j] + A[k] == 0
// 
// Input: nums { -1 , 0, 1, 2, -1, -4 }
// Output: {-1, -1, 2 }, { -1, 0, 1 }

BOOST_AUTO_TEST_SUITE(three_sum_suite)

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
	// Sort the array
	std::sort(nums.begin(), nums.end());

	// The main loop
	std::vector<std::vector<int>> res;
	for (int i = 0; i < nums.size() - 2; ++i) {
		// Forward the current pointer
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}

		// The two pointers loop
		int start = i + 1;
		int end = nums.size() - 1;
		while (start < end) {
			int sum = nums[i] + nums[start] + nums[end];
			if (sum == 0) {
				res.push_back({nums[i], nums[start], nums[end]});

				// Forward the start pointer
				int tmp = nums[start];
				do {
					++start;
				} while (start < end && nums[start] == tmp);

				// Forward the end pointer
				tmp = nums[end];
				do {
					--end;
				} while (start < end && nums[end] == tmp);
			} else if (sum > 0) {
				--end;
			} else {
				++start;
			}
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(three_sum_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> arr = { -1, 0, 1, 2, -1, -4 };
		auto res = threeSum(arr);
		print(res);
	}

	{ // Test 2
		std::vector<int> arr = { 0, 1, 1 };
		auto res = threeSum(arr);
		print(res);
	}

	{ // Test 3
		std::vector<int> arr = { 0, 0, 0 };
		auto res = threeSum(arr);
		print(res);
	}

	{ // Test 4
		std::vector<int> arr = { 0, 0, 0, 0 };
		auto res = threeSum(arr);
		print(res);
	}

	{ // Test 5
		std::vector<int> arr = { -1, -1, 0, 0, 1, 1, 2, 2, -1, -1, -4, -4 };
		auto res = threeSum(arr);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()