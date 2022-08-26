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

BOOST_AUTO_TEST_SUITE_END()