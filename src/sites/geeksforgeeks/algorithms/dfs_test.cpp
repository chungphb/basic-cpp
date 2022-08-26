#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

#include "test_util.h"

// Note:
// - Iterative DFS is usually faster than recursive DFS.
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

BOOST_AUTO_TEST_SUITE_END()