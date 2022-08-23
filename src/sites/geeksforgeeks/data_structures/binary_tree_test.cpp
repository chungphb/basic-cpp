#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <queue>
#include <stack>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_binary_tree)

struct node {
	int data;
	node* left;
	node* right;
};

node* create_new_node(int data) {
	node* new_node = new node();
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	return new_node;
}

void free(node* root) {
	if (root == nullptr) {
		return;
	}
	free(root->left);
	free(root->right);
	delete root;
}

// BFS

void print_bfs(node* root);

BOOST_AUTO_TEST_CASE(test_1) {
	TEST_MARKER();

	node* root = create_new_node(1);
	root->left = create_new_node(2);
	root->right = create_new_node(3);
	root->left->left = create_new_node(4);
	root->left->right = create_new_node(5);

	print_bfs(root);

	free(root);
}

void print_bfs(node* root) {
	if (root == nullptr) {
		return;
	}
	std::queue<node*> queue;
	queue.push(root);
	while (!queue.empty()) {
		node* current_node = queue.front();
		std::cout << current_node->data << std::endl;
		queue.pop();
		if (current_node->left != nullptr) {
			queue.push(current_node->left);
		}
		if (current_node->right != nullptr) {
			queue.push(current_node->right);
		}
	}
}

// DFS

void print_dfs_preorder(node* root);

void print_dfs_inorder(node* root);

void print_dfs_postorder(node* root);

BOOST_AUTO_TEST_CASE(test_2) {
	TEST_MARKER();

	node* root = create_new_node(1);
	root->left = create_new_node(2);
	root->right = create_new_node(3);
	root->left->left = create_new_node(4);
	root->left->right = create_new_node(5);

	std::cout << "Preorder: " << std::endl;
	print_dfs_preorder(root);
	std::cout << "Inorder: " << std::endl;
	print_dfs_inorder(root);
	std::cout << "Postorder: " << std::endl;
	print_dfs_postorder(root);

	free(root);
}

void print_dfs_preorder(node* root) {
	if (root == nullptr) {
		return;
	}
	std::cout << root->data << std::endl;
	print_dfs_preorder(root->left);
	print_dfs_preorder(root->right);
}

void print_dfs_inorder(node* root) {
	if (root == nullptr) {
		return;
	}
	print_dfs_inorder(root->left);
	std::cout << root->data << std::endl;
	print_dfs_inorder(root->right);
}

void print_dfs_postorder(node* root) {
	if (root == nullptr) {
		return;
	}
	print_dfs_postorder(root->left);
	print_dfs_postorder(root->right);
	std::cout << root->data << std::endl;
}

// Find the diameter of a tree

int diameter(node* root, int* height);

BOOST_AUTO_TEST_CASE(test_3) {
	TEST_MARKER();

	node* root = create_new_node(1);
	root->left = create_new_node(2);
	root->right = create_new_node(3);
	root->left->left = create_new_node(4);
	root->left->right = create_new_node(5);
	// Test case: Add more nodes
	// root->right->left = create_new_node(6);

	int height = 0;
	std::cout << "The diameter of the tree: " << diameter(root, &height) << std::endl;

	free(root);
}

int diameter(node* root, int* height) {
	if (root == nullptr) {
		*height = 0;
		return 0;
	}
	int left_height = 0;
	int left_diameter = diameter(root->left, &left_height);
	int right_height = 0;
	int right_diameter = diameter(root->right, &right_height);
	*height = max(left_height, right_height) + 1;
	return max(left_height + right_height + 1, max(left_diameter, right_diameter));
}

// Another inorder tree traversal implementation

void print_dfs_inorder_2(node* root);

BOOST_AUTO_TEST_CASE(test_4) {
	TEST_MARKER();

	node* root = create_new_node(1);
	root->left = create_new_node(2);
	root->right = create_new_node(3);
	root->left->left = create_new_node(4);
	root->left->right = create_new_node(5);

	std::cout << "Inorder: " << std::endl;
	print_dfs_inorder_2(root);

	free(root);
}

void print_dfs_inorder_2(node* root) {
	std::stack<node*> stack;
	node* current_node = root;
	while (current_node != nullptr || !stack.empty()) {
		while (current_node != nullptr) {
			stack.push(current_node);
			current_node = current_node->left;
		}
		current_node = stack.top();
		stack.pop();
		std::cout << current_node->data << std::endl;
		current_node = current_node->right;
	}
}

// Construct a tree from given inorder and preorder traversals

node* construct_tree(int in[], int pre[], int in_start, int in_end, int& pre_index);

BOOST_AUTO_TEST_CASE(test_5) {
	TEST_MARKER();

	int in[] = { 4, 2, 5, 1, 3 };
	int pre[] = { 1, 2, 4, 5, 3 };
	int in_size = sizeof(in) / sizeof(in[0]);
	int pre_index = 0;

	node* root = construct_tree(in, pre, 0, in_size - 1, pre_index);

	print_bfs(root);

	free(root);
}

node* construct_tree(int in[], int pre[], int in_start, int in_end, int& pre_index) {
	if (in_start > in_end) {
		return nullptr;
	}
	node* current_node = create_new_node(pre[pre_index]);
	++pre_index;
	if (in_start == in_end) {
		return current_node;
	}
	int in_index = -1;
	for (int i = in_start; i <= in_end; ++i) {
		if (in[i] == current_node->data) {
			in_index = i;
			break;
		}
	}
	if (in_index == -1) {
		throw std::runtime_error("Something went wrong");
	}
	current_node->left = construct_tree(in, pre, in_start, in_index - 1, pre_index);
	current_node->right = construct_tree(in, pre, in_index + 1, in_end, pre_index);
	return current_node;
}

// Print nodes at the same level

void print_level(node* root, int level);

BOOST_AUTO_TEST_CASE(test_6) {
	TEST_MARKER();

	node* root = create_new_node(1);
	root->left = create_new_node(2);
	root->right = create_new_node(3);
	root->left->left = create_new_node(4);
	root->left->right = create_new_node(5);

	int level = 1;
	// Test cases:
	// int level = 0;
	// int level = 3;
	// int level = -1;
	std::cout << "Level " << level << ": " << std::endl;
	print_level(root, level);

	free(root);
}

void print_level(node* root, int level) {
	if (root == nullptr || level < 0) {
		return;
	}
	if (level == 0) {
		std::cout << root->data << std::endl;
		return;
	}
	print_level(root->left, level - 1);
	print_level(root->right, level - 1);
}

// Check if a binary tree is subtree of another binary tree

void store_dfs_preorder(node* root, char arr[], int& id);
void store_dfs_inorder(node* root, char arr[], int& id);
bool is_subtree(node* root_1, node* root_2);

BOOST_AUTO_TEST_CASE(test_7) {
	TEST_MARKER();

	node* root_1 = create_new_node('a');
	root_1->left = create_new_node('b');
	root_1->right = create_new_node('c');
	root_1->left->left = create_new_node('d');
	root_1->left->right = create_new_node('e');
	root_1->right->left = create_new_node('f');
	root_1->left->left->left = create_new_node('g');

	node* root_2 = create_new_node('b');
	root_2->left = create_new_node('d');
	root_2->right = create_new_node('e');
	root_2->left->left = create_new_node('g');

	std::cout << "Tree 1: " << std::endl;
	print_bfs(root_1);
	std::cout << "Tree 2: " << std::endl;
	print_bfs(root_2);
	std::cout << "Is Tree 2 a subtree of Tree 1: " << std::boolalpha << is_subtree(root_1, root_2) << std::endl;

	free(root_1);
	free(root_2);
}

void store_dfs_preorder(node* root, char arr[], int& id) {
	if (root == nullptr) {
		arr[id++] = '$';
		return;
	}
	arr[id++] = root->data;
	store_dfs_preorder(root->left, arr, id);
	store_dfs_preorder(root->right, arr, id);
}

void store_dfs_inorder(node* root, char arr[], int& id) {
	if (root == nullptr) {
		arr[id++] = '$';
		return;
	}
	store_dfs_inorder(root->left, arr, id);
	arr[id++] = root->data;
	store_dfs_inorder(root->right, arr, id);
}

bool is_subtree(node* root_1, node* root_2) {
	if (root_2 == nullptr) {
		return true;
	}
	if (root_1 == nullptr) {
		return false;
	}

	const int SIZE = 100;

	int id_1 = 0, id_2 = 0;
	char pre_1[SIZE], pre_2[SIZE];
	store_dfs_preorder(root_1, pre_1, id_1);
	store_dfs_preorder(root_2, pre_2, id_2);
	pre_1[id_1] = '\0', pre_2[id_2] = '\0';

	if (strstr(pre_1, pre_2) == nullptr) {
		return false;
	}

	id_1 = 0, id_2 = 0;
	char in_1[SIZE], in_2[SIZE];
	store_dfs_inorder(root_1, in_1, id_1);
	store_dfs_inorder(root_2, in_2, id_2);
	in_1[id_1] = '\0', in_2[id_2] = '\0';

	return strstr(pre_1, pre_2) != nullptr;
}

// Connect nodes at same level

struct node_2 {
	int data;
	node_2* left;
	node_2* right;
	node_2* next;
};
node_2* create_new_node_2(int data);
void free(node_2* root);
void connect(node_2* root);
void print_next(node_2* current_node);

BOOST_AUTO_TEST_CASE(test_8) {
	TEST_MARKER();

	node_2* root = create_new_node_2(1);
	root->left = create_new_node_2(2);
	root->right = create_new_node_2(3);
	root->left->left = create_new_node_2(4);
	root->left->right = create_new_node_2(5);

	connect(root);

	print_next(root);
	print_next(root->left);
	print_next(root->right);
	print_next(root->left->left);
	print_next(root->left->right);

	free(root);
}

node_2* create_new_node_2(int data) {
	node_2* new_node = new node_2();
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->next = nullptr;
	return new_node;
}

void free(node_2* root) {
	if (root == nullptr) {
		return;
	}
	free(root->left);
	free(root->right);
	delete root;
}

void connect(node_2* root) {
	if (root == nullptr) {
		return;
	}
	std::queue<node_2*> queue;
	queue.push(root);
	while (!queue.empty()) {
		size_t current_size = queue.size();
		node_2* prev_node = nullptr;
		while (current_size--) {
			node_2* current_node = queue.front();
			queue.pop();
			if (current_node->left != nullptr) {
				queue.push(current_node->left);
			}
			if (current_node->right != nullptr) {
				queue.push(current_node->right);
			}
			if (prev_node != nullptr) {
				prev_node->next = current_node;
			}
			prev_node = current_node;
		}
		prev_node->next = nullptr;
	}
}

void print_next(node_2* current_node) {
	std::cout << "Next node of " << current_node->data << " is ";
	std::cout << (current_node->next != nullptr ? current_node->next->data : -1);
	std::cout << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()