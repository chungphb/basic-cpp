#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include "test_util.h"

BOOST_AUTO_TEST_SUITE(test_circular_linked_list)

struct node {
	int data;
	node* next;
};

void print(node* last, std::string name) {
	if (last == nullptr) {
		return;
	}
	std::cout << name << ": ";
	node* head = last->next;
	node* current_node = last->next;
	do {
		std::cout << current_node->data;
		if (current_node->next != head) {
			std::cout << ", ";
		}
		current_node = current_node->next;
	} while (current_node != head);
	std::cout << std::endl;
}

void free(node* last) {
	if (last == nullptr) {
		return;
	}
	// Store a (const) pointer to the head of the list because the last pointer might be updated while processing
	node* head = last->next;
	node* current_node = last->next;
	node* next_node = nullptr;
	do {
		next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	} while (current_node != head);
}

// Insert a node

void insert_to_empty(node** last_ref, int data);
void push(node** last_ref, int data);
void append(node** last_ref, int data);
void insert_after(node** last_ref, int data, int element);

BOOST_AUTO_TEST_CASE(test_1) {
	TEST_MARKER();

	node* last = nullptr;

	// To an empty list
	insert_to_empty(&last, 1);

	// At the front
	push(&last, 0);

	// At the back
	append(&last, 3);

	// After a given element
	insert_after(&last, 2, 1);

	print(last, "List");

	free(last);
}

void insert_to_empty(node** last_ref, int data) {
	if (last_ref == nullptr || *last_ref != nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	new_node->next = new_node;
	*last_ref = new_node;
}

void push(node** last_ref, int data) {
	if (last_ref == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	if (*last_ref == nullptr) {
		new_node->next = new_node;
		*last_ref = new_node;
	}
	else {
		new_node->next = (*last_ref)->next;
		(*last_ref)->next = new_node;
	}
}

void append(node** last_ref, int data) {
	if (last_ref == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	if (*last_ref == nullptr) {
		new_node->next = new_node;
		*last_ref = new_node;
	}
	else {
		new_node->next = (*last_ref)->next;
		(*last_ref)->next = new_node;
		*last_ref = new_node;
	}

}

void insert_after(node** last_ref, int data, int element) {
	if (last_ref == nullptr || *last_ref == nullptr) {
		return;
	}
	node* last = *last_ref;
	node* head = last->next;
	node* current_node = last->next;
	do {
		if (current_node->data == element) {
			node* new_node = new node();
			new_node->data = data;
			new_node->next = current_node->next;
			current_node->next = new_node;
			if (current_node == last) {
				last = new_node;
			}
			return;
		}
		current_node = current_node->next;
	} while (current_node != head);
	std::cout << "There is no element " << element << " in the list" << std::endl;
}

// Split a list

void split(node* head, node** left_sub_head_ref, node** right_sub_head_ref);
void print_h(node* head, std::string name);
void free_h(node* head);
void push_h(node** head_ref, int data);

BOOST_AUTO_TEST_CASE(test_2) {
	TEST_MARKER();

	node* head = nullptr;
	push_h(&head, 4);
	push_h(&head, 3);
	push_h(&head, 2);
	push_h(&head, 1);
	print_h(head, "List");

	node* left_sub_head = nullptr;
	node* right_sub_head = nullptr;
	split(head, &left_sub_head, &right_sub_head);
	print_h(left_sub_head, "Left sublist");
	print_h(right_sub_head, "Right sublist");

	free_h(left_sub_head);
	free_h(right_sub_head);
}

void split(node* head, node** left_sub_head_ref, node** right_sub_head_ref) {
	if (head == nullptr || left_sub_head_ref == nullptr || right_sub_head_ref == nullptr) {
		return;
	}
	// If there is only one element in the list
	if (head->next == head) {
		*left_sub_head_ref = head;
	}
	// Otherwise
	node* slow = head;
	node* fast = head;
	while (fast->next != head && fast->next->next != head) {
		slow = slow->next;
		fast = fast->next->next;
	}
	// If the size of the list is an even number
	if (fast->next->next == head) {
		fast = fast->next;
	}
	// Split
	*left_sub_head_ref = head;
	*right_sub_head_ref = slow->next;
	fast->next = slow->next;
	slow->next = head;
}

void print_h(node* head, std::string name) {
	if (head == nullptr) {
		return;
	}
	std::cout << name << ": ";
	node* current_node = head;
	do {
		std::cout << current_node->data;
		if (current_node->next != head) {
			std::cout << ", ";
		}
		current_node = current_node->next;
	} while (current_node != head);
	std::cout << std::endl;
}

void free_h(node* head) {
	if (head == nullptr) {
		return;
	}
	node* current_node = head;
	node* next_node = nullptr;
	do {
		next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	} while (current_node != head);
}

void push_h(node** head_ref, int data) {
	if (head_ref == nullptr) {
		return;
	}
	node* new_node = new node();
	new_node->data = data;
	if (*head_ref == nullptr) {
		new_node->next = new_node;
	}
	else {
		new_node->next = *head_ref;
		// Find the last element
		node* current_node = *head_ref;
		while (current_node->next != *head_ref) {
			current_node = current_node->next;
		}
		// Update the last element's next pointer
		current_node->next = new_node;
	}
	*head_ref = new_node;
}

BOOST_AUTO_TEST_SUITE_END()