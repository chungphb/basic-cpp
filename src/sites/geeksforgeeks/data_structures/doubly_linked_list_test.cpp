#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_doubly_linked_list)

struct node {
	int data;
	node* next;
	node* prev;
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
	new_node->prev = nullptr;
	if (*head_ref != nullptr) {
		(*head_ref)->prev = new_node;
	}
	*head_ref = new_node;
}

void insert_after(node* prev_node, int data) {
	if (prev_node == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	prev_node->next = new_node;
	if (new_node->next != nullptr) {
		new_node->next->prev = new_node;
	}
}

void append(node** head_ref, int data) {
	if (head_ref == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	new_node->next = nullptr;
	if (*head_ref == nullptr) {
		new_node->prev = nullptr;
		*head_ref = new_node;
		return;
	}
	node* last_node = *head_ref;
	while (last_node->next != nullptr) {
		last_node = last_node->next;
	}
	last_node->next = new_node;
	new_node->prev = last_node;
}

// Remove a node

void remove(node** head_ref, node* removed_node);

BOOST_AUTO_TEST_CASE(test_2) {
	TEST_MARKER();

	node* head = nullptr;
	append(&head, 0);
	append(&head, 1);
	append(&head, 2);
	print(head, "Before removing");

	remove(&head, head->next);
	print(head, "After removing");

	// Test case: Remove the head
	// remove(&head, head);
	//
	// Test case: Remove non-existent element
	// remove(&head, nullptr);

	free(head);
}

void remove(node** head_ref, node* removed_node) {
	if (head_ref == nullptr || *head_ref == nullptr || removed_node == nullptr) {
		return;
	}
	// If the removed node is the head
	if (removed_node == *head_ref) {
		*head_ref = removed_node->next;
	}
	// Reset the next node's prev pointer
	if (removed_node->next != nullptr) {
		removed_node->next->prev = removed_node->prev;
	}
	// Reset the previous node's next pointer
	if (removed_node->prev != nullptr) {
		removed_node->prev->next = removed_node->next;
	}
	// Remove the node
	delete removed_node;
}

// Reverse a list

void reverse(node** head_ref);

BOOST_AUTO_TEST_CASE(test_3) {
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
	node* prev_node = nullptr;
	while (current_node != nullptr) {
		prev_node = current_node->prev;
		current_node->prev = current_node->next;
		current_node->next = prev_node;
		// Use prev pointer instead of next pointer because they have already been swapped
		current_node = current_node->prev;
	}
	if (prev_node != nullptr) {
		// prev_node is the node right behind of the new head (or right in front of its in the old list)
		*head_ref = prev_node->prev;
	}
}

// Merge sort

void split(node* head, node** left_sub_head_ref, node** right_sub_head_ref);
node* merge(node* left_sub_head, node* right_sub_head);
void merge_sort(node** head_ref);

BOOST_AUTO_TEST_CASE(test_4) {
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
	node* fast = head;
	while (fast->next != nullptr && fast->next->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
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
	if (result->next != nullptr) {
		result->next->prev = result;
	}
	result->prev = nullptr;
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

BOOST_AUTO_TEST_SUITE_END()