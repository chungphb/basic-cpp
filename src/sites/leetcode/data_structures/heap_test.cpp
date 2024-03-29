#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_heap_leetcode)

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

// "Kth Largest Element in a Stream" problem (LeetCode #703)
// Problem:
// - Design a class to find the kth largest element in a stream.
// - Note that it is the kth largest element in the sorted order, not the kth distinct element.
// Input: ["KthLargest", "add", "add", "add", "add", "add"]
// [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
// Output: [null, 4, 5, 5, 8, 8]

BOOST_AUTO_TEST_SUITE(kth_largest_suite)

class KthLargest {
private:
	int _k;
	std::priority_queue<int, std::vector<int>, std::greater<int>> _heap;
public:
	KthLargest(int k, std::vector<int>& nums) {
		_k = k;
		for (int num : nums) {
			_heap.push(num);
		}
		while (_heap.size() > _k) {
			_heap.pop();
		}
	}

	int add(int val) {
		_heap.push(val);
		if (_heap.size() > _k) {
			_heap.pop();
		}
		return _heap.top();
	}
};

BOOST_AUTO_TEST_CASE(kth_largest_test) {
	TEST_MARKER();

	{ // Test 1
		int k = 3;
		std::vector<int> nums = { 4, 5, 8, 2 };
		std::cout << "Nums: ";
		print(nums);
		KthLargest* obj = new KthLargest(k, nums);
		std::vector<int> vals = { 3, 5, 10, 9, 4, 3, 4, 9, 1, 7, 6, 3, 2, 5, 4, 1 };
		for (int val : vals) {
			int res = obj->add(val);
			std::cout << "Add: " << val << ", Extract: " << res << "\n";
		}
		std::cout << "\n";
		delete obj;
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Ugly Number II" problem (LeetCode #264)
// Problem:
// - An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
// - Given an integer n, return the nth ugly number.
// Input: n = 10
// Output: 12

BOOST_AUTO_TEST_SUITE(ugly_number_2_suite)

int nthUglyNumber(int n) {
	int k = 0;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	minHeap.push(1);
	int prev = 0;
	while (!minHeap.empty()) {
		int val = minHeap.top();
		minHeap.pop();
		if (val == prev) {
			continue;
		} else {
			prev = val;
		}

		++k;
		if (k == n) {
			return val;
		} else {
			if (val <= INT_MAX / 2) {
				minHeap.push(val * 2);
			}
			if (val <= INT_MAX / 3) {
				minHeap.push(val * 3);
			}
			if (val <= INT_MAX / 5) {
				minHeap.push(val * 5);
			}
		}
	}
	return 1;
}

BOOST_AUTO_TEST_CASE(ugly_number_2_test) {
	TEST_MARKER();

	{ // Test 1
		int n = 10;
		int res = nthUglyNumber(n);
		std::cout << "n = " << n << ", res = " << res << "\n";
	}

	{ // Test 2
		int n = 1;
		int res = nthUglyNumber(n);
		std::cout << "n = " << n << ", res = " << res << "\n";
	}

	{ // Test 3
		int n = 1690;
		int res = nthUglyNumber(n);
		std::cout << "n = " << n << ", res = " << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Top K Frequent Elements" problem (LeetCode #347)
// Problem:
// - Given an integer array nums and an integer k.
// - Return the k most frequent elements.
// Input: nums = [1,1,1,2,2,3], k = 2
// Output: [1,2]

BOOST_AUTO_TEST_SUITE(top_k_frequent_elements_suite)

using Pair = std::pair<int, int>;

class Compare {
public:
	bool operator()(Pair p1, Pair p2) {
		return p1.second < p2.second;
	}
};

std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
	std::unordered_map<int, int> map;
	for (int num : nums) {
		++map[num];
	}
	
	std::priority_queue<Pair, std::vector<Pair>, Compare> maxHeap;
	for (auto elem : map) {
		maxHeap.push(elem);
	}

	std::vector<int> res;
	for (int i = 0; i < k; ++i) {
		Pair top = maxHeap.top();
		res.push_back(top.first);
		maxHeap.pop();
	}
	return res;
}

BOOST_AUTO_TEST_CASE(top_k_frequent_elements_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 1, 1, 2, 2, 3 };
		int k = 2;
		std::cout << "Nums: ";
		print(nums);
		std::cout << "K: " << k << "\n";
		std::vector<int> res = topKFrequent(nums, k);
		std::cout << "Result: ";
		print(res);
		std::cout << "\n";
	}

	{ // Test 2
		std::vector<int> nums = { 1, 1, 2, 2, 3, 4, 5 };
		int k = 2;
		std::cout << "Nums: ";
		print(nums);
		std::cout << "K: " << k << "\n";
		std::vector<int> res = topKFrequent(nums, k);
		std::cout << "Result: ";
		print(res);
		std::cout << "\n";
	}

	{ // Test 3
		std::vector<int> nums = { 1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 8 };
		int k = 5;
		std::cout << "Nums: ";
		print(nums);
		std::cout << "K: " << k << "\n";
		std::vector<int> res = topKFrequent(nums, k);
		std::cout << "Result: ";
		print(res);
		std::cout << "\n";
	}

	{ // Test 5
		std::vector<int> nums = { 1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 8 };
		int k = 8;
		std::cout << "Nums: ";
		print(nums);
		std::cout << "K: " << k << "\n";
		std::vector<int> res = topKFrequent(nums, k);
		std::cout << "Result: ";
		print(res);
		std::cout << "\n";
	}

	{ // Test 6
		std::vector<int> nums = { 1 };
		int k = 1;
		std::cout << "Nums: ";
		print(nums);
		std::cout << "K: " << k << "\n";
		std::vector<int> res = topKFrequent(nums, k);
		std::cout << "Result: ";
		print(res);
		std::cout << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Trapping Rain Water" problem (LeetCode #42)
// Problem:
// - Given n non-negative integers representing an elevation map where the width of each bar is 1.
// - Compute how much water it can trap after raining.
// Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6

BOOST_AUTO_TEST_SUITE(trapping_rain_water_suite)

using Pair = std::pair<int, int>;

class PairComparer {
public:
	bool operator()(Pair p1, Pair p2) {
		return p1.second < p2.second;
	}
};

int trap(std::vector<int>& height) {
	std::priority_queue<Pair, std::vector<Pair>, PairComparer> maxHeap;
	for (int i = 0; i < height.size(); ++i) {
		maxHeap.emplace(i, height[i]);
	}

	int res = 0;
	Pair maxLeft = maxHeap.top();
	Pair maxRight = maxHeap.top();
	maxHeap.pop();
	while (!maxHeap.empty()) {
		Pair top = maxHeap.top();
		maxHeap.pop();
		if (top.second == 0) {
			continue;
		}
		if (top.first < maxLeft.first) {
			int sum = std::accumulate(height.begin() + top.first + 1, height.begin() + maxLeft.first, 0);
			res += top.second * (maxLeft.first - top.first - 1) - sum;
			maxLeft = top;
		}
		if (top.first > maxRight.first) {
			int sum = std::accumulate(height.begin() + maxRight.first + 1, height.begin() + top.first, 0);
			res += top.second * (top.first - maxRight.first - 1) - sum;
			maxRight = top;
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(trapping_rain_water_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 2
		std::vector<int> height = { 4, 2, 0, 3, 2, 5 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 3
		std::vector<int> height = { 0, 0, 1, 0, 1, 1, 2, 5, 2, 1, 0, 1, 0, 0 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 4
		std::vector<int> height = { 1 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 5
		std::vector<int> height = { 1, 2 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 6
		std::vector<int> height = { 2, 1, 3 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 7
		std::vector<int> height = { 3, 1, 2 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}

	{ // Test 8
		std::vector<int> height = { 2, 1, 1 };
		std::cout << "Heights: ";
		print(height);
		int res = trap(height);
		std::cout << "Result: " << res << "\n\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()