#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_binary_search)

// "Binary Search" problem (LeetCode #704)
// Problem:
// - Given an array of integers nums which is sorted in ascending order, and an integer target.
// - Write a function to search target in nums.
// - If target exists, then return its index. Otherwise, return -1.
// Input: nums = [-1,0,3,5,9,12], target = 9
// Output: 4

BOOST_AUTO_TEST_SUITE(binary_search_suite)

int search(std::vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return -1;
}

BOOST_AUTO_TEST_CASE(binary_search_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { -1, 0, 3, 5, 9, 12 };
		int target = 9;
		int res = search(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::vector<int> nums = { -1, 0, 3, 5, 9, 12 };
		int target = 2;
		int res = search(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::vector<int> nums = { 1 };
		int target = 1;
		int res = search(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 4
		std::vector<int> nums = { 1 };
		int target = 2;
		int res = search(nums, target);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Search Insert Position" problem (LeetCode #35)
// Problem:
// - Given a sorted array of distinct integers and a target value.
// - Return the index if the target is found.
// - If not, return the index where it would be if it were inserted in order.
// Input: nums = [1,3,5,6], target = 2
// Output: 1

BOOST_AUTO_TEST_SUITE(search_insert_position_suite)

int searchInsert(std::vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return left;
}

BOOST_AUTO_TEST_CASE(search_insert_position_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { -1, 0, 3, 5, 9, 12 };
		int target = 9;
		int res = searchInsert(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::vector<int> nums = { -1, 0, 3, 5, 9, 12 };
		int target = 2;
		int res = searchInsert(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::vector<int> nums = { 1 };
		int target = 1;
		int res = searchInsert(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 4
		std::vector<int> nums = { 1 };
		int target = 2;
		int res = searchInsert(nums, target);
		std::cout << res << "\n";
	}

	{ // Test 5
		std::vector<int> nums = { 2, 3, 4, 5 };
		int target = 1;
		int res = searchInsert(nums, target);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()