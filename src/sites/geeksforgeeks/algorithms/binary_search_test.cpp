#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_binary_search)

template <typename T>
void print(std::vector<T>& arr) {
	for (int item : arr) {
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

// "Search a 2D Matrix" problem (LeetCode #74)
// Problem:
// - Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix.
// - This matrix has the following properties:
//   + Integers in each row are sorted from left to right.
//   + The first integer of each row is greater than the last integer of the previous row.
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true

BOOST_AUTO_TEST_SUITE(search_2d_matrix_suite)

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
	int m = matrix.size();
	int n = matrix[0].size();
	int left = 0;
	int right = m * n - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int midVal = matrix[mid / n][mid % n];
		if (midVal == target) {
			return true;
		} else if (midVal < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return false;
}

BOOST_AUTO_TEST_CASE(search_2d_matrix_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<std::vector<int>> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } };
		int target = 3;
		bool res = searchMatrix(matrix, target);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 2
		std::vector<std::vector<int>> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } };
		int target = 23;
		bool res = searchMatrix(matrix, target);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 3
		std::vector<std::vector<int>> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } };
		int target = 22;
		bool res = searchMatrix(matrix, target);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 4
		std::vector<std::vector<int>> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } };
		int target = 0;
		bool res = searchMatrix(matrix, target);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 5
		std::vector<std::vector<int>> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } };
		int target = 100;
		bool res = searchMatrix(matrix, target);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 6
		std::vector<std::vector<int>> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 60 } };
		int target = 60;
		bool res = searchMatrix(matrix, target);
		std::cout << std::boolalpha << res << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "First Bad Version" problem (LeetCode #278)
// Problem:
// - Suppose you have n versions [1, 2, ..., n].
// - Find out the first bad one.
// - You are given an API bool isBadVersion(version) which returns whether version is bad.
// Input: n = 5, bad = 4
// Output: 4

BOOST_AUTO_TEST_SUITE(first_bad_version_suite)

bool isBadVersion(int version) {
	return version >= 1;
}

int firstBadVersion(int n) {
	int left = 1;
	int right = n;
	int res = 0;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (isBadVersion(mid)) {
			right = mid - 1;
			res = mid;
		} else {
			left = mid + 1;
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(first_bad_version_test) {
	TEST_MARKER();

	{ // Test 1
		int n = 5;
		int res = firstBadVersion(n);
		std::cout << res << "\n";
	}

	{ // Test 2
		int n = 9;
		int res = firstBadVersion(n);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Find Peak Element" problem (LeetCode #162)
// Problem:
// - Given a 0-indexed integer array nums.
// - Find a peak element, and return its index.
// - If the array contains multiple peaks, return the index to any of the peaks.
// - You may imagine that nums[-1] = nums[n] = -inf.
// - You must write an algorithm that runs in O(log n) time.
// Input: nums = [1,2,3,1]
// Output: 2

BOOST_AUTO_TEST_SUITE(find_peak_element_suite)

int findPeakElement(std::vector<int>& nums) {
	const int SIZE = nums.size();
	if (SIZE == 1) {
		return 0;
	}
	int left = 0;
	int right = SIZE - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (mid > 0 && mid < SIZE - 1) {
			if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
				return mid;
			} else if (nums[mid] < nums[mid + 1]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		} else if (mid == 0) {
			if (nums[mid] > nums[mid + 1]) {
				return mid;
			} else {
				left = mid + 1;
			}
		} else if (mid == SIZE - 1) {
			if (nums[mid] > nums[mid - 1]) {
				return mid;
			}
			else {
				right = mid - 1;
			}
		}
	}

	return -1;
}

BOOST_AUTO_TEST_CASE(find_peak_element_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 2, 3, 1 };
		int res = findPeakElement(nums);
		std::cout << res << std::endl;
	}

	{ // Test 2
		std::vector<int> nums = { 1, 2, 3, 4 };
		int res = findPeakElement(nums);
		std::cout << res << std::endl;
	}

	{ // Test 3
		std::vector<int> nums = { 4, 3, 2, 1 };
		int res = findPeakElement(nums);
		std::cout << res << std::endl;
	}

	{ // Test 4
		std::vector<int> nums = { 1, 2, 1, 3, 5, 6, 4 };
		int res = findPeakElement(nums);
		std::cout << res << std::endl;
	}

	{ // Test 5
		std::vector<int> nums = { 3, 4, 3, 2, 1 };
		int res = findPeakElement(nums);
		std::cout << res << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Search in Rotated Sorted Array" problem (LeetCode #33)
// Problem:
// - There is an integer array nums sorted in ascending order (with distinct values)..
// - Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k.
// - Given the array nums after the possible rotation and an integer target.
// - Return the index of target if it is in nums, or -1 if it is not in nums.
// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4

BOOST_AUTO_TEST_SUITE(search_rotated_sorted_array_suite)

int search(std::vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (target == nums[mid]) {
			return mid;
		}

		if (nums[left] < nums[mid]) {
			if (target == nums[left]) {
				return left;
			} else if (target > nums[left] && target < nums[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		} else { // nums[mid] < nums[right]
			if (target == nums[right]) {
				return right;
			} else if (target > nums[mid] && target < nums[right]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
	}
	return -1;
}

BOOST_AUTO_TEST_CASE(search_rotated_sorted_array_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 4, 5, 6, 7, 0, 1, 2 };
		int target = 0;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 2
		std::vector<int> nums = { 4, 5, 6, 7, 0, 1, 2 };
		int target = 3;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 3
		std::vector<int> nums = { 6, 7, 0, 1, 2, 4, 5 };
		int target = 0;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 4
		std::vector<int> nums = { 6, 7, 0, 1, 2, 4, 5 };
		int target = 3;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 5
		std::vector<int> nums = { 0, 1, 2, 4, 5, 6, 7 };
		int target = 0;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 6
		std::vector<int> nums = { 0, 1, 2, 4, 5, 6, 7 };
		int target = 3;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 7
		std::vector<int> nums = { 2, 4, 5, 6, 7, 0, 1 };
		int target = 0;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 8
		std::vector<int> nums = { 2, 4, 5, 6, 7, 0, 1 };
		int target = 3;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 9
		std::vector<int> nums = { 1 };
		int target = 1;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}

	{ // Test 10
		std::vector<int> nums = { 1 };
		int target = 0;
		print(nums);
		std::cout << target << "\n";
		int res = search(nums, target);
		std::cout << res << "\n\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()