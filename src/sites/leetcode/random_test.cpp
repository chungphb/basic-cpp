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

// "Multiply Strings" problem (LeetCode #43)
// Problem:
// - Given two non-negative integers num1 and num2 represented as strings.
// - Return the product of num1 and num2, also represented as a string.
// Input: num1 = "123", num2 = "456"
// Output: "56088"

BOOST_AUTO_TEST_SUITE(multiply_strings_suite)

std::string fix(std::string num) {
	std::string res;
	bool ignore0 = true;
	for (int i = num.size() - 1; i >= 0; --i) {
		if (num[i] == '0' && ignore0) {
			continue;
		}
		ignore0 = false;
		res += num[i];
	}
	return res;
}

std::string multiply(std::string num1, std::string num2) {
	if (num1 == "0" || num2 == "0") {
		return "0";
	}
	int n1 = num1.size();
	int n2 = num2.size();
	int start = 0;
	std::string num(n1 + n2 + 1, '0');
	for (int k1 = n1 - 1; k1 >= 0; --k1) {
		int c1 = num1[k1] - '0';
		int k = start;
		int offset = 0;
		for (int k2 = n2 - 1; k2 >= 0; --k2) {
			int c2 = num2[k2] - '0';
			int sum = (num[k] - '0') + (c1 * c2) + offset;
			num[k] = sum % 10 + '0';
			offset = sum / 10;
			++k;
		}
		if (offset > 0) {
			num[k] = offset + '0';
		}
		++start;
	}
	return fix(num);
}

BOOST_AUTO_TEST_CASE(multiply_strings_test) {
	TEST_MARKER();

	{ // Test 1
		std::string num1 = "2";
		std::string num2 = "3";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 2
		std::string num1 = "2";
		std::string num2 = "5";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 3
		std::string num1 = "123";
		std::string num2 = "456";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 4
		std::string num1 = "99999";
		std::string num2 = "99999";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 5
		std::string num1 = "99";
		std::string num2 = "99999";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 6
		std::string num1 = "99999";
		std::string num2 = "99";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 7
		std::string num1 = "0";
		std::string num2 = "100";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 8
		std::string num1 = "1";
		std::string num2 = "100";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}

	{ // Test 9
		std::string num1 = "9";
		std::string num2 = "8";
		std::string res = multiply(num1, num2);
		std::cout << num1 << " x " << num2 << " = " << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Permutations II" problem (LeetCode #47)
// Problem:
// - Given a collection of numbers, nums, that might contain duplicates.
// - Return all possible unique permutations in any order.
// Input: nums = [1,1,2]
// Output: [[1,1,2],[1,2,1],[2,1,1]]

BOOST_AUTO_TEST_SUITE(permutations_2_suite)

void dfs(std::vector<int>& nums, std::vector<int>& list, std::vector<bool>& visited, std::vector<std::vector<int>>& res) {
	if (list.size() == nums.size()) {
		res.push_back(list);
		return;
	}

	int prev = INT_MAX;
	for (int i = 0; i < nums.size(); ++i) {
		if (visited[i] == true || nums[i] == prev) {
			continue;
		}
		list.push_back(nums[i]);
		visited[i] = true;
		dfs(nums, list, visited, res);
		list.pop_back();
		visited[i] = false;
		prev = nums[i];
	}
}

std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	std::vector<int> list;
	std::vector<bool> visited(nums.size(), false);
	std::vector<std::vector<int>> res;
	dfs(nums, list, visited, res);
	return res;
}

BOOST_AUTO_TEST_CASE(permutations_2_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 1, 2 };
		std::cout << "Nums:\n";
		print(nums);
		std::vector<std::vector<int>> res = permuteUnique(nums);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}

	{ // Test 2
		std::vector<int> nums = { 1, 2, 3, 4 };
		std::cout << "Nums:\n";
		print(nums);
		std::vector<std::vector<int>> res = permuteUnique(nums);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}

	{ // Test 3
		std::vector<int> nums = { 1, 1, 2, 2, 3, 3 };
		std::cout << "Nums:\n";
		print(nums);
		std::vector<std::vector<int>> res = permuteUnique(nums);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}

	{ // Test 4
		std::vector<int> nums = { 1, 1, 1, 1 };
		std::cout << "Nums:\n";
		print(nums);
		std::vector<std::vector<int>> res = permuteUnique(nums);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}

	{ // Test 5
		std::vector<int> nums = { 1 };
		std::cout << "Nums:\n";
		print(nums);
		std::vector<std::vector<int>> res = permuteUnique(nums);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Rotate Image" problem (LeetCode #48)
// Problem:
// - Given an n x n 2D matrix representing an image.
// - Rotate the image by 90 degrees (clockwise).
// - You have to rotate the image in-place.
// Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
// Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

BOOST_AUTO_TEST_SUITE(rotate_image_suite)

void rotate(std::vector<std::vector<int>>& matrix) {
	int n = matrix.size();
	for (int circle = 0; circle < n / 2; ++circle) {
		int low = circle;
		int high = n - circle - 1;
		for (int row = low; row < high; ++row) {
			int tmp = matrix[row][low];
			matrix[row][low] = matrix[high][row];
			matrix[high][row] = matrix[(high + low) - row][high];
			matrix[(high + low) - row][high] = matrix[low][(high + low) - row];
			matrix[low][(high + low) - row] = tmp;
		}
	}
}

BOOST_AUTO_TEST_CASE(rotate_image_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<std::vector<int>> matrix = {
			{ 1, 2, 3 },
			{ 4, 5, 6 },
			{ 7, 8, 9 },
		};
		std::cout << "Before:\n";
		print(matrix);
		rotate(matrix);
		std::cout << "After:\n";
		print(matrix);
		std::cout << "\n";
	}

	{ // Test 2
		std::vector<std::vector<int>> matrix = {
			{ 5, 1, 9, 11 },
			{ 2, 4, 8, 10 },
			{ 13, 3, 6, 7 },
			{ 15, 14, 12, 16 }
		};
		std::cout << "Before:\n";
		print(matrix);
		rotate(matrix);
		std::cout << "After:\n";
		print(matrix);
		std::cout << "\n";
	}

	{ // Test 3
		std::vector<std::vector<int>> matrix = {
			{ 1, 2 },
			{ 3, 4 }
		};
		std::cout << "Before:\n";
		print(matrix);
		rotate(matrix);
		std::cout << "After:\n";
		print(matrix);
		std::cout << "\n";
	}

	{ // Test 4
		std::vector<std::vector<int>> matrix = {
			{ 1 }
		};
		std::cout << "Before:\n";
		print(matrix);
		rotate(matrix);
		std::cout << "After:\n";
		print(matrix);
		std::cout << "\n";
	}

	{ // Test 5
		std::vector<std::vector<int>> matrix = {
			{ 1, 2, 3, 4, 5, 6 },
			{ 1, 2, 3, 4, 5, 6 },
			{ 1, 2, 3, 4, 5, 6 },
			{ 1, 2, 3, 4, 5, 6 },
			{ 1, 2, 3, 4, 5, 6 },
			{ 1, 2, 3, 4, 5, 6 }
		};
		std::cout << "Before:\n";
		print(matrix);
		rotate(matrix);
		std::cout << "After:\n";
		print(matrix);
		std::cout << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()