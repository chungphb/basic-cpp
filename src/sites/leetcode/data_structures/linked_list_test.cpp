#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include "test_util.h"

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
// Input:
// Output:

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
	TEST_MARKER

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

BOOST_AUTO_TEST_SUITE_END()