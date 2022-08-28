#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include "test_util.h"

// Note: Use a dummy head when needed.

BOOST_AUTO_TEST_SUITE(test_linked_list_leetcode)

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

void print(ListNode* head) {
	ListNode* curr = head;
	while (curr != nullptr) {
		std::cout << curr->val << " ";
		curr = curr->next;
	}
	std::cout << "\n";
}

void release(ListNode* head) {
	ListNode* curr = head;
	while (curr != nullptr) {
		ListNode* next = curr->next;
		delete curr;
		curr = next;
	}
	std::cout << "\n";
}

// "Remove Duplicates from Sorted List II" problem (LeetCode #81)
// Problem:
// - Given the head of a sorted linked list.
// - Delete all nodes that have duplicate numbers.
// Input: head = [1,2,3,3,4,4,5]
// Output: [1,2,5]

BOOST_AUTO_TEST_SUITE(remove_duplicates_suite)

ListNode* deleteDuplicates(ListNode* head) {
	ListNode* curr = head;
	bool deleteCurr = false;
	ListNode* prev = nullptr;
	ListNode* res = nullptr;
	while (curr != nullptr) {
		// Remove the duplicated nodes
		if (curr->next != nullptr && curr->next->val == curr->val) {
			deleteCurr = true;
			ListNode* oldNext = curr->next;
			curr->next = oldNext->next;
			delete oldNext;
			continue;
		}
		
		// Remove the current node if it is duplicated
		ListNode* oldNext = curr->next;
		if (deleteCurr) {
			if (prev != nullptr) {
				prev->next = oldNext;
			}
			delete curr;
		} else {
			if (res == nullptr) {
				res = curr;
			}
			prev = curr;
			curr = curr->next;
		}
		curr = oldNext;
		deleteCurr = false;
	}
	return res;
}

BOOST_AUTO_TEST_CASE(remove_duplicates_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(3);
		head->next->next->next->next = new ListNode(4);
		head->next->next->next->next->next = new ListNode(4);
		head->next->next->next->next->next->next = new ListNode(5);
		std::cout << "Original: ";
		print(head);
		ListNode* res = deleteDuplicates(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(1);
		head->next->next = new ListNode(1);
		head->next->next->next = new ListNode(2);
		head->next->next->next->next = new ListNode(3);
		std::cout << "Original: ";
		print(head);
		ListNode* res = deleteDuplicates(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		head->next = new ListNode(1);
		head->next->next = new ListNode(2);
		head->next->next->next = new ListNode(2);
		head->next->next->next->next = new ListNode(3);
		head->next->next->next->next->next = new ListNode(3);
		std::cout << "Original: ";
		print(head);
		ListNode* res = deleteDuplicates(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 4
		ListNode* head = new ListNode(1);
		head->next = new ListNode(1);
		head->next->next = new ListNode(1);
		head->next->next->next = new ListNode(1);
		head->next->next->next->next = new ListNode(1);
		std::cout << "Original: ";
		print(head);
		ListNode* res = deleteDuplicates(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 5
		ListNode* head = new ListNode(1);
		std::cout << "Original: ";
		print(head);
		ListNode* res = deleteDuplicates(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 6
		ListNode* head = nullptr;
		std::cout << "Original: ";
		print(head);
		ListNode* res = deleteDuplicates(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Reverse Linked List" problem (LeetCode #206)
// Problem:
// - Given the head of a singly linked list.
// - Reverse the list, and return the reversed list.
// Input: head = [1,2,3]
// Output: [3,2,1]

BOOST_AUTO_TEST_SUITE(reversed_linked_list_suite)

ListNode* reverseList(ListNode* head) {
	ListNode* curr = head;
	ListNode* prev = nullptr;
	while (curr != nullptr) {
		ListNode* oldNext = curr->next;
		curr->next = prev;
		prev = curr;
		curr = oldNext;
	}
	return prev;
}

BOOST_AUTO_TEST_CASE(reversed_linked_list_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode * head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseList(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseList(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 3
		ListNode* head = nullptr;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseList(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Reverse Linked List II" problem (LeetCode #92)
// Problem:
// - Given the head of a singly linked list and two integers left and right where left <= right.
// - Reverse the nodes of the list from position left to position right, and return the reversed list.
// Input: head = [1,2,3,4,5], left = 2, right = 4
// Output: [1,4,3,2,5]

BOOST_AUTO_TEST_SUITE(reversed_linked_list_2_suite)

ListNode* reverseBetween(ListNode* head, int left, int right) {
	if (left == right) {
		return head;
	}
	int id = 0;
	ListNode* curr = head;
	ListNode* prev = nullptr;
	ListNode* leftNode = nullptr;
	ListNode* prevLeftNode = nullptr;
	ListNode* rightNode = nullptr;
	ListNode* nextRightNode = nullptr;
	while (curr != nullptr) {
		ListNode* oldNext = curr->next;
		++id;
		if (id > left && id < right) {
			curr->next = prev;
		} else if (id == left) {
			leftNode = curr;
			prevLeftNode = prev;
		} else if (id == right) {
			rightNode = curr;
			nextRightNode = oldNext;
			curr->next = prev;
		}
		prev = curr;
		curr = oldNext;
	}
	leftNode->next = nextRightNode;
	if (prevLeftNode != nullptr) {
		prevLeftNode->next = rightNode;
	} else {
		head = rightNode;
	}
	return head;
}

BOOST_AUTO_TEST_CASE(reversed_linked_list_2_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int left = 2;
		int right = 4;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseBetween(head, left, right);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int left = 1;
		int right = 4;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseBetween(head, left, right);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int left = 2;
		int right = 5;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseBetween(head, left, right);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 4
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int left = 1;
		int right = 5;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseBetween(head, left, right);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 5
		ListNode* head = new ListNode(1);
		int left = 1;
		int right = 1;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseBetween(head, left, right);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 6
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int left = 2;
		int right = 2;
		std::cout << "Original: ";
		print(head);
		ListNode* res = reverseBetween(head, left, right);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Sort List" problem (LeetCode #148)
// Problem:
// - Given the head of a linked list.
// - Return the list after sorting it in ascending order.
// Input: head = [4,2,1,3]
// Output: [1,2,3,4]

BOOST_AUTO_TEST_SUITE(sort_list_suite)

ListNode* merge(ListNode* list1, ListNode* list2) {
	if (list1 == nullptr) {
		return list2;
	}

	if (list2 == nullptr) {
		return list1;
	}

	ListNode* dummyHead = new ListNode();
	ListNode* curr = dummyHead;
	while (list1 != nullptr && list2 != nullptr) {
		if (list1->val < list2->val) {
			curr->next = list1;
			list1 = list1->next;
		} else {
			curr->next = list2;
			list2 = list2->next;
		}
		curr = curr->next;
	}

	while (list1 != nullptr) {
		curr->next = list1;
		list1 = list1->next;
		curr = curr->next;
	}

	while (list2 != nullptr) {
		curr->next = list2;
		list2 = list2->next;
		curr = curr->next;
	}

	ListNode* head = dummyHead->next;
	delete dummyHead;
	return head;
}

ListNode* mergeSort(ListNode* head) {
	// Return if invalid
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	// Find the middle node
	ListNode* fast = head->next;
	ListNode* slow = head;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	ListNode* midPrev = slow;
	ListNode* mid = midPrev->next;
	midPrev->next = nullptr;

	// Sort the left
	ListNode* left = mergeSort(head);

	// Sort the right
	ListNode* right = mergeSort(mid);

	// Merge the list
	return merge(left, right);
}

ListNode* sortList(ListNode* head) {
	return mergeSort(head);
}

BOOST_AUTO_TEST_CASE(sort_list_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(4);
		head->next = new ListNode(2);
		head->next->next = new ListNode(1);
		head->next->next->next = new ListNode(3);
		std::cout << "Original: ";
		print(head);
		ListNode* res = mergeSort(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 2
		ListNode* head = new ListNode(9);
		head->next = new ListNode(4);
		head->next->next = new ListNode(7);
		head->next->next->next = new ListNode(3);
		std::cout << "Original: ";
		print(head);
		ListNode* res = mergeSort(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		std::cout << "Original: ";
		print(head);
		ListNode* res = mergeSort(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 4
		ListNode* head = nullptr;
		std::cout << "Original: ";
		print(head);
		ListNode* res = mergeSort(head);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()