#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <queue>
#include <deque>
#include <string>
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

// "Count and Say" problem (LeetCode #38)
// Problem:
// - The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
//   + countAndSay(1) = "1"
//   + countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1)
// - For example, the saying and conversion for digit string "3322251" is "23321511".
// - Given a positive integer n, return the nth term of the count-and-say sequence.
// Input: n = 4
// Output: "1211"
// countAndSay(1) = "1"
// countAndSay(2) = say "1" = one 1 = "11"
// countAndSay(3) = say "11" = two 1's = "21"
// countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"

BOOST_AUTO_TEST_SUITE(count_and_say_suite)

std::string countAndSay(int n) {
	if (n == 1) {
		return "1";
	}
	std::string s = countAndSay(n - 1);
	std::string res = "";
	char prev = '0';
	int count;
	for (char c : s) {
		if (c == prev) {
			++count;
		} else {
			if (prev != '0') {
				res += std::to_string(count);
				res += prev;
			}
			count = 1;
			prev = c;
		}
	}
	res += std::to_string(count);
	res += prev;
	return res;
}

BOOST_AUTO_TEST_CASE(count_and_say_test) {
	TEST_MARKER();

	{ // Test 1
		for (int n = 1; n <= 10; ++n) {
			std::cout << "n = " << n << ": " << countAndSay(n) << "\n";
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()