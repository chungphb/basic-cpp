#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_singly_linked_list)

struct node {
	int data;
	node* next;
};

void print(node* head, std::string name) {
	if (head == nullptr) {
		return;
	}
	std::cout << name << ": ";
	node* current_node = head;
	while (current_node != nullptr) {
		std::cout << current_node->data;
		if (current_node->next != nullptr) {
			std::cout << ", ";
		}
		current_node = current_node->next;
	}
	std::cout << std::endl;
}

void free(node* head) {
	if (head == nullptr) {
		return;
	}
	node* current_node = head;
	node* next_node = nullptr;
	while (current_node != nullptr) {
		next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	}
}

// Insert a node

void push(node** head_ref, int data);
void insert_after(node* prev_node, int data);
void append(node** head_ref, int data);

BOOST_AUTO_TEST_CASE(test_1) {
	TEST_MARKER();

	node* head = nullptr;

	// At the front
	push(&head, 0);
	print(head, "After inserting at the front");

	// At the back
	append(&head, 2);
	print(head, "After inserting at the back");

	// After a given node
	insert_after(head, 1);
	print(head, "After inserting after a given node");

	free(head);
}

void push(node** head_ref, int data) {
	if (head_ref == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	new_node->next = *head_ref;
	*head_ref = new_node;
}

void insert_after(node* prev_node, int data) {
	if (prev_node == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}

void append(node** head_ref, int data) {
	if (head_ref == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	new_node->next = nullptr;
	if (*head_ref == nullptr) {
		*head_ref = new_node;
		return;
	}
	node* last_node = *head_ref;
	while (last_node->next != nullptr) {
		last_node = last_node->next;
	}
	last_node->next = new_node;
}

// Remove a node

void remove(node** head_ref, int data);

BOOST_AUTO_TEST_CASE(test_2) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 0);
	append(&head, 1);
	append(&head, 2);
	print(head, "Before removing");

	remove(&head, 1);

	// Test case: When removing the head
	// remove(&head, 0);
	// 
	// Test case: When removing a non-existent element
	// remove(&head, 3);

	print(head, "After removing");

	free(head);
}

void remove(node** head_ref, int data) {
	if (head_ref == nullptr || *head_ref == nullptr) {
		return;
	}
	node* current_node = *head_ref;
	node* prev_node = nullptr;
	// If the removed node is at the front
	if (current_node != nullptr && current_node->data == data) {
		*head_ref = current_node->next;
		delete current_node;
	}
	else {
		// Find the previous node
		while (current_node != nullptr && current_node->data != data) {
			prev_node = current_node;
			current_node = current_node->next;
		}
		// If the removed node is not in the list
		if (current_node == nullptr) {
			return;
		}
		// Otherwise
		prev_node->next = current_node->next;
		delete current_node;
	}
}

// Remove a node at a given position

void remove_at(node** head_ref, int pos);

BOOST_AUTO_TEST_CASE(test_3) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 0);
	append(&head, 1);
	append(&head, 2);
	print(head, "Before removing");

	remove_at(&head, 2);

	// Test case: When removing the head
	// remove(&head, 0);
	// 
	// Test case: When removing an element at a postion outside of the list
	// remove(&head, 3);
	// 
	// Test case: When removing an element at a negative postion
	// remove(&head, -1);

	print(head, "After removing");

	free(head);
}

void remove_at(node** head_ref, int pos) {
	if (head_ref == nullptr || *head_ref == nullptr || pos < 0) {
		return;
	}
	node* current_node = *head_ref;
	node* prev_node = nullptr;
	// If the removed node is at the front
	if (pos == 0) {
		*head_ref = current_node->next;
		delete current_node;
	}
	else {
		// Find the previous node
		for (int i = 0; i < pos && current_node != nullptr; ++i) {
			prev_node = current_node;
			current_node = current_node->next;
		}
		// If the removed node is not in the list
		if (prev_node == nullptr || current_node == nullptr) {
			return;
		}
		// Otherwise
		prev_node->next = current_node->next;
		delete current_node;
	}
}

// Find the length of a list

int length(node* head);

BOOST_AUTO_TEST_CASE(test_4) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 0);
	append(&head, 1);
	append(&head, 2);
	print(head, "List");

	std::cout << "Length: " << length(head) << std::endl;
	// Test case: Zero-length list
	// std::cout << "Length: " << length(nullptr) << std::endl;

	free(head);
}

int length(node* head) {
	int len = 0;
	node* current_node = head;
	while (current_node != nullptr) {
		++len;
		current_node = current_node->next;
	}
	return len;
}

// Reverse a list

void reverse(node** head_ref);

BOOST_AUTO_TEST_CASE(test_5) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 0);
	append(&head, 1);
	append(&head, 2);
	append(&head, 3);
	append(&head, 4);
	print(head, "Before reversing");

	reverse(&head);
	print(head, "After reversing");

	free(head);
}

void reverse(node** head_ref) {
	if (head_ref == nullptr) {
		return;
	}
	node* current_node = *head_ref;
	node* next_node = nullptr;
	node* prev_node = nullptr;
	while (current_node != nullptr) {
		next_node = current_node->next;
		current_node->next = prev_node;
		prev_node = current_node;
		current_node = next_node;
	}
	*head_ref = prev_node;
}

// Sort a list

void split(node* head, node** left_sub_head_ref, node** right_sub_head_ref);
node* merge(node* left_sub_head, node* right_sub_head);
void merge_sort(node** head_ref);

BOOST_AUTO_TEST_CASE(test_6) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 4);
	append(&head, 2);
	append(&head, 0);
	append(&head, 3);
	append(&head, 1);
	print(head, "Before sorting");

	merge_sort(&head);
	print(head, "After sorting");

	free(head);
}

void split(node* head, node** left_sub_head_ref, node** right_sub_head_ref) {
	if (head == nullptr || left_sub_head_ref == nullptr || right_sub_head_ref == nullptr) {
		return;
	}
	node* slow = head;
	node* fast = head->next;
	while (fast != nullptr) {
		fast = fast->next;
		if (fast != nullptr) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*left_sub_head_ref = head;
	*right_sub_head_ref = slow->next;
	slow->next = nullptr;
}

node* merge(node* left_sub_head, node* right_sub_head) {
	if (left_sub_head == nullptr) {
		return right_sub_head;
	}
	if (right_sub_head == nullptr) {
		return left_sub_head;
	}
	node* result = nullptr;
	if (left_sub_head->data < right_sub_head->data) {
		result = left_sub_head;
		result->next = merge(left_sub_head->next, right_sub_head);
	}
	else {
		result = right_sub_head;
		result->next = merge(left_sub_head, right_sub_head->next);
	}
	return result;
}

void merge_sort(node** head_ref) {
	// If the list is empty or has a single element
	if (head_ref == nullptr || *head_ref == nullptr || (*head_ref)->next == nullptr) {
		return;
	}
	node* head = *head_ref;
	node* left_sub_head = nullptr;
	node* right_sub_head = nullptr;
	// Split
	split(head, &left_sub_head, &right_sub_head);
	// Merge
	merge_sort(&left_sub_head);
	merge_sort(&right_sub_head);
	*head_ref = merge(left_sub_head, right_sub_head);
}

// Rotate a list

void rotate(node** head_ref, int rotating_size);
void rotate_2(node** head_ref, int rotating_size);

BOOST_AUTO_TEST_CASE(test_7) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 1);
	append(&head, 2);
	append(&head, 3);
	append(&head, 4);
	append(&head, 5);
	append(&head, 6);
	append(&head, 7);
	append(&head, 8);
	print(head, "Before rotating");

	rotate(&head, 3);
	print(head, "After rotating");

	rotate_2(&head, 3);
	print(head, "After rotating (again)");

	free(head);
}

void rotate(node** head_ref, int rotating_size) {
	if (rotating_size == 0) {
		return;
	}
	node* current_node = *head_ref;
	int current_id = 0;
	// Find the (rotating_size)-th element
	while (current_node != nullptr && current_id < rotating_size - 1) {
		current_node = current_node->next;
		++current_id;
	}
	// If the rotating size is greater than the list size
	if (current_node == nullptr) {
		return;
	}
	// Find the last element
	node* rotating_node = current_node;
	while (current_node->next != nullptr) {
		current_node = current_node->next;
	}
	// Rotate
	current_node->next = *head_ref;
	*head_ref = rotating_node->next;
	rotating_node->next = nullptr;
}

void rotate_2(node** head_ref, int rotating_size) {
	if (rotating_size == 0) {
		return;
	}
	// Find the last element
	node* current_node = *head_ref;
	while (current_node->next != nullptr) {
		current_node = current_node->next;
	}
	current_node->next = *head_ref;
	// Rotate
	current_node = *head_ref;
	for (int i = 1; i < rotating_size; ++i) {
		current_node = current_node->next;
	}
	*head_ref = current_node->next;
	current_node->next = nullptr;
}

// Detect and remove loop in a list

void remove_loop(node* head, node* loop_node);
void detect_and_remove_loop(node* head);
node* create_new_node(int data);

BOOST_AUTO_TEST_CASE(test_8) {
	TEST_MARKER();

	node* head = create_new_node(1);
	head->next = create_new_node(2);
	head->next->next = create_new_node(3);
	head->next->next->next = create_new_node(4);
	head->next->next->next->next = create_new_node(5);
	head->next->next->next->next->next = head->next->next;

	detect_and_remove_loop(head);
	print(head, "After removing loop");

	free(head);
}

void remove_loop(node* head, node* loop_node) {
	node* start_node = loop_node;
	node* end_node = loop_node;
	// Find the loop size
	int loop_size = 1;
	while (start_node->next != end_node) {
		start_node = start_node->next;
		++loop_size;
	}
	// Set the two pointers
	start_node = head;
	end_node = head;
	for (int i = 0; i < loop_size; i++) {
		end_node = end_node->next;
	}
	// Find the start node of the loop
	while (start_node != end_node) {
		start_node = start_node->next;
		end_node = end_node->next;
	}
	// Find the end node of the loop
	while (end_node->next != start_node) {
		end_node = end_node->next;
	}
	// Remove the loop
	end_node->next = nullptr;
}

void detect_and_remove_loop(node* head) {
	node* slow = head;
	node* fast = head;
	while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			remove_loop(head, slow);
			return;
		}
	}
}

node* create_new_node(int data) {
	node* new_node = new node();
	new_node->data = data;
	new_node->next = nullptr;
	return new_node;
}

BOOST_AUTO_TEST_SUITE_END()