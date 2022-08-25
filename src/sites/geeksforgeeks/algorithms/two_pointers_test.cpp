#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <algorithm>

#include "test_util.h"

// Notes:
// - Is easy to understand.
// - Solve problem within linear time complexity.
// - Techniques:
//   + Collision: 1 array. Each pointer moves from each side to the middle.
//   + Forward: 1 array. Both pointers move forward.
//   + Parallel: 2 arrays. Each array is assigned a pointer.

BOOST_AUTO_TEST_SUITE(test_two_pointers)

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val{ 0 }, next{ nullptr } {}
	ListNode(int x) : val{ x }, next{ nullptr } {}
	ListNode(int x, ListNode* n) : val{ 0 }, next{ n } {}
};


void print(ListNode* head) {
	while (head != nullptr) {
		std::cout << head->val << " ";
		head = head->next;
	}
	std::cout << "\n";
}

void release(ListNode* head) {
	ListNode* cur = nullptr;
	while (head != nullptr) {
		cur = head;
		head = head->next;
		delete cur;
	}
}

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

// ========================================
// COLLISION
// ========================================

// ====================
// Sub type: TWO SUM
// ====================

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
// - Return all the triplets A[i], A[j], and A[k] such that:
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

// "Three Sum Closest" problem (LeetCode #16)
// Problem:
// - Given an integer array A and an integer target.
// - Find three integers in A such that the sum is closest to target.
// - Return the sum of the three integers.
// Input: nums = { -1, 2, 1, -4 }, target = 1
// Output: 2 (-1 + 2 + 1)

BOOST_AUTO_TEST_SUITE(three_sum_closest_suite)

int threeSumClosest(std::vector<int>& nums, int target) {
	// Sort the array
	std::sort(nums.begin(), nums.end());

	// Cache the result
	int res = target;
	int min_diff = INT_MAX;

	// The main loop
	for (int i = 0; i < nums.size() - 2; ++i) {
		int start = i + 1;
		int end = nums.size() - 1;
		while (start < end) {
			int sum = nums[i] + nums[start] + nums[end];
			if (sum == target) {
				return target;
			}

			int diff = std::abs(sum - target);
			if (diff < min_diff) {
				res = sum;
				min_diff = diff;
			}

			// Note: For subarray { x, y, z, t }
			// If (x + t) >= target
			// => (y + t) >= target since y > x
			// => |y + t - target| >= |x + t - target|
			// => The (y, t) pair can't be included in the final answer
			if (sum < target) {
				++start;
			} else {
				--end;
			}
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(three_sum_closest_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> arr = { -1, 2, 1, -4 };
		int target = 1;
		int res = threeSumClosest(arr, target);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::vector<int> arr = { 0, 0, 0 };
		int target = 1;
		int res = threeSumClosest(arr, target);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::vector<int> arr = { 1, 6, 9, 14, 16, 70 };
		int target = 81;
		int res = threeSumClosest(arr, target);
		std::cout << res << "\n";
	}

	{ // Test 4
		std::vector<int> arr = { -111, -111, 3, 6, 7, 16, 17, 18, 19 };
		int target = 13;
		int res = threeSumClosest(arr, target);
		std::cout << res << "\n";
	}

	{ // Test 5
		std::vector<int> arr = { -55, -24, -18, -11, -7, -3, 4, 5, 6, 9, 11, 23, 33 };
		int target = 0;
		int res = threeSumClosest(arr, target);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Valid Triangle Number" problem (LeetCode #611)
// Problem:
// - Given an integer array.
// - Return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
// Input: nums = {2, 2, 3, 4}
// Output: nums = {4, 2, 3, 4}

BOOST_AUTO_TEST_SUITE(valid_triangle_number_suite)

int triangleNumber(std::vector<int>& nums) {
	std::sort(nums.begin(), nums.end());

	int res = 0;
	for (int i = nums.size() - 1; i >= 2; --i) {
		int start = 0;
		int end = i - 1;
		
		while (start < end) {
			int sum = nums[start] + nums[end];
			if (sum <= nums[i]) {
				++start;
			} else {
				res += end - start;
				--end;
			}
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(valid_triangle_number_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> arr = { 2, 2, 3, 4 };
		int res = triangleNumber(arr);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::vector<int> arr = { 4, 2, 3, 4 };
		int res = triangleNumber(arr);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::vector<int> arr = { 2, 2, 3, 3, 3, 4, 4, 5, 5, 5 };
		int res = triangleNumber(arr);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// ====================
// Sub type: PARTITION
// ====================

// "Palindrome" problem (LeetCode #125)
// Problem:
// - Given a string s.
// - Return true if it is a palindrome, or false otherwise.
// Input: s = "A man, a plan, a canal: Panama"
// Output: true

BOOST_AUTO_TEST_SUITE(palindrome_suite)

inline bool isValid(char c) {
	return (c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z');
}

inline bool isCapital(char c) {
	return (c >= 'A' && c <= 'Z');
}

bool isPalindrome(std::string s) {
	int start = 0;
	int end = s.size() - 1;
	while (start < end) {
		while (start < end && !isValid(s[start])) {
			++start;
		}

		while (start < end && !isValid(s[end])) {
			--end;
		}

		if (start >= end) {
			return true;
		}

		char c1 = s[start];
		char c2 = s[end];

		if (isCapital(c1)) {
			c1 += 32;
		}

		if (isCapital(c2)) {
			c2 += 32;
		}

		if (c1 != c2) {
			return false;
		} else {
			++start;
			--end;
		}
	}

	return true;
}

BOOST_AUTO_TEST_CASE(palindrome_test) {
	TEST_MARKER();

	{ // Test 1
		std::string s = "A man, a plan, a canal: Panama";
		if (isPalindrome(s)) {
			std::cout << "\"" << s << "\" is a palindrome\n";
		} else {
			std::cout << "\"" << s << "\" is not a palindrome\n";
		}
	}

	{ // Test 2
		std::string s = "race a car";
		if (isPalindrome(s)) {
			std::cout << "\"" << s << "\" is a palindrome\n";
		}
		else {
			std::cout << "\"" << s << "\" is not a palindrome\n";
		}
	}

	{ // Test 2
		std::string s = "\n\t";
		if (isPalindrome(s)) {
			std::cout << "\"" << s << "\" is a palindrome\n";
		}
		else {
			std::cout << "\"" << s << "\" is not a palindrome\n";
		}
	}

	{ // Test 3
		std::string s = "0 % 1 2 3 4 5 6 7 8 9 9 8 7 6 5 4 3 2 1 # 0";
		if (isPalindrome(s)) {
			std::cout << "\"" << s << "\" is a palindrome\n";
		}
		else {
			std::cout << "\"" << s << "\" is not a palindrome\n";
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Sort Colors" problem (LeetCode #75)
// Problem:
// - Given an array A with n objects colored red, white, or blue.
// - Sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
// Input: nums = { 2, 0, 2, 1, 1, 0 }
// Output: { 0, 0, 1, 1, 2, 2 }

BOOST_AUTO_TEST_SUITE(sort_colors_suite)

void sortColors(std::vector<int>& nums) {
	int start = 0;
	int end = nums.size() - 1;
	for (int num : nums) {
		if (num == 0) {
			++start;
		} else if (num == 2) {
			--end;
		}
	}
	for (int i = 0; i < nums.size(); ++i) {
		if (i < start) {
			nums[i] = 0;
		} else if (i > end) {
			nums[i] = 2;
		} else {
			nums[i] = 1;
		}
	}
}

BOOST_AUTO_TEST_CASE(sort_colors_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> arr = { 2, 0, 2, 1, 1, 0 };
		sortColors(arr);
		print(arr);
	}

	{ // Test 2
		std::vector<int> arr = { 2, 0, 1 };
		sortColors(arr);
		print(arr);
	}

	{ // Test 3
		std::vector<int> arr = { 1, 1, 0, 0, 2, 2, 0, 1, 2 };
		sortColors(arr);
		print(arr);
	}

	{ // Test 4
		std::vector<int> arr = { 0, 0, 0 };
		sortColors(arr);
		print(arr);
	}

	{ // Test 5
		std::vector<int> arr = { 1, 1, 1 };
		sortColors(arr);
		print(arr);
	}

	{ // Test 6
		std::vector<int> arr = { 2, 2, 2 };
		sortColors(arr);
		print(arr);
	}

	{ // Test 6
		std::vector<int> arr = { 1, 2 };
		sortColors(arr);
		print(arr);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// ========================================
// FORWARD
// ========================================

// ====================
// Sub type: WINDOW
// ====================

// "Minimum Size Subarray Sum" problem (LeetCode #209)
// Problem:
// - Given an array of positive integers A and a positive integer target.
// - Return the minimal length of a contiguous subarray of which the sum is greater than or equal to target.
// Input: target = 7, nums = { 2, 3, 1, 2, 4, 3 }
// Output: 2 ([4, 3])

BOOST_AUTO_TEST_SUITE(minimum_size_subarray_suite)

int minSubArrayLen(int target, std::vector<int>& nums) {
	// Initalize the first window
	int start = 0, end = 0;
	int sum = nums[start];
	int min = INT_MAX;
	int res = 0;

	// The main loop
	while (start < nums.size() && end < nums.size()) {
		// Note: Handle when the window size is 1
		if (start == end) {
			if (sum >= target) {
				return 1;
			} else {
				++end;
				if (end < nums.size()) {
					sum += nums[end];
				}
			}
		}

		// Update the window size
		if (sum < target) {
			// Prepare for the next round
			++end;
			if (end < nums.size()) {
				sum += nums[end];
			}
		} else {
			// Update the result
			int cnt = end - start + 1;
			if (cnt < min) {
				min = cnt;
				res = min;
			}

			// Prepare for the next round
			sum -= nums[start];
			++start;
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(minimum_size_subarray_test) {
	TEST_MARKER();

	{ // Test 1
		int target = 7;
		std::vector<int> arr = { 2, 3, 1, 2, 4, 3 };
		int res = minSubArrayLen(target, arr);
		std::cout << res << "\n";
	}

	{ // Test 2
		int target = 4;
		std::vector<int> arr = { 1, 4, 4 };
		int res = minSubArrayLen(target, arr);
		std::cout << res << "\n";
	}

	{ // Test 3
		int target = 11;
		std::vector<int> arr = { 1, 1, 1, 1, 1, 1 };
		int res = minSubArrayLen(target, arr);
		std::cout << res << "\n";
	}

	{ // Test 4
		int target = 2;
		std::vector<int> arr = { 2 };
		int res = minSubArrayLen(target, arr);
		std::cout << res << "\n";
	}

	{ // Test 5
		int target = 2;
		std::vector<int> arr = { 0 };
		int res = minSubArrayLen(target, arr);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Longest Unique Substring" problem (LeetCode #3)
// Problem:
// - Given a string s.
// - Find the length of the longest substring without repeating characters.
// Input: s = "abcabcbb"
// Output: 3

BOOST_AUTO_TEST_SUITE(longest_unique_substring_suite)

int lengthOfLongestSubstring(std::string s) {
	int len = s.length();
	if (len == 0 || len == 1) {
		return len;
	}

	// Initalize the first window
	int start = 0;
	int end = 0;
	int res = 1;
	bool isUnique = true;
	std::unordered_map<char, int> chars;
	chars.emplace(s[start], 1);

	// The main loop
	while (start < len && end < len) {
		// Update the window size
		if (isUnique) {
			// Update the result
			int cnt = end - start + 1;
			if (cnt > res) {
				res = cnt;
			}

			// Prepare for the next round
			++end;
			if (end < len) {
				auto it = chars.find(s[end]);
				if (it == chars.end()) {
					chars.emplace(s[end], 1);
				} else {
					++chars[s[end]];
				}
				isUnique = (chars[s[end]] == 1);
			}
		} else {
			// Prepare for the next round
			--chars[s[start]];
			isUnique = (chars[s[end]] == 1);
			++start;
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(longest_unique_substring_test) {
	TEST_MARKER();

	{ // Test 1
		std::string s = "abcabcbb";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::string s = "bbbbb";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::string s = "pwwkew";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}

	{ // Test 4
		std::string s = "abcdefu";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}

	{ // Test 5
		std::string s = "";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}

	{ // Test 6
		std::string s = "a";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}

	{ // Test 7
		std::string s = "abccbadeffbascbaffcfbfcabdef";
		int res = lengthOfLongestSubstring(s);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Minimum Window Substring" problem (LeetCode #76)
// Problem:
// - Given two strings s and t of lengths m and n respectively.
// - Return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
// - Return the empty string "" if there is no such substring.
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"

BOOST_AUTO_TEST_SUITE(minimum_window_substring_suite)

std::string minWindow(std::string s, std::string t) {
	int sLen = s.length();
	int tLen = t.length();

	// Handle the first window in the main loop
	int start = 0;
	int end = -1;
	std::unordered_map<char, int> chars;
	for (char c : t) {
		if (chars.find(c) == chars.end()) {
			chars.emplace(c, 1);
		} else {
			++chars[c];
		}
	}
	bool isValid = false;

	int min = INT_MAX;
	int min_start = start;
	int min_end = end;

	// The main loop
	while (start < sLen && end < sLen) {
		if (!isValid) {
			// Prepare for the next round
			++end;
			if (end < sLen) {
				auto it = chars.find(s[end]);
				if (it == chars.end()) {
					isValid = false;
				} else {
					--chars[s[end]];
					if (chars[s[end]] <= 0) {
						isValid = true;
						for (auto it = chars.begin(); it != chars.end(); ++it) {
							if (it->second > 0) {
								isValid = false;
								break;
							}
						}
					}
				}
			}
		} else {
			// Update the result
			int cnt = end - start + 1;
			if (cnt < min) {
				min = cnt;
				min_start = start;
				min_end = end;
			}

			// Prepare for the next round
			auto it = chars.find(s[start]);
			if (it == chars.end()) {
				isValid = true;
			} else {
				++chars[s[start]];
				isValid = (chars[s[start]] <= 0);
			}
			++start;
		}
	}
	return s.substr(min_start, min_end - min_start + 1);
}

BOOST_AUTO_TEST_CASE(minimum_window_substring_test) {
	TEST_MARKER();

	{ // Test 1
		std::string s = "ADOBECODEBANC";
		std::string t = "ABC";
		std::string res = minWindow(s, t);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::string s = "a";
		std::string t = "a";
		std::string res = minWindow(s, t);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::string s = "a";
		std::string t = "aa";
		std::string res = minWindow(s, t);
		std::cout << res << "\n";
	}

	{ // Test 4
		std::string s = "ABCDEFGHIJKLMN";
		std::string t = "AM";
		std::string res = minWindow(s, t);
		std::cout << res << "\n";
	}

	{ // Test 5
		std::string s = "aa";
		std::string t = "b";
		std::string res = minWindow(s, t);
		std::cout << res << "\n";
	}

	{ // Test 6
		std::string s = "abc";
		std::string t = "abc";
		std::string res = minWindow(s, t);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Remove Nth Node From End of List" problem (LeetCode #19)
// Problem:
// - Given the head of a linked list.
// - Remove the nth node from the end of the list and return its head.
// Input: head = 1 -> 2 -> 3 -> 4 -> 5, n = 2
// Output: 1 -> 2 -> 3 -> 4

BOOST_AUTO_TEST_SUITE(remove_nth_node_from_the_end_suite)

ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* start = head;
	ListNode* end = head;
	for (int i = 0; i < n; ++i) {
		end = end->next;
	}
	ListNode* prevStart = nullptr;
	while (end != nullptr) {
		prevStart = start;
		start = start->next;
		end = end->next;
	}
	if (start == head) {
		ListNode* next = head->next;
		delete head;
		return next;
	} else {
		prevStart->next = start->next;
		delete start;
		return head;
	}
}

BOOST_AUTO_TEST_CASE(remove_nth_node_from_the_end_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int n = 2;
		print(head);
		head = removeNthFromEnd(head, n);
		print(head);
		release(head);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int n = 1;
		print(head);
		head = removeNthFromEnd(head, n);
		print(head);
		release(head);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int n = 5;
		print(head);
		head = removeNthFromEnd(head, n);
		print(head);
		release(head);
	}

	{ // Test 4
		ListNode* head = new ListNode(1);
		int n = 1;
		print(head);
		head = removeNthFromEnd(head, n);
		print(head);
		release(head);
	}

	{ // Test 5
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		int n = 1;
		print(head);
		head = removeNthFromEnd(head, n);
		print(head);
		release(head);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// ====================
// Sub type: FAST AND SLOW
// ====================

// "Middle of the Linked List" problem (LeetCode #876)
// Problem:
// - Given the head of a singly linked list.
// - Return the middle node of the linked list.
// - If there are two middle nodes, return the second middle node.
// Input: head = 1 -> 2 -> 3 -> 4 -> 5
// Output: 3 -> 4 -> 5

BOOST_AUTO_TEST_SUITE(middle_linked_list_suite)

ListNode* middleNode(ListNode* head) {
	ListNode* fast = head;
	ListNode* slow = head;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

BOOST_AUTO_TEST_CASE(middle_linked_list_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		head->next->next->next->next->next = new ListNode(6);
		print(head);
		ListNode* mid = middleNode(head);
		print(mid);
		release(head);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		print(head);
		ListNode* mid = middleNode(head);
		print(mid);
		release(head);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		print(head);
		ListNode* mid = middleNode(head);
		print(mid);
		release(head);
	}

	{ // Test 4
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		print(head);
		ListNode* mid = middleNode(head);
		print(mid);
		release(head);
	}

	{ // Test 5
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		print(head);
		ListNode* mid = middleNode(head);
		print(mid);
		release(head);
	}

	{ // Test 6
		ListNode* head = new ListNode(1);
		print(head);
		ListNode* mid = middleNode(head);
		print(mid);
		release(head);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()