#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include "test_util.h"

// Note: Might need to be used with other data structures.

BOOST_AUTO_TEST_SUITE(test_linked_list_leetcode)

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

// ========================================
// STRINGS
// ========================================

// "Find the Difference" problem (LeetCode #389)
// Problem:
// - You are given two strings s and t.
// - String t is generated by random shuffling string s and then add one more letter at a random position.
// - Return the letter that was added to t.
// Input: s = "abcd", t = "abcde"
// Output: "e"

BOOST_AUTO_TEST_SUITE(find_the_difference_suite)

char findTheDifference(std::string s, std::string t) {
	std::unordered_map<char, int> chars;
	for (char c : s) {
		++chars[c];
	}
	for (char c : t) {
		--chars[c];
		if (chars[c] < 0) {
			return c;
		}
	}
	return ' ';
}

BOOST_AUTO_TEST_CASE(find_the_difference_test) {
	TEST_MARKER();

	{ // Test 1
		std::string s = "abcd";
		std::string t = "abcde";
		std::cout << s << "\n";
		std::cout << t << "\n";
		char res = findTheDifference(s, t);
		std::cout << res << "\n\n";
	}

	{ // Test 2
		std::string s = "abcdefghij";
		std::string t = "hbedcfaijgk";
		std::cout << s << "\n";
		std::cout << t << "\n";
		char res = findTheDifference(s, t);
		std::cout << res << "\n\n";
	}

	{ // Test 3
		std::string s = "aaaaaaa";
		std::string t = "aaaaaaaa";
		std::cout << s << "\n";
		std::cout << t << "\n";
		char res = findTheDifference(s, t);
		std::cout << res << "\n\n";
	}

	{ // Test 43
		std::string s = "";
		std::string t = "a";
		std::cout << s << "\n";
		std::cout << t << "\n";
		char res = findTheDifference(s, t);
		std::cout << res << "\n\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Longest Palindrome" problem (LeetCode #409)
// Problem:
// - Given a string s which consists of lowercase or uppercase letters.
// - Return the length of the longest palindrome that can be built with those letters.
// Input: s = "abccccdd"
// Output: 7

BOOST_AUTO_TEST_SUITE(longest_palindrome_suite)

int longestPalindrome(std::string s) {
	std::unordered_map<char, int> chars;
	for (char c : s) {
		++chars[c];
	}
	int res = 0;
	int offset = 0;
	for (auto c : chars) {
		if (c.second % 2 == 0) {
			res += c.second;
		} else {
			res += (c.second - 1);
			offset = 1;
		}
	}
	return res + offset;
}

BOOST_AUTO_TEST_CASE(longest_palindrome_test) {
	TEST_MARKER();

	{ // Test 1
		std::string s = "abccccdd";
		int res = longestPalindrome(s);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::string s = "a";
		int res = longestPalindrome(s);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::string s = "abcabcabc";
		int res = longestPalindrome(s);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Valid Anagram" problem (LeetCode #242)
// Problem:
// - Given two strings s and t.
// - Return true if t is an anagram of s, and false otherwise.
// - An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase.
// Input: s = "anagram", t = "nagaram"
// Output: true

BOOST_AUTO_TEST_SUITE(valid_anagram_suite)

bool isAnagram(std::string s, std::string t) {
	if (s.size() != t.size()) {
		return false;
	}

	std::unordered_map<char, int> chars;
	for (char c : s) {
		++chars[c];
	}
	for (char c : t) {
		--chars[c];
		if (chars[c] < 0) {
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_CASE(valid_anagram_test) {
	TEST_MARKER();

	{ // Test 1
		std::string s = "anagram";
		std::string t = "nagaram";
		std::cout << s << "\n";
		std::cout << t << "\n";
		bool res = isAnagram(s, t);
		std::cout << std::boolalpha << res << "\n\n";
	}

	{ // Test 2
		std::string s = "anagram";
		std::string t = "nagara";
		std::cout << s << "\n";
		std::cout << t << "\n";
		bool res = isAnagram(s, t);
		std::cout << std::boolalpha << res << "\n\n";
	}

	{ // Test 3
		std::string s = "anagrm";
		std::string t = "nagaram";
		std::cout << s << "\n";
		std::cout << t << "\n";
		bool res = isAnagram(s, t);
		std::cout << std::boolalpha << res << "\n\n";
	}

	{ // Test 4
		std::string s = "aabbccddee";
		std::string t = "abcdeabcde";
		std::cout << s << "\n";
		std::cout << t << "\n";
		bool res = isAnagram(s, t);
		std::cout << std::boolalpha << res << "\n\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// ========================================
// ARRAYS
// ========================================

// "Next Greater Element I" problem (LeetCode #496)
// Problem:
// - The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.
// - Given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.
// - For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2.
// - All integers in nums1 and nums2 are unique.
// Input: Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
// Output: Output: [-1,3,-1]

BOOST_AUTO_TEST_SUITE(next_greater_element_suite)

// Note: Could you stack to store unassigned items

std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2) {
	std::unordered_map<int, int> nextGreaterElements;
	for (int i = 0; i < nums2.size(); ++i) {
		nextGreaterElements[nums2[i]] = -1;
		for (int j = i + 1; j < nums2.size(); ++j) {
			if (nums2[j] > nums2[i]) {
				nextGreaterElements[nums2[i]] = nums2[j];
				break;
			}
		}
	}

	for (int i = 0; i < nums1.size(); ++i) {
		nums1[i] = nextGreaterElements[nums1[i]];
	}
	return nums1;
}

BOOST_AUTO_TEST_CASE(next_greater_element_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums1 = { 4, 1, 2 };
		std::vector<int> nums2 = { 1, 3, 4, 2 };
		print(nums1);
		print(nums2);
		std::vector<int> res = nextGreaterElement(nums1, nums2);
		print(res);
		std::cout << "\n";
	}

	{ // Test 2
		std::vector<int> nums1 = { 4, 1, 2, 3 };
		std::vector<int> nums2 = { 1, 3, 4, 2 };
		print(nums1);
		print(nums2);
		std::vector<int> res = nextGreaterElement(nums1, nums2);
		print(res);
		std::cout << "\n";
	}

	{ // Test 3
		std::vector<int> nums1 = { 2, 4 };
		std::vector<int> nums2 = { 1, 2, 3, 4 };
		print(nums1);
		print(nums2);
		std::vector<int> res = nextGreaterElement(nums1, nums2);
		print(res);
		std::cout << "\n";
	}

	{ // Test 4
		std::vector<int> nums1 = { 1, 3 };
		std::vector<int> nums2 = { 4, 3, 2, 1 };
		print(nums1);
		print(nums2);
		std::vector<int> res = nextGreaterElement(nums1, nums2);
		print(res);
		std::cout << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Contains Duplicate II" problem (LeetCode #219)
// Problem:
// - Given an integer array nums and an integer k.
// - Return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
// Input: nums = [1,2,3,1], k = 3
// Output: true

BOOST_AUTO_TEST_SUITE(contains_duplicate_suite)

bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
	std::unordered_map<int, int> map;
	for (int i = 0; i < nums.size(); ++i) {
		if (map.find(nums[i]) != map.end()) {
			if (i - map[nums[i]] <= k) {
				return true;
			}
		}
		map[nums[i]] = i;
	}
	return false;
}

BOOST_AUTO_TEST_CASE(contains_duplicate_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 2, 3, 1 };
		int k = 3;
		bool res = containsNearbyDuplicate(nums, k);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 2
		std::vector<int> nums = { 1, 2, 3, 4, 1 };
		int k = 3;
		bool res = containsNearbyDuplicate(nums, k);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 3
		std::vector<int> nums = { 1, 2, 3, 4, 2, 1 };
		int k = 3;
		bool res = containsNearbyDuplicate(nums, k);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 4
		std::vector<int> nums = { 1, 2, 3, 4, 5, 6 };
		int k = 0;
		bool res = containsNearbyDuplicate(nums, k);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 5
		std::vector<int> nums = { 1 };
		int k = 0;
		bool res = containsNearbyDuplicate(nums, k);
		std::cout << std::boolalpha << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Contains Duplicate" problem (LeetCode #217)
// Problem:
// - Given an integer array nums.
// - Return true if any value appears at least twice in the array.
// Input: nums = [1,2,3,1]
// Output: true

BOOST_AUTO_TEST_SUITE(contains_deuplicate_suite)

bool containsDuplicate(std::vector<int>& nums) {
	std::unordered_set<int> set;
	for (int num : nums) {
		if (set.count(num) == 0) {
			set.insert(num);
		}
		else {
			return true;
		}
	}
	return false;
}

BOOST_AUTO_TEST_CASE(contains_deuplicate_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 2, 3, 1 };
		bool res = containsDuplicate(nums);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 2
		std::vector<int> nums = { 1, 2, 3, 4 };
		bool res = containsDuplicate(nums);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 3
		std::vector<int> nums = { 1 };
		bool res = containsDuplicate(nums);
		std::cout << std::boolalpha << res << "\n";
	}

	{ // Test 4
		std::vector<int> nums = { 1, 1, 1, 3, 3, 4, 3, 2, 4, 2 };
		bool res = containsDuplicate(nums);
		std::cout << std::boolalpha << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()


// "Group Anagrams" problem (LeetCode #49)
// Problem:
// - Given an array of strings strs.
// - Group the anagrams together.
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

BOOST_AUTO_TEST_SUITE(group_anagrams_suite)

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
	std::unordered_map<std::string, std::vector<std::string>> map;
	for (std::string& str : strs) {
		std::string strKey = str;
		std::sort(strKey.begin(), strKey.end());
		map[strKey].push_back(std::move(str));
	}
	std::vector<std::vector<std::string>> res;
	for (auto& pair : map) {
		res.push_back(std::move(pair.second));
	}
	return res;
}

BOOST_AUTO_TEST_CASE(group_anagrams_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<std::string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
		std::cout << "Strings:\n";
		print(strs);
		std::vector<std::vector<std::string>> res = groupAnagrams(strs);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}

	{ // Test 2
		std::vector<std::string> strs = { "" };
		std::cout << "Strings:\n";
		print(strs);
		std::vector<std::vector<std::string>> res = groupAnagrams(strs);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}

	{ // Test 3
		std::vector<std::string> strs = { "a", "b", "c", "d" };
		std::cout << "Strings:\n";
		print(strs);
		std::vector<std::vector<std::string>> res = groupAnagrams(strs);
		std::cout << "Result:\n";
		print(res);
		std::cout << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Valid Sudoku" problem (LeetCode #36)
// Problem:
// - Determine if a 9 x 9 Sudoku board is valid.
// - Only the filled cells need to be validated.
// - Note: A Sudoku board (partially filled) could be valid but is not necessarily solvable.
// Input: board = 
// [["5", "3", ".", ".", "7", ".", ".", ".", "."]
// , ["6", ".", ".", "1", "9", "5", ".", ".", "."]
// , [".", "9", "8", ".", ".", ".", ".", "6", "."]
// , ["8", ".", ".", ".", "6", ".", ".", ".", "3"]
// , ["4", ".", ".", "8", ".", "3", ".", ".", "1"]
// , ["7", ".", ".", ".", "2", ".", ".", ".", "6"]
// , [".", "6", ".", ".", ".", ".", "2", "8", "."]
// , [".", ".", ".", "4", "1", "9", ".", ".", "5"]
// , [".", ".", ".", ".", "8", ".", ".", "7", "9"]]
// Output: true

BOOST_AUTO_TEST_SUITE(valid_sudoku_suite)

bool isValidSudoku(std::vector<std::vector<char>>& board) {
	std::unordered_set<char> set;

	// Check all the rows
	for (int r = 0; r < 9; ++r) {
		set.clear();
		for (int c = 0; c < 9; ++c) {
			char ch = board[r][c];
			if (ch != '.') {
				if (set.count(ch) > 0) {
					return false;
				}
				set.insert(ch);
			}
		}
	}

	// Check all the columns
	for (int c = 0; c < 9; ++c) {
		set.clear();
		for (int r = 0; r < 9; ++r) {
			char ch = board[r][c];
			if (ch != '.') {
				if (set.count(ch) > 0) {
					return false;
				}
				set.insert(ch);
			}
		}
	}

	// Check all the squares
	for (int R = 0; R < 3; ++R) {
		for (int C = 0; C < 3; ++C) {
			set.clear();
			for (int r = 0; r < 3; ++r) {
				for (int c = 0; c < 3; ++c) {
					char ch = board[R * 3 + r][C * 3 + c];
					if (ch != '.') {
						if (set.count(ch) > 0) {
							return false;
						}
						set.insert(ch);
					}
				}
			}
		}
	}

	return true;
}

BOOST_AUTO_TEST_CASE(valid_sudoku_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<std::vector<char>> board = {
			{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
			{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
			{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
			{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
			{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
			{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
			{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
			{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
			{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }
		};
		std::cout << "Board:\n";
		print(board);
		bool res = isValidSudoku(board);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
	}

	{ // Test 2
		std::vector<std::vector<char>> board = {
			{ '8', '3', '.', '.', '7', '.', '.', '.', '.' },
			{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
			{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
			{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
			{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
			{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
			{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
			{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
			{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }
		};
		std::cout << "Board:\n";
		print(board);
		bool res = isValidSudoku(board);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
	}

	{ // Test 3
		std::vector<std::vector<char>> board = {
			{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
			{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
			{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
			{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
			{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
			{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
			{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
			{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
			{ '.', '.', '.', '.', '8', '.', '.', '7', '2' }
		};
		std::cout << "Board:\n";
		print(board);
		bool res = isValidSudoku(board);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()