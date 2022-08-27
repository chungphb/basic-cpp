#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

#include "test_util.h"

// Note:
// - Iterative DFS is usually faster than recursive DFS.
// - Recursive DFS is usually easier to implement than iterative DFS;
// - Use a stack when implementing iterative DFS (careful about the order to push the neighbors).
// - In matrix problems, to mark a position as visited, we usually update its value to something else.

BOOST_AUTO_TEST_SUITE(test_dfs)

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

void print(TreeNode* root) {
	if (root == nullptr) {
		return;
	}

	std::queue<TreeNode*> queue;
	queue.push(root);
	while (!queue.empty()) {
		TreeNode* node = queue.front();
		queue.pop();

		std::cout << node->val << " -> ";
		if (node->left != nullptr) {
			std::cout << node->left->val;
			queue.push(node->left);
		}
		else {
			std::cout << "NULL";
		}

		std::cout << " + ";

		if (node->right != nullptr) {
			std::cout << node->right->val;
			queue.push(node->right);
		}
		else {
			std::cout << "NULL";
		}

		std::cout << "\n";
	}
	std::cout << "\n";
}

void release(TreeNode* root) {
	if (root == nullptr) {
		return;
	}

	std::queue<TreeNode*> queue;
	queue.push(root);
	while (!queue.empty()) {
		TreeNode* node = queue.front();
		queue.pop();
		if (node->left != nullptr) {
			queue.push(node->left);
		}
		if (node->right != nullptr) {
			queue.push(node->right);
		}
		delete node;
	}
}

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

// "Binary Tree Preorder Traversal" problem (LeetCode #144)
// Problem:
// - Given the root of a binary tree.
// - Return the preorder traversal of its nodes' values.
// Input: root = [1,null,2,3]
// Output: [1,2,3]

BOOST_AUTO_TEST_SUITE(binary_tree_preorder_traversal_suite)

std::vector<int> preorderTraversal(TreeNode* root) {
	if (root == nullptr) {
		return {};
	}
	std::vector<int> res;
	std::stack<TreeNode*> stack;
	stack.push(root);
	while (!stack.empty()) {
		TreeNode* node = stack.top();
		stack.pop();
		res.push_back(node->val);
		if (node->right != nullptr) {
			stack.push(node->right);
		}
		if (node->left != nullptr) {
			stack.push(node->left);
		}
	}
	return res;
}

BOOST_AUTO_TEST_CASE(binary_tree_preorder_traversal_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* root = new TreeNode(1);
		root->right = new TreeNode(2);
		root->right->left = new TreeNode(3);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<int> res = preorderTraversal(root);
		print(res);
		std::cout << "\n";
		release(root);
	}

	{ // Test 2
		TreeNode* root = nullptr;
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<int> res = preorderTraversal(root);
		print(res);
		std::cout << "\n";
		release(root);
	}

	{ // Test 3
		TreeNode* root = new TreeNode(1);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<int> res = preorderTraversal(root);
		print(res);
		std::cout << "\n";
		release(root);
	}

	{ // Test 4
		TreeNode* root = new TreeNode(3);
		root->left = new TreeNode(9);
		root->right = new TreeNode(20);
		root->right->left = new TreeNode(15);
		root->right->right = new TreeNode(7);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<int> res = preorderTraversal(root);
		print(res);
		std::cout << "\n";
		release(root);
	}

	{ // Test 5
		TreeNode* root = new TreeNode(3);
		root->left = new TreeNode(9);
		root->right = new TreeNode(20);
		root->left->left = new TreeNode(6);
		root->left->right = new TreeNode(13);
		root->right->left = new TreeNode(15);
		root->right->right = new TreeNode(7);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<int> res = preorderTraversal(root);
		print(res);
		std::cout << "\n";
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Same Tree" problem (LeetCode #100)
// Problem:
// - Given the roots of two binary trees p and q.
// - Check if they are the same or not.
// Input: p = [1,2,3], q = [1,2,3]
// Output: true

BOOST_AUTO_TEST_SUITE(same_tree_suite)

bool isSameTree(TreeNode* p, TreeNode* q) {
	if (!p) {
		return !q;
	}

	if (!q) {
		return !p;
	}

	std::stack<TreeNode*> pQueue;
	pQueue.push(p);
	std::stack<TreeNode*> qQueue;
	qQueue.push(q);
	while (!pQueue.empty() && !qQueue.empty()) {
		TreeNode* pNode = pQueue.top();
		pQueue.pop();
		TreeNode* qNode = qQueue.top();
		qQueue.pop();
		if (pNode->val != qNode->val) {
			return false;
		}

		if ((pNode->right && !qNode->right) || (!pNode->right && qNode->right)) {
			return false;
		}

		if (pNode->right && qNode->right) {
			pQueue.push(pNode->right);
			qQueue.push(qNode->right);
		}

		if ((pNode->left && !qNode->left) || (!pNode->left && qNode->left)) {
			return false;
		}

		if (pNode->left && qNode->left) {
			pQueue.push(pNode->left);
			qQueue.push(qNode->left);
		}
	}
	return pQueue.empty() && qQueue.empty();
}

BOOST_AUTO_TEST_CASE(same_tree_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* p = new TreeNode(1);
		p->left = new TreeNode(2);
		p->right = new TreeNode(3);
		std::cout << "Tree 1:\n";
		print(p);

		TreeNode* q = new TreeNode(1);
		q->left = new TreeNode(2);
		q->right = new TreeNode(3);
		std::cout << "Tree 2:\n";
		print(q);

		bool res = isSameTree(p, q);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";

		release(p);
		release(q);
	}

	{ // Test 2
		TreeNode* p = new TreeNode(1);
		p->left = new TreeNode(2);
		std::cout << "Tree 1:\n";
		print(p);

		TreeNode* q = new TreeNode(1);
		q->right = new TreeNode(2);
		std::cout << "Tree 2:\n";
		print(q);

		bool res = isSameTree(p, q);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";

		release(p);
		release(q);
	}

	{ // Test 3
		TreeNode* p = new TreeNode(1);
		p->left = new TreeNode(2);
		p->right = new TreeNode(1);
		std::cout << "Tree 1:\n";
		print(p);

		TreeNode* q = new TreeNode(1);
		q->left = new TreeNode(1);
		q->right = new TreeNode(2);
		std::cout << "Tree 2:\n";
		print(q);

		bool res = isSameTree(p, q);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";

		release(p);
		release(q);
	}

	{ // Test 4
		TreeNode* p = new TreeNode(1);
		std::cout << "Tree 1:\n";
		print(p);

		TreeNode* q = new TreeNode(1);
		q->right = new TreeNode(2);
		std::cout << "Tree 2:\n";
		print(q);

		bool res = isSameTree(p, q);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";

		release(p);
		release(q);
	}

	{ // Test 5
		TreeNode* p = new TreeNode(1);
		std::cout << "Tree 1:\n";
		print(p);

		TreeNode* q = nullptr;
		std::cout << "Tree 2:\n";
		print(q);

		bool res = isSameTree(p, q);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";

		release(p);
		release(q);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Symmetric Tree" problem (LeetCode #101)
// Problem:
// - Given the root of a binary tree.
// - Check whether it is a mirror of itself.
// Input: root = [1,2,2,3,4,4,3]
// Output: true

BOOST_AUTO_TEST_SUITE(symmetric_tree_suite)

bool isSymmetric(TreeNode* root) {
	if (root == nullptr) {
		return true;
	}
	std::stack<TreeNode*> leftStack;
	leftStack.push(root->left);
	std::stack<TreeNode*> rightStack;
	rightStack.push(root->right);
	while (!leftStack.empty() && !rightStack.empty()) {
		TreeNode* leftNode = leftStack.top();
		leftStack.pop();
		TreeNode* rightNode = rightStack.top();
		rightStack.pop();
		if (leftNode == nullptr && rightNode == nullptr) {
			continue;
		} else if (leftNode == nullptr || rightNode == nullptr) {
			return false;
		} else {
			if (leftNode->val != rightNode->val) {
				return false;
			}
			leftStack.push(leftNode->right);
			leftStack.push(leftNode->left);
			rightStack.push(rightNode->left);
			rightStack.push(rightNode->right);
		}
	}
	return leftStack.empty() && rightStack.empty();
}

BOOST_AUTO_TEST_CASE(symmetric_tree_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* root = new TreeNode(1);
		root->left = new TreeNode(2);
		root->right = new TreeNode(2);
		root->left->left = new TreeNode(3);
		root->left->right = new TreeNode(4);
		root->right->left = new TreeNode(4);
		root->right->right = new TreeNode(3);
		std::cout << "Tree:\n";
		print(root);
		bool res = isSymmetric(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 2
		TreeNode* root = new TreeNode(1);
		root->left = new TreeNode(2);
		root->right = new TreeNode(2);
		root->left->left = new TreeNode(3);
		root->right->left = new TreeNode(3);
		std::cout << "Tree:\n";
		print(root);
		bool res = isSymmetric(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 3
		TreeNode* root = new TreeNode(1);
		std::cout << "Tree:\n";
		print(root);
		bool res = isSymmetric(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 4
		TreeNode* root = nullptr;
		std::cout << "Tree:\n";
		print(root);
		bool res = isSymmetric(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 5
		TreeNode* root = new TreeNode(1);
		root->left = new TreeNode(2);
		root->right = new TreeNode(2);
		root->left->left = new TreeNode(3);
		root->left->left->left = new TreeNode(4);
		root->right->right = new TreeNode(3);
		root->right->right->right = new TreeNode(4);
		std::cout << "Tree:\n";
		print(root);
		bool res = isSymmetric(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Maximum Depth of Binary Tree" problem (LeetCode #104)
// Problem:
// - Given the root of a binary tree.
// - Return its maximum depth.
// Input: root = [3,9,20,null,null,15,7]
// Output: 3

BOOST_AUTO_TEST_SUITE(maximum_depth_suite)

int depth(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}
	int leftDepth = depth(root->left);
	int rightDepth = depth(root->right);
	return 1 + max(leftDepth, rightDepth);
}

int maxDepth(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}
	int leftDepth = maxDepth(root->left);
	int rightDepth = maxDepth(root->right);
	return 1 + max(leftDepth, rightDepth);
}

BOOST_AUTO_TEST_CASE(maximum_depth_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* root = new TreeNode(3);
		root->left = new TreeNode(9);
		root->right = new TreeNode(20);
		root->right->left = new TreeNode(15);
		root->right->right = new TreeNode(7);
		std::cout << "Tree:\n";
		print(root);
		int res = maxDepth(root);
		std::cout << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 2
		TreeNode* root = new TreeNode(1);
		root->right = new TreeNode(2);
		std::cout << "Tree:\n";
		print(root);
		int res = maxDepth(root);
		std::cout << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 3
		TreeNode* root = new TreeNode(1);
		std::cout << "Tree:\n";
		print(root);
		int res = maxDepth(root);
		std::cout << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 4
		TreeNode* root = nullptr;
		std::cout << "Tree:\n";
		print(root);
		int res = maxDepth(root);
		std::cout << "Result: " << res << "\n\n";
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Convert Sorted Array to Binary Search Tree" problem (LeetCode #108)
// Problem:
// - Given an integer array nums where the elements are sorted in ascending order.
// - Convert it to a height-balanced binary search tree.
// Input: nums = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]

BOOST_AUTO_TEST_SUITE(convert_sorted_array_to_bst_suite)

TreeNode* createBST(std::vector<int>& nums, int left, int right) {
	if (left > right) {
		return nullptr;
	}
	int mid = (left + right) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = createBST(nums, left, mid - 1);
	root->right = createBST(nums, mid + 1, right);
	return root;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums) {
	return createBST(nums, 0, nums.size() - 1);
}

BOOST_AUTO_TEST_CASE(convert_sorted_array_to_bst_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { -10, -3, 0, 5, 9 };
		print(nums);
		TreeNode* root = sortedArrayToBST(nums);
		print(root);
		release(root);
	}

	{ // Test 2
		std::vector<int> nums = { 1, 3 };
		print(nums);
		TreeNode* root = sortedArrayToBST(nums);
		print(root);
		release(root);
	}

	{ // Test 3
		std::vector<int> nums = { 1 };
		print(nums);
		TreeNode* root = sortedArrayToBST(nums);
		print(root);
		release(root);
	}

	{ // Test 4
		std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		print(nums);
		TreeNode* root = sortedArrayToBST(nums);
		print(root);
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// ========================================
// COMBINATIONS, PERMUTATIONS, SUBSETS
// ========================================

// "Combinations" problem (LeetCode #77)
// Problem:
// - Given two integers n and k.
// - Return all possible combinations of k numbers chosen from the range [1, n].
// Input: n = 4, k = 2
// Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]

BOOST_AUTO_TEST_SUITE(combinations_suite)

void dfs(int start, int n, int k, std::vector<int>& list, std::vector<std::vector<int>>& res) {
	if (list.size() == k) {
		res.push_back(list);
		return;
	}

	for (int i = start; i <= n; ++i) {
		list.push_back(i);
		dfs(i + 1, n, k, list, res);
		list.pop_back();
	}
}

std::vector<std::vector<int>> combine(int n, int k) {
	std::vector<std::vector<int>> res;
	std::vector<int> list;
	dfs(1, n, k, list, res);
	return res;
}

BOOST_AUTO_TEST_CASE(combinations_test) {
	TEST_MARKER();

	{ // Test 1
		int n = 4, k = 2;
		std::vector<std::vector<int>> res = combine(n, k);
		print(res);
	}

	{ // Test 2
		int n = 1, k = 1;
		std::vector<std::vector<int>> res = combine(n, k);
		print(res);
	}

	{ // Test 3
		int n = 8, k = 4;
		std::vector<std::vector<int>> res = combine(n, k);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Combination Sum" problem (LeetCode #39)
// Problem:
// - Given an array of distinct integers candidates and a target integer target.
// - Return a list of all unique combinations of candidates where the chosen numbers sum to target.
// - The same number may be chosen from candidates an unlimited number of times.
// Input: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]

BOOST_AUTO_TEST_SUITE(combination_sum_suite)

void dfs(int start, std::vector<int>& candidates, int target, std::vector<int>& list, int sum, std::vector<std::vector<int>>& res) {
	if (sum > target) {
		return;
	}
	if (sum == target) {
		res.push_back(list);
		return;
	}
	for (int i = start; i < candidates.size(); ++i) {
		list.push_back(candidates[i]);
		sum += candidates[i];
		dfs(i, candidates, target, list, sum, res);
		list.pop_back();
		sum -= candidates[i];
	}
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
	std::vector<std::vector<int>> res;
	std::vector<int> list;
	dfs(0, candidates, target, list, 0, res);
	return res;
}

BOOST_AUTO_TEST_CASE(combination_sum_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> candidates = { 2, 3, 6, 7 };
		int target = 7;
		std::vector<std::vector<int>> res = combinationSum(candidates, target);
		print(res);
	}

	{ // Test 2
		std::vector<int> candidates = { 2, 3, 5, 4, 1 };
		int target = 6;
		std::vector<std::vector<int>> res = combinationSum(candidates, target);
		print(res);
	}

	{ // Test 3
		std::vector<int> candidates = { 2, 3, 5 };
		int target = 8;
		std::vector<std::vector<int>> res = combinationSum(candidates, target);
		print(res);
	}

	{ // Test 4
		std::vector<int> candidates = { 2 };
		int target = 1;
		std::vector<std::vector<int>> res = combinationSum(candidates, target);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Combination Sum II" problem (LeetCode #40)
// Problem:
// - Given a collection of candidate numbers (candidates) and a target number (target).
// - Find all unique combinations in candidates where the candidate numbers sum to target.
// - Each number in candidates may only be used once in the combination.
// Input: candidates = [10,1,2,7,6,1,5], target = 8
// Output: [
// [1, 1, 6],
// [1, 2, 5],
// [1, 7],
// [2, 6]
// ]

BOOST_AUTO_TEST_SUITE(combination_sum_2_suite)

void dfs(int start, std::vector<int>& candidates, int target, std::vector<int>& list, int sum, std::vector<std::vector<int>>& res) {
	if (sum > target) {
		return;
	}
	if (sum == target) {
		res.push_back(list);
		return;
	}

	for (int i = start; i < candidates.size(); ++i) {
		if (i > start && candidates[i] == candidates[i - 1]) {
			continue;
		}
		list.push_back(candidates[i]);
		sum += candidates[i];
		dfs(i + 1, candidates, target, list, sum, res);
		list.pop_back();
		sum -= candidates[i];
	}
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
	std::sort(candidates.begin(), candidates.end());
	std::vector<std::vector<int>> res;
	std::vector<int> list;
	dfs(0, candidates, target, list, 0, res);
	return res;
}

BOOST_AUTO_TEST_CASE(combination_sum_2_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> candidates = { 10, 1, 2, 7, 6, 1, 5 };
		int target = 8;
		std::vector<std::vector<int>> res = combinationSum2(candidates, target);
		print(res);
	}

	{ // Test 2
		std::vector<int> candidates = { 2, 5, 2, 1, 2 };
		int target = 5;
		std::vector<std::vector<int>> res = combinationSum2(candidates, target);
		print(res);
	}

	{ // Test 3
		std::vector<int> candidates = { 2, 3, 5 };
		int target = 8;
		std::vector<std::vector<int>> res = combinationSum2(candidates, target);
		print(res);
	}

	{ // Test 4
		std::vector<int> candidates = { 2 };
		int target = 1;
		std::vector<std::vector<int>> res = combinationSum2(candidates, target);
		print(res);
	}

	{ // Test 5
		std::vector<int> candidates = { 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3 };
		int target = 4;
		std::vector<std::vector<int>> res = combinationSum2(candidates, target);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Combination Sum III" problem (LeetCode #216)
// Problem:
// - Find all valid combinations of k numbers that sum up to n, such that:
//   + Only numbers 1 through 9 are used.
//   + Each number is used at most once.
// Input: k = 3, n = 7
// Output: [[1,2,4]]

BOOST_AUTO_TEST_SUITE(combination_sum_3_suite)

void dfs(int start, int k, int n, std::vector<int>& list, int sum, std::vector<std::vector<int>>& res) {
	if (sum > n) {
		return;
	}

	if (list.size() == k) {
		if (sum == n) {
			res.push_back(list);
		}
		return;
	}

	for (int i = start; i <= 9; ++i) {
		list.push_back(i);
		sum += i;
		dfs(i + 1, k, n, list, sum, res);
		list.pop_back();
		sum -= i;
	}
}

std::vector<std::vector<int>> combinationSum3(int k, int n) {
	std::vector<std::vector<int>> res;
	std::vector<int> list;
	dfs(1, k, n, list, 0, res);
	return res;
}

BOOST_AUTO_TEST_CASE(combination_sum_3_test) {
	TEST_MARKER();

	{ // Test 1
		int k = 3, n = 7;
		std::vector<std::vector<int>> res = combinationSum3(k, n);
		print(res);
	}

	{ // Test 2
		int k = 3, n = 9;
		std::vector<std::vector<int>> res = combinationSum3(k, n);
		print(res);
	}

	{ // Test 3
		int k = 4, n = 1;
		std::vector<std::vector<int>> res = combinationSum3(k, n);
		print(res);
	}

	{ // Test 4
		int k = 9, n = 45;
		std::vector<std::vector<int>> res = combinationSum3(k, n);
		print(res);
	}

	{ // Test 5
		int k = 8, n = 40;
		std::vector<std::vector<int>> res = combinationSum3(k, n);
		print(res);
	}

	{ // Test 5
		int k = 9, n = 50;
		std::vector<std::vector<int>> res = combinationSum3(k, n);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Permutations" problem (LeetCode #46)
// Problem
// - Given an array nums of distinct integers.
// - Return all the possible permutations.
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

BOOST_AUTO_TEST_SUITE(permutations_suite)

void dfs(std::vector<int>& nums, std::vector<int>& list, std::vector<bool>& visited, std::vector<std::vector<int>>& res) {
	if (list.size() == nums.size()) {
		res.push_back(list);
		return;
	}
	for (int i = 0; i < nums.size(); ++i) {
		if (visited[i]) {
			continue;
		}
		list.push_back(nums[i]);
		visited[i] = true;
		dfs(nums, list, visited, res);
		list.pop_back();
		visited[i] = false;
	}
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
	std::vector<std::vector<int>> res;
	std::vector<int> list;
	std::vector<bool> visited(nums.size());
	std::fill(visited.begin(), visited.end(), false);
	dfs(nums, list, visited, res);
	return res;
}

BOOST_AUTO_TEST_CASE(permutations_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = {1, 2, 3};
		std::vector<std::vector<int>> res = permute(nums);
		print(res);
	}

	{ // Test 2
		std::vector<int> nums = { 3, 2, 1 };
		std::vector<std::vector<int>> res = permute(nums);
		print(res);
	}

	{ // Test 3
		std::vector<int> nums = { 0, 1 };
		std::vector<std::vector<int>> res = permute(nums);
		print(res);
	}

	{ // Test 4
		std::vector<int> nums = { 1 };
		std::vector<std::vector<int>> res = permute(nums);
		print(res);
	}

	{ // Test 5
		std::vector<int> nums = { -1, 2, 3, -2, 5, 4 };
		std::vector<std::vector<int>> res = permute(nums);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Subsets" problem (LeetCode #78)
// Problem:
// - Given an integer array nums of unique elements.
// - Return all possible subsets (the power set).
// - The solution set must not contain duplicate subsets.
// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

BOOST_AUTO_TEST_SUITE(subsets_suite)

void dfs(int start, std::vector<int>& nums, std::vector<int>& list, std::vector<std::vector<int>>& res) {
	res.push_back(list);
	for (int i = start; i < nums.size(); ++i) {
		list.push_back(nums[i]);
		dfs(i + 1, nums, list, res);
		list.pop_back();
	}
}

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
	std::vector<int> list;
	std::vector<std::vector<int>> res;
	dfs(0, nums, list, res);
	return res;
}

BOOST_AUTO_TEST_CASE(subsets_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> nums = { 1, 2, 3 };
		std::vector<std::vector<int>> res = subsets(nums);
		print(res);
	}

	{ // Test 2
		std::vector<int> nums = { 3, 2, 1 };
		std::vector<std::vector<int>> res = subsets(nums);
		print(res);
	}

	{ // Test 3
		std::vector<int> nums = { 0, 1 };
		std::vector<std::vector<int>> res = subsets(nums);
		print(res);
	}

	{ // Test 4
		std::vector<int> nums = { 1 };
		std::vector<std::vector<int>> res = subsets(nums);
		print(res);
	}

	{ // Test 5
		std::vector<int> nums = { -1, 2, 3, -2, 5, 4 };
		std::vector<std::vector<int>> res = subsets(nums);
		print(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// ========================================
// COMBINATIONS, PERMUTATIONS, SUBSETS
// ========================================

// "Word Search" problem (LeetCode #79)
// Problem:
// - Given an m x n grid of characters board and a string word.
// - Return true if word exists in the grid.
// Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
// Output: true

BOOST_AUTO_TEST_SUITE(word_search_suite)

bool dfs(int posX, int posY, int id, std::vector<std::vector<char>>& board, std::string word) {
	if (id >= word.size()) {
		return true;
	}

	if (posX < 0 || posX >= board.size() || posY < 0 || posY >= board[0].size() || board[posX][posY] != word[id]) {
		return false;
	}

	char c = board[posX][posY];
	board[posX][posY] = '*';
	int res = dfs(posX + 1, posY, id + 1, board, word) || dfs(posX - 1, posY, id + 1, board, word) || dfs(posX, posY + 1, id + 1, board, word) || dfs(posX, posY - 1, id + 1, board, word);
	board[posX][posY] = c;
	return res;
}

bool exist(std::vector<std::vector<char>>& board, std::string word) {
	int m = board.size();
	int n = board[0].size();
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (board[i][j] == word[0]) {
				int res = dfs(i, j, 0, board, word);
				if (res) {
					return true;
				}
			}
		}
	}
	return false;
}

BOOST_AUTO_TEST_CASE(word_search_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<std::vector<char>> board = {
			{'A', 'B', 'C', 'E'},
			{'S', 'F', 'C', 'S'},
			{'A', 'D', 'E', 'E'}
		};
		std::string word = "SEE";
		bool res = exist(board, word);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 2
		std::vector<std::vector<char>> board = {
			{'A', 'B', 'C', 'E'},
			{'S', 'F', 'C', 'S'},
			{'A', 'D', 'E', 'E'}
		};
		std::string word = "ABCD";
		bool res = exist(board, word);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 3
		std::vector<std::vector<char>> board = {
			{'A'}
		};
		std::string word = "A";
		bool res = exist(board, word);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 4
		std::vector<std::vector<char>> board = {
			{'A'}
		};
		std::string word = "B";
		bool res = exist(board, word);
		std::cout << std::boolalpha << res << std::endl;
	}

	{ // Test 5
		std::vector<std::vector<char>> board = {
			{'A', 'B', 'C', 'E'},
			{'S', 'F', 'C', 'S'},
			{'A', 'D', 'E', 'E'}
		};
		std::string word = "ABCB";
		bool res = exist(board, word);
		std::cout << std::boolalpha << res << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Validate Binary Search Tree" problem (LeetCode #xxx)
// Problem:
// - Given the root of a binary tree.
// - Determine if it is a valid binary search tree (BST).
// Input: root = [5,1,4,null,null,3,6]
// Output: false

BOOST_AUTO_TEST_SUITE(validate_bst_suite)

bool isValidBST(TreeNode* root) {
	if (root == nullptr) {
		return true;
	}
	TreeNode* node;

	node = root->left;
	while (node != nullptr) {
		if (node->right == nullptr && node->val >= root->val) {
			return false;
		}
		node = node->right;
	}

	node = root->right;
	while (node != nullptr) {
		if (node->left == nullptr && node->val <= root->val) {
			return false;
		}
		node = node->left;
	}

	return isValidBST(root->left) && isValidBST(root->right);
}

BOOST_AUTO_TEST_CASE(validate_bst_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* root = new TreeNode(2);
		root->left = new TreeNode(1);
		root->right = new TreeNode(3);
		std::cout << "Tree:\n";
		print(root);
		bool res = isValidBST(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 2
		TreeNode* root = new TreeNode(5);
		root->left = new TreeNode(1);
		root->right = new TreeNode(4);
		root->right->left = new TreeNode(3);
		root->right->right = new TreeNode(6);
		std::cout << "Tree:\n";
		print(root);
		bool res = isValidBST(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 3
		TreeNode* root = new TreeNode(1);
		std::cout << "Tree:\n";
		print(root);
		bool res = isValidBST(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 4
		TreeNode* root = new TreeNode(10);
		root->left = new TreeNode(5);
		root->right = new TreeNode(15);
		root->left->left = new TreeNode(3);
		root->left->right = new TreeNode(7);
		root->left->right->left = new TreeNode(6);
		root->right->left = new TreeNode(12);
		root->right->right = new TreeNode(17);
		root->right->left->right = new TreeNode(14);
		root->right->left->right->left = new TreeNode(13);
		std::cout << "Tree:\n";
		print(root);
		bool res = isValidBST(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 5
		TreeNode* root = new TreeNode(10);
		root->left = new TreeNode(5);
		root->right = new TreeNode(15);
		root->left->left = new TreeNode(3);
		root->left->right = new TreeNode(7);
		root->left->right->left = new TreeNode(8);
		root->right->left = new TreeNode(12);
		root->right->right = new TreeNode(17);
		root->right->left->right = new TreeNode(14);
		root->right->left->right->left = new TreeNode(13);
		std::cout << "Tree:\n";
		print(root);
		bool res = isValidBST(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}

	{ // Test 6
		TreeNode* root = new TreeNode(2);
		root->left = new TreeNode(2);
		root->right = new TreeNode(2);
		std::cout << "Tree:\n";
		print(root);
		bool res = isValidBST(root);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Construct Binary Tree from Preorder and Inorder Traversal" problem (LeetCode #105)
// Problem:
// - Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree.
// - Construct and return the binary tree.
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]

BOOST_AUTO_TEST_SUITE(construct_binary_tree_suite)

TreeNode* dfs(int preStart, int inStart, int size, std::vector<int>& preorder, std::vector<int>& inorder) {
	if (size == 0) {
		return nullptr;
	}

	// Construct the root
	int rootVal = preorder[preStart];
	TreeNode* root = new TreeNode(rootVal);

	// Determine the size of the subtrees
	int leftSize = 0;
	for (int k = inStart; k < inStart + size; ++k) {
		if (inorder[k] == rootVal) { 
			break;
		}
		++leftSize;
	}
	int rightSize = size - leftSize - 1;

	// Construct the subtrees
	root->left = dfs(preStart + 1, inStart, leftSize, preorder, inorder);
	root->right = dfs(preStart + leftSize + 1, inStart + leftSize + 1, rightSize, preorder, inorder);
	return root;
}

TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
	if (preorder.size() == 0) {
		return nullptr;
	}
	return dfs(0, 0, preorder.size(), preorder, inorder);
}

BOOST_AUTO_TEST_CASE(construct_binary_tree_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<int> preorder = { 3, 9, 20, 15, 7 };
		std::vector<int> inorder = { 9, 3, 15, 20, 7 };
		TreeNode* root = buildTree(preorder, inorder);
		print(root);
		release(root);
	}

	{ // Test 2
		std::vector<int> preorder = { -1 };
		std::vector<int> inorder = { -1 };
		TreeNode* root = buildTree(preorder, inorder);
		print(root);
		release(root);
	}

	{ // Test 3
		std::vector<int> preorder = { 10, 5, 3, 7, 6, 15, 12, 14, 13, 17 };
		std::vector<int> inorder = { 3, 5, 6, 7, 10, 12, 13, 14, 15, 17 };
		TreeNode* root = buildTree(preorder, inorder);
		print(root);
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()