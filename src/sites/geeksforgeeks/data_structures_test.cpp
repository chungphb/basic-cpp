#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include "test_util.h"

// ARRAY

BOOST_AUTO_TEST_SUITE(test_array)

void print(int arr[], int size, std::string name) {
	std::cout << name << ": ";
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i];
		if (i != size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

// Search, insert, and delete in an unsorted array
BOOST_AUTO_TEST_CASE(test_1) {
	TEST_MARKER();

	int arr[20] = {1, 5, 4, 11, 3, 12, 2, 6, 8, 7, 9, 10};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 12;

	{ // Search
		int searched_element = 4;
		int searched_index = -1;
		for (int i = 0; i < size; ++i) {
			if (arr[i] == searched_element) {
				searched_index = i;
			}
		}
		if (searched_index != -1) {
			std::cout << "Index of the searched element: " << searched_index << std::endl;
		}
		else {
			std::cout << "Searched element not exists" << std::endl;
		}
	}

	{ // Insert
		print(arr, size, "Before inserting");
		int inserted_element = 4;
		if (size < capacity) {
			arr[size] = inserted_element;
			++size;
		}
		print(arr, size, "After inserting");
	}

	{ // Delete
		print(arr, size, "Before deleting");
		int deleted_element = 12;
		int deleted_index = -1;
		for (int i = 0; i < size; ++i) {
			if (arr[i] == deleted_index) {
				deleted_index = i;
			}
		}
		if (deleted_index != -1) {
			--size;
			for (int i = deleted_index; i < size; ++i) {
				arr[i] = arr[i + 1];
			}
			print(arr, size, "After deleting");
		} else {
			std::cout << "Deleted element not exists" << std::endl;
		}
	}
}

// Search, insert, and delete in an sorted array

int binary_search(int arr[], int low, int high, int key);

BOOST_AUTO_TEST_CASE(test_2) {
	TEST_MARKER();

	int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 12;

	{ // Search
		int searched_element = 4;
		int searched_index = binary_search(arr, 0, size - 1, searched_element);
		if (searched_index != -1) {
			std::cout << "Index of the searched element: " << searched_index << std::endl;
		} else {
			std::cout << "Searched element not exists" << std::endl;
		}
	}

	{ // Insert
		print(arr, size, "Before inserting");
		int inserted_element = 4;
		if (size < capacity) {
			int i;
			for (i = size; i > 0 && arr[i - 1] > inserted_element; --i) {
				arr[i] = arr[i - 1];
			}
			arr[i] = inserted_element;
			++size;
		}
		print(arr, size, "After inserting");
	}

	{ // Delete
		print(arr, size, "Before deleting");
		int deleted_element = 12;
		int deleted_index = binary_search(arr, 0, size - 1, deleted_element);
		if (deleted_index != -1) {
			--size;
			for (int i = deleted_index; i < size; ++i) {
				arr[i] = arr[i + 1];
			}
			print(arr, size, "After deleting");
		} else {
			std::cout << "Deleted element not exists" << std::endl;
		}
	}
}

int binary_search(int arr[], int low, int high, int key) {
	if (high < low) {
		return -1;
	}
	int mid = (low + high) >> 1;
	if (arr[mid] == key) {
		return mid;
	} else if (arr[mid] < key) {
		return binary_search(arr, mid + 1, high, key);
	} else {
		return binary_search(arr, low, mid - 1, key);
	}
}

// Reverse an array
BOOST_AUTO_TEST_CASE(test_3) {
	TEST_MARKER();

	int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 12;
	// Test case: When array size is an odd number.
	// int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	// int size = 11;

	print(arr, size, "Before reversing");
	int temp;
	for (int i = 0; i < size / 2; ++i) {
		temp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temp;
	}
	print(arr, size, "After reversing");
}

// Find the leaders of an array
BOOST_AUTO_TEST_CASE(test_4) {
	TEST_MARKER();

	int arr[20] = {12, 8, 9, 7, 1, 3};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 6;

	print(arr, size, "Array");
	std::cout << "Leaders: " << std::endl;

	int max = INT_MIN;
	for (int i = size - 1; i >= 0; --i) {
		if (arr[i] > max) {
			std::cout << arr[i] << std::endl;
			max = arr[i];
		}
	}
}

// Find two elements of an array with a given sum

void merge(int arr[], int low, int mid, int high);
void merge_sort(int arr[], int low, int high);

BOOST_AUTO_TEST_CASE(test_5) {
	TEST_MARKER();

	const int SUM = 13;
	int arr[20] = {5, 7, 1, 9, 4, 6};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 6;

	std::cout << "Sum: " << SUM << std::endl;
	print(arr, size, "Array");

	// Sort
	merge_sort(arr, 0, size - 1);

	// Apply the Two-Pointers technique
	int low = 0;
	int high = size - 1;
	while (low < high) {
		if (arr[low] + arr[high] == SUM) {
			std::cout << "The needed pair of elements is " << arr[low] << " and " << arr[high] << std::endl;
			break;
		} else if (arr[low] + arr[high] > SUM) {
			--high;
		} else {
			++low;
		}
	}
}

void merge(int arr[], int low, int mid, int high) {
	int left_sub_size = mid - low + 1;
	int* left_sub = new int[left_sub_size];
	for (int i = 0; i < left_sub_size; ++i) {
		left_sub[i] = arr[low + i];
	}

	int right_sub_size = high - mid;
	int* right_sub = new int[right_sub_size];
	for (int i = 0; i < right_sub_size; ++i) {
		right_sub[i] = arr[mid + 1 + i];
	}

	int left_sub_id = 0;
	int right_sub_id = 0;
	int merge_id = low;
	while (left_sub_id < left_sub_size && right_sub_id < right_sub_size) {
		if (left_sub[left_sub_id] < right_sub[right_sub_id]) {
			arr[merge_id] = left_sub[left_sub_id];
			++left_sub_id;
		} else {
			arr[merge_id] = right_sub[right_sub_id];
			++right_sub_id;
		}
		++merge_id;
	}

	while (left_sub_id < left_sub_size) {
		arr[merge_id] = left_sub[left_sub_id];
		++left_sub_id;
		++merge_id;
	}

	while (right_sub_id < right_sub_id) {
		arr[merge_id] = right_sub[right_sub_id];
		++right_sub_id;
		++merge_id;
	}

	delete[] left_sub;
	delete[] right_sub;
}

void merge_sort(int arr[], int low, int high) {
	if (low >= high) {
		return;
	}
	int mid = (low + high) >> 1;
	merge_sort(arr, low, mid);
	merge_sort(arr, mid + 1, high);
	merge(arr, low, mid, high);
}

// Find the majority element in an array
BOOST_AUTO_TEST_CASE(test_6) {
	TEST_MARKER();

	int arr[20] = {4, 12, 13, 4, 12, 4, 4};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 7;

	print(arr, size, "Array");

	// Boyer-Moore majority voting algorithm
	int majority_element = arr[0];
	int majority_count = 1;
	for (int i = 1; i < size; ++i) {
		if (majority_element == arr[i]) {
			++majority_count;
		} else {
			--majority_count;
		}
		if (majority_count == 0) {
			majority_element = arr[i];
			majority_count = 1;
		}
	}
	majority_count = 0;
	for (int i = 0; i < size; ++i) {
		if (majority_element == arr[i]) {
			++majority_count;
		}
	}
	if (majority_count > (size >> 1)) {
		std::cout << "The majority element is " << majority_element << std::endl;
	} else {
		std::cout << "There is not a majority element" << std::endl;
	}
}

// Find the largest sum contiguous subarray
BOOST_AUTO_TEST_CASE(test_7) {
	TEST_MARKER();

	int arr[20] = {5, -1, -2, 4, 0, -4, 7, -2};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 8;

	print(arr, size, "Array");

	// Kadane's Algorithm
	int start = 0;
	int end = 0;
	int mark = 0;
	int max_ending_here = 0;
	int max_so_far = INT_MIN;
	for (int i = 0; i < size; ++i)
	{
		max_ending_here = max_ending_here + arr[i];
		if (max_ending_here > max_so_far) {
			max_so_far = max_ending_here;
			start = mark;
			end = i;
		}
		if (max_ending_here < 0) {
			max_ending_here = 0;
			mark = i + 1;
		}
	}
	std::cout << "The largest sum contiguous subarray starts from " << start << " to " << end << std::endl;
	std::cout << "Maxmimum contiguous sum: " << max_so_far << std::endl;
}

// Find the missing number in a range
BOOST_AUTO_TEST_CASE(test_8) {
	TEST_MARKER();

	int arr[20] = {9, 3, 2, 1, 7, 6, 4, 8};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 8;

	print(arr, size, "Array");

	// Use summation
	int n = 9;
	int sum = (n * (n + 1)) >> 1;
	for (int i = 0; i < size; ++i) {
		sum -= arr[i];
	}
	std::cout << "The missing number is " << sum << std::endl;

	// Use XOR
	int result_1 = arr[0];
	for (int i = 1; i < size; ++i) {
		result_1 ^= arr[i];
	}
	int result_2 = 1;
	for (int k = 2; k <= n; ++k) {
		result_2 ^= k;
	}
	std::cout << "The missing number is " << (result_1 ^ result_2) << std::endl;
}

// Rotate an array

void reverse(int arr[], int start, int end);
void swap_block(int arr[], int block_1_start, int block_2_start, int swap_size);
void rotate(int arr[], int rotating_size, int size);

BOOST_AUTO_TEST_CASE(test_9) {
	TEST_MARKER();

	int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 8;
	int rotating_size = 3;

	print(arr, size, "Before rotating");

	// Reversal algorithm
	reverse(arr, 0, rotating_size - 1);
	reverse(arr, rotating_size, size - 1);
	reverse(arr, 0, size - 1);
	print(arr, size, "After rotating");

	// Block swap algorithm
	// 
	// For example: [1 2 3 | 4 5 6 7 8]
	// Step 1 (rotating_size = 3, size = 8):
	// - Swap (1 2 3) to (6 7 8) since rotating_size = 3 < 5 = size - rotating_size
	// - Result: [6 7 8 | 4 5] 1 2 3			((1 2 3) is in the right place)
	// Step 2 (rotating_size = 3, size = 5):
	// - Swap (6 7) to (4 5) since rotating_size = 3 > 2 = size - rotating_size
	// - Result: 4 5 [8 | 6 7] 1 2 3			((4 5) is in the right place)
	// Step 3 (rotating_size = 3 - (5 - 3) = 1, size = 3):
	// - Swap (8) to (7) since rotating_size = 1 < 2 = size - rotating_size
	// - Result: 4 5 [7 | 6] 8 1 2 3			((8) is in the right place)
	// Step 4 (rotating_size = 1, size = 2):
	// - Swap (7) to (6) since rotating_size = 1 = size - rotating_size
	// - Result: 4 5 6 7 8 1 2 3				((6 7) is in the right place)
	rotate(arr, rotating_size, size);
	print(arr, size, "After rotating (again)");
}

void reverse(int arr[], int start, int end) {
	int temp;
	while (start < end) {
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		++start;
		--end;
	}
}

void swap_block(int arr[], int block_1_start, int block_2_start, int swap_size) {
	int temp;
	for (int i = 0; i < swap_size; ++i) {
		temp = arr[block_1_start + i];
		arr[block_1_start + i] = arr[block_2_start + i];
		arr[block_2_start + i] = temp;
	}
}

void rotate(int arr[], int rotating_size, int size) {
	if (rotating_size == 0 || rotating_size == size) {
		return;
	}
	if (rotating_size == size - rotating_size) {
		swap_block(arr, 0, size - rotating_size, rotating_size);
		return;
	}

	if (rotating_size < size - rotating_size) {
		swap_block(arr, 0, size - rotating_size, rotating_size);
		rotate(arr, rotating_size, size - rotating_size);
	} else {
		swap_block(arr, 0, rotating_size, size - rotating_size);
		rotate(arr + (size - rotating_size), rotating_size - (size - rotating_size), rotating_size);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// LINKED LIST

BOOST_AUTO_TEST_SUITE(test_linked_list)

// SINGLY LINKED LIST

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
	} else {
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
	} else {
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
	} else {
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

// CIRCULAR LINKED LIST

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
	} else {
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
	} else {
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
	} else {
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

// SINGLY LINKED LIST

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
	} else {
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

BOOST_AUTO_TEST_SUITE_END()