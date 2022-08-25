#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <queue>
#include <unordered_set>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_bfs)

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
		} else {
			std::cout << "NULL";
		}

		std::cout << " + ";

		if (node->right != nullptr) {
			std::cout << node->right->val;
			queue.push(node->right);
		} else {
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

// "Binary Tree Level Order Traversal" problem (LeetCode #102)
// Problem:
// - Given the root of a binary tree.
// - Return the level order traversal of its nodes' values.
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]

BOOST_AUTO_TEST_SUITE(binary_tree_level_order_traversal_suite)

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
	// Return if the tree is empty
	if (root == nullptr) {
		return {};
	}

	// BFS
	std::vector<std::vector<int>> res;
	std::queue<TreeNode*> queue;
	queue.push(root);
	while (!queue.empty()) {
		int size = queue.size();
		std::vector<int> list;
		for (int i = 0; i < size; ++i) {
			// Get the current node
			TreeNode* node = queue.front();
			queue.pop();

			// Update result
			list.push_back(node->val);

			// Add the children nodes
			if (node->left) {
				queue.push(node->left);
			}
			if (node->right) {
				queue.push(node->right);
			}
		}
		res.push_back(std::move(list));
	}
	return res;
}

BOOST_AUTO_TEST_CASE(binary_tree_level_order_traversal_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* root = new TreeNode(3);
		root->left = new TreeNode(9);
		root->right = new TreeNode(20);
		root->right->left = new TreeNode(15);
		root->right->right = new TreeNode(7);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<std::vector<int>> res = levelOrder(root);
		print(res);
		release(root);
	}

	{ // Test 2
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
		std::vector<std::vector<int>> res = levelOrder(root);
		print(res);
		release(root);
	}

	{ // Test 3
		TreeNode* root = new TreeNode(1);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<std::vector<int>> res = levelOrder(root);
		print(res);
		release(root);
	}

	{ // Test 4
		TreeNode* root = nullptr;
		std::cout << "Tree:\n";
		print(root);
		std::cout << "Result:\n";
		std::vector<std::vector<int>> res = levelOrder(root);
		print(res);
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "01 Matrix" problem (LeetCode #542)
// Problem:
// - Given an m x n binary matrix mat.
// - Return the distance of the nearest 0 for each cell.
// Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
// Output: [[0,0,0],[0,1,0],[1,2,1]]
// Note:
// - Start from 0, not from 1. 
// - If a node is reached, it's not been visited.
//   -> Is 1 (because we marked all 0s as visited).
//   -> Has distance to the closest 0 = distance of the previous node to its closest 0 + 1.

BOOST_AUTO_TEST_SUITE(binary_matrix_suite)

std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat) {
	int dirX[] = { -1, 0, 0, 1 };
	int dirY[] = { 0, -1, 1, 0 };

	std::queue<std::pair<int, int>> queue;
	std::unordered_set<int> set;
	int m = mat.size();
	int n = mat[0].size();
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (mat[i][j] == 0) {
				queue.emplace(i, j);
				set.insert(i * n + j);
			}
		}
	}

	while (!queue.empty()) {
		std::pair<int, int> pos = queue.front();
		queue.pop();
		for (int i = 0; i < 4; ++i) {
			int nPosX = pos.first + dirX[i];
			int nPosY = pos.second + dirY[i];
			int nHash = nPosX * n + nPosY;
			if (nPosX >= 0 && nPosX < m && nPosY >= 0 && nPosY < n && !set.contains(nHash)) {
				queue.emplace(nPosX, nPosY);
				set.insert(nHash);
				mat[nPosX][nPosY] = mat[pos.first][pos.second] + 1;
			}
		}
	}

	return mat;
}

BOOST_AUTO_TEST_CASE(binary_matrix_test) {
	TEST_MARKER();

	{ // Test 1
		std::vector<std::vector<int>> mat = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}

	{ // Test 2
		std::vector<std::vector<int>> mat = { { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 1 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}

	{ // Test 3
		std::vector<std::vector<int>> mat = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}

	{ // Test 4
		std::vector<std::vector<int>> mat = { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}

	{ // Test 5
		std::vector<std::vector<int>> mat = { { 0, 1, 0, 1 }, { 1, 0, 1, 0 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}

	{ // Test 6
		std::vector<std::vector<int>> mat = { { 1, 0 }, { 1, 1 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}

	{ // Test 7
		std::vector<std::vector<int>> mat = { {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } };
		std::cout << "Matrix:\n";
		print(mat);
		std::vector<std::vector<int>> res = updateMatrix(mat);
		std::cout << "Result:\n";
		print(mat);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Minimum Depth of Binary Tree" problem (LeetCode #111)
// Problem:
// - Given a binary tree.
// - Find its minimum depth.
// Input: root = [3,9,20,null,null,15,7]
// Output: 2

BOOST_AUTO_TEST_SUITE(minimum_depth_of_binary_tree_suite)

int minDepth(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}

	std::queue<TreeNode*> queue;
	queue.push(root);
	int minDepth = 0;
	while (!queue.empty()) {
		++minDepth;
		int size = queue.size();
		for (int k = 0; k < size; ++k) {
			TreeNode* node = queue.front();
			queue.pop();
			if (node->left == nullptr && node->right == nullptr) {
				return minDepth;
			}
			if (node->left != nullptr) {
				queue.push(node->left);
			}
			if (node->right != nullptr) {
				queue.push(node->right);
			}
		}
	}

	return minDepth;
}

BOOST_AUTO_TEST_CASE(minimum_depth_of_binary_tree_test) {
	TEST_MARKER();

	{ // Test 1
		TreeNode* root = new TreeNode(3);
		root->left = new TreeNode(9);
		root->right = new TreeNode(20);
		root->right->left = new TreeNode(15);
		root->right->right = new TreeNode(7);
		std::cout << "Tree:\n";
		print(root);
		int res = minDepth(root);
		std::cout << "Result: " << res << "\n";
		release(root);
	}

	{ // Test 2
		TreeNode* root = new TreeNode(2);
		root->right = new TreeNode(3);
		root->right->right = new TreeNode(4);
		root->right->right->right = new TreeNode(5);
		root->right->right->right->right = new TreeNode(6);
		std::cout << "Tree:\n";
		print(root);
		int res = minDepth(root);
		std::cout << "Result: " << res << "\n";
		release(root);
	}

	{ // Test 3
		TreeNode* root = new TreeNode(1);
		std::cout << "Tree:\n";
		print(root);
		int res = minDepth(root);
		std::cout << "Result: " << res << "\n";
		release(root);
	}

	{ // Test 4
		TreeNode* root = nullptr;
		std::cout << "Tree:\n";
		print(root);
		int res = minDepth(root);
		std::cout << "Result: " << res << "\n";
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Populating Next Right Pointers in Each Node" problem (LeetCode #116)
// Problem:
// - Given a perfect binary tree where all leaves are on the same level, and every parent has two children.
// - Populate each next pointer to point to its next right node.
// - If there is no next right node, the next pointer should be set to NULL.
// Input:
// Output:

BOOST_AUTO_TEST_SUITE(populate_next_right_pointers_suite)

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};

void print(Node* root) {
	if (root == nullptr) {
		return;
	}

	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty()) {
		Node* node = queue.front();
		queue.pop();

		std::cout << node->val << " -> ";
		if (node->left != nullptr) {
			std::cout << node->left->val;
			queue.push(node->left);
		} else {
			std::cout << "NULL";
		}

		std::cout << " + ";

		if (node->right != nullptr) {
			std::cout << node->right->val;
			queue.push(node->right);
		} else {
			std::cout << "NULL";
		}

		std::cout << " , ";

		if (node->next != nullptr) {
			std::cout << node->next->val;
		} else {
			std::cout << "NULL";
		}

		std::cout << "\n";
	}
	std::cout << "\n";
}

void release(Node* root) {
	if (root == nullptr) {
		return;
	}

	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty()) {
		Node* node = queue.front();
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

Node* connect(Node* root) {
	if (root == nullptr) {
		return nullptr;
	}
	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty()) {
		int size = queue.size();
		Node* prev = nullptr;
		for (int i = 0; i < size; ++i) {
			Node* node = queue.front();
			queue.pop();
			if (node->left != nullptr) {
				queue.push(node->left);
			}
			if (node->right != nullptr) {
				queue.push(node->right);
			}
			if (prev != nullptr) {
				prev->next = node;
			}
			prev = node;
		}
	}
	return root;
}

BOOST_AUTO_TEST_CASE(populate_next_right_pointers_test) {
	TEST_MARKER();

	{ // Test 1
		Node* root = new Node(1);
		root->left = new Node(2);
		root->right = new Node(3);
		root->left->left = new Node(4);
		root->left->right = new Node(5);
		root->right->left = new Node(6);
		root->right->right = new Node(7);
		std::cout << "Tree:\n";
		print(root);
		Node* res = connect(root);
		std::cout << "Result:\n";
		print(res);
		release(root);
	}

	{ // Test 2
		Node* root = new Node(1);
		std::cout << "Tree:\n";
		print(root);
		Node* res = connect(root);
		std::cout << "Result:\n";
		print(res);
		release(root);
	}

	{ // Test 3
		Node* root = nullptr;
		std::cout << "Tree:\n";
		print(root);
		Node* res = connect(root);
		std::cout << "Result:\n";
		print(res);
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Word Ladder" problem (LeetCode #127)
// Problem:
// - Given two words, beginWord and endWord, and a dictionary wordList.
// - Return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5 ("hit" -> "hot" -> "dot" -> "dog" -> cog")

BOOST_AUTO_TEST_SUITE(word_ladder_suite)

bool areNeighbors(std::string word1, std::string word2) {
	const int WORD_SIZE = word1.size();
	bool isDiff = false;
	for (int i = 0; i < WORD_SIZE; ++i) {
		if (word1[i] != word2[i]) {
			if (isDiff) {
				return false;
			}
			isDiff = true;
		}
	}
	return true;
}

int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
	const int WORD_SIZE = beginWord.size();
	const int LIST_SIZE = wordList.size();

	int endId = -1;
	std::vector<std::vector<int>> graph;
	std::queue<int> queue;
	for (int i = 0; i < LIST_SIZE; ++i) {
		if (wordList[i] == endWord) {
			endId = i;
		}
		graph.push_back({});
		if (areNeighbors(wordList[i], beginWord)) {
			if (i == endId) {
				return 2;
			}
			queue.push(i);
		}
	}
	if (endId == -1 || queue.empty()) {
		return 0;
	}

	for (int i = 0; i < LIST_SIZE - 1; ++i) {
		for (int j = i + 1; j < LIST_SIZE; ++j) {
			if (areNeighbors(wordList[i], wordList[j])) {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}

	int res = 0;
	std::unordered_set<int> set;
	while (!queue.empty() && res < LIST_SIZE) {
		++res;
		int size = queue.size();
		for (int k = 0; k < size; ++k) {
			int node = queue.front();
			set.insert(node);
			queue.pop();
			std::vector<int> neighbors = graph[node];
			if (!neighbors.empty()) {
				for (int neighbor : neighbors) {
					if (neighbor == endId) {
						return res + 2;
					} else {
						if (!set.contains(neighbor)) {
							queue.push(neighbor);
						}
					}
				}
			}
		}
	}
	return 0;
}

BOOST_AUTO_TEST_CASE(word_ladder_test) {
	TEST_MARKER();

	{ // Test 1
		std::string beginWord = "hit";
		std::string endWord = "cog";
		std::vector<std::string> wordList = { "hot", "dot", "dog", "lot", "log", "cog"};

		int res = ladderLength(beginWord, endWord, wordList);
		std::cout << res << "\n";
	}

	{ // Test 2
		std::string beginWord = "hit";
		std::string endWord = "cog";
		std::vector<std::string> wordList = { "hot", "lot", "log", "cog" };

		int res = ladderLength(beginWord, endWord, wordList);
		std::cout << res << "\n";
	}

	{ // Test 3
		std::string beginWord = "hit";
		std::string endWord = "cog";
		std::vector<std::string> wordList = { "hot", "lot", "log" };

		int res = ladderLength(beginWord, endWord, wordList);
		std::cout << res << "\n";
	}

	{ // Test 4
		std::string beginWord = "hit";
		std::string endWord = "cog";
		std::vector<std::string> wordList = { "lot", "log" };

		int res = ladderLength(beginWord, endWord, wordList);
		std::cout << res << "\n";
	}

	{ // Test 5
		std::string beginWord = "hit";
		std::string endWord = "hot";
		std::vector<std::string> wordList = { "hot" };

		int res = ladderLength(beginWord, endWord, wordList);
		std::cout << res << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()