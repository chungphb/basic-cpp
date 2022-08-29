#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_hash_leetcode)

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

// "Relative Ranks" problem (LeetCode #506)
// Problem:
// - You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition. 
// - The athletes are placed based on their scores, where the 1st place athlete has the highest score, the 2nd place athlete has the 2nd highest score, and so on.
// - The placement of each athlete determines their rank.
// - Return an array answer of size n where answer[i] is the rank of the ith athlete.
// Input: score = [10,3,8,9,4]
// Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]

BOOST_AUTO_TEST_SUITE(relative_ranks_suite)

std::vector<std::string> findRelativeRanks(std::vector<int>& score) {
	std::unordered_map<int, int> map;
	for (int i = 0; i < score.size(); ++i) {
		map[score[i]] = i;
	}
	std::priority_queue<int> heap;
	for (int val : score) {
		heap.push(val);
	}
	std::vector<std::string> res(score.size());
	int rank = 1;
	while (!heap.empty()) {
		int val = heap.top();
		heap.pop();
		int id = map[val];
		if (rank == 1) {
			res[id] = "Gold Medal";
		} else if (rank == 2) {
			res[id] = "Silver Medal";
		} else if (rank == 3) {
			res[id] = "Bronze Medal";
		} else {
			res[id] = std::to_string(rank);
		}
		++rank;
	}
	return res;
}

BOOST_AUTO_TEST_CASE(relative_ranks_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> score = { 5, 4, 3, 2, 1 };
		std::cout << "Score: ";
		print(score);
		std::vector<std::string> res = findRelativeRanks(score);
		std::cout << "Placement: ";
		print(res);
		std::cout << "\n";
	}

	{ // Test 2
		std::vector<int> score = { 10, 3, 8, 9, 4 };
		std::cout << "Score: ";
		print(score);
		std::vector<std::string> res = findRelativeRanks(score);
		std::cout << "Placement: ";
		print(res);
		std::cout << "\n";
	}

	{ // Test 3
		std::vector<int> score = { 1 };
		std::cout << "Score: ";
		print(score);
		std::vector<std::string> res = findRelativeRanks(score);
		std::cout << "Placement: ";
		print(res);
		std::cout << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()