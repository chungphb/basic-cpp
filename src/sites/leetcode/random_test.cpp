#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_set>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(leetcode_test_random)

template <typename T>
void print(std::vector<T>& arr) {
	for (T item : arr) {
		std::cout << item << " ";
	}
	std::cout << "\n";
}

template <typename T>
void print(std::vector<std::vector<T>>& arr2d) {
	for (std::vector<T>& arr : arr2d) {
		print(arr);
	}
	std::cout << "\n";
}

// "Next Permutation" problem (LeetCode #31)
// Problem:
// - Given an array of integers nums.
// - Find the next permutation of nums.
// Input: nums = [1,2,3]
// Output: [1,3,2]

BOOST_AUTO_TEST_SUITE(next_permutation_suite)

void reverse(std::vector<int>& nums, int left, int right) {
	while (left < right) {
		std::swap(nums[left], nums[right]);
		++left;
		--right;
	}
}

void nextPermutation(std::vector<int>& nums) {
	const int size = nums.size();

	// Find the largest k such that nums[k] < nums[k + 1]
	int k = -1;
	for (int i = 0; i < size - 1; ++i) {
		if (nums[i] < nums[i + 1]) {
			k = i;
		}
	}

	// If such k not exists, reverse the array and return
	if (k == -1) {
		reverse(nums, 0, size - 1);
		return;
	}

	// Find the largest l (l > k) such thats nums[l] > nums[k] 
	int l = -1;
	for (int i = 0; i < size; ++i) {
		if (nums[i] > nums[k]) {
			l = i;
		}
	}

	// Swap nums[l] and nums[k]
	if (l != -1) {
		std::swap(nums[l], nums[k]);
	}

	// Reverse the subarray from k + 1
	reverse(nums, k + 1, size - 1);
}

BOOST_AUTO_TEST_CASE(next_permutation_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 2, 3 };
		print(nums);
		nextPermutation(nums);
		print(nums);
	}

	{ // Test 2
		std::vector<int> nums = { 1, 3, 2 };
		print(nums);
		nextPermutation(nums);
		print(nums);
	}

	{ // Test 3
		std::vector<int> nums = { 3, 2, 1 };
		print(nums);
		nextPermutation(nums);
		print(nums);
	}

	{ // Test 4
		std::vector<int> nums = { 1, 1, 5, 1, 1 };
		print(nums);
		nextPermutation(nums);
		print(nums);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()