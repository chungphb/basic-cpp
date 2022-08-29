#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <queue>

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

// "Reorder List" problem (LeetCode #143)
// Problem:
// - You are given the head of a singly linked-list: L0 -> L1 -> ... -> L(n - 1) -> Ln
// - Reorder the list to be on the following form: L0 -> Ln -> L1 -> L(n - 1) -> ...
// Input:  head = [1,2,3,4]
// Output: [1,4,2,3]

BOOST_AUTO_TEST_SUITE(reorder_list_suite)

ListNode* getMid(ListNode* head) {
	ListNode* fast = head->next;
	ListNode* slow = head;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

ListNode* reverse(ListNode* head) {
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

void reorderList(ListNode* head) {
	ListNode* mid = getMid(head);
	ListNode* list1 = head;
	ListNode* list2 = reverse(mid->next);
	mid->next = nullptr;

	ListNode* dummyHead = new ListNode();
	ListNode* curr = dummyHead;
	bool flag = true;
	while (list1 != nullptr && list2 != nullptr) {
		if (flag) {
			curr->next = list1;
			list1 = list1->next;
		} else {
			curr->next = list2;
			list2 = list2->next;
		}
		curr = curr->next;
		flag = !flag;
	}
	if (list1 != nullptr) {
		curr->next = list1;
	}
	if (list2 != nullptr) {
		curr->next = list2;
	}
	head = dummyHead->next;
	delete dummyHead;
}

BOOST_AUTO_TEST_CASE(reorder_list_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		std::cout << "Original: ";
		print(head);
		reorderList(head);
		std::cout << "After: ";
		print(head);
		std::cout << "\n";
		release(head);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		std::cout << "Original: ";
		print(head);
		reorderList(head);
		std::cout << "After: ";
		print(head);
		std::cout << "\n";
		release(head);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		std::cout << "Original: ";
		print(head);
		reorderList(head);
		std::cout << "After: ";
		print(head);
		std::cout << "\n";
		release(head);
	}

	{ // Test 4
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		std::cout << "Original: ";
		print(head);
		reorderList(head);
		std::cout << "After: ";
		print(head);
		std::cout << "\n";
		release(head);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Rotate List" problem (LeetCode #61)
// Problem:
// - Given the head of a linked list.
// - Rotate the list to the right by k places.
// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]

BOOST_AUTO_TEST_SUITE(rotate_list_suite)

ListNode* rotateRight(ListNode* head, int k) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	int size = 0;
	ListNode* curr = head;
	ListNode* prev = nullptr;
	while (curr != nullptr) {
		prev = curr;
		curr = curr->next;
		++size;
	}
	prev->next = head;
	int offset = size - k % size;

	curr = head;
	prev = nullptr;
	for (int i = 0; i < offset; ++i) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = nullptr;
	return curr;
}

BOOST_AUTO_TEST_CASE(rotate_list_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		int k = 2;
		std::cout << "Original: ";
		print(head);
		ListNode* res = rotateRight(head, k);
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
		int k = 4;
		std::cout << "Original: ";
		print(head);
		ListNode* res = rotateRight(head, k);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 3
		ListNode* head = new ListNode(0);
		head->next = new ListNode(1);
		head->next->next = new ListNode(2);
		int k = 13;
		std::cout << "Original: ";
		print(head);
		ListNode* res = rotateRight(head, k);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 4
		ListNode* head = new ListNode(0);
		int k = 13;
		std::cout << "Original: ";
		print(head);
		ListNode* res = rotateRight(head, k);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 5
		ListNode* head = nullptr;
		int k = 13;
		std::cout << "Original: ";
		print(head);
		ListNode* res = rotateRight(head, k);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Remove Linked List Elements" problem (LeetCode #203)
// Problem:
// - Given the head of a linked list and an integer val.
// - Remove all the nodes of the linked list that has Node.val == val.
// Input: head = [1,2,6,3,4,5,6], val = 6
// Output: [1,2,3,4,5]

BOOST_AUTO_TEST_SUITE(remove_elements_suite)

ListNode* removeElements(ListNode* head, int val) {
	ListNode* dummyHead = new ListNode();
	dummyHead->next = head;
	ListNode* prev = dummyHead;
	ListNode* curr = head;
	while (curr != nullptr) {
		ListNode* next = curr->next;
		if (curr->val == val) {
			delete curr;
			prev->next = next;
		}
		else {
			prev = curr;
		}
		curr = next;
	}
	head = dummyHead->next;
	delete dummyHead;
	return head;
}

BOOST_AUTO_TEST_CASE(remove_elements_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(6);
		head->next->next->next = new ListNode(3);
		head->next->next->next->next = new ListNode(4);
		head->next->next->next->next->next = new ListNode(5);
		head->next->next->next->next->next->next = new ListNode(6);
		int val = 6;
		std::cout << "Original: ";
		print(head);
		ListNode* res = removeElements(head, val);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 2
		ListNode* head = new ListNode(7);
		head->next = new ListNode(7);
		head->next->next = new ListNode(7);
		head->next->next->next = new ListNode(7);
		int val = 7;
		std::cout << "Original: ";
		print(head);
		ListNode* res = removeElements(head, val);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}

	{ // Test 3
		ListNode* head = nullptr;
		int val = 1;
		std::cout << "Original: ";
		print(head);
		ListNode* res = removeElements(head, val);
		std::cout << "After: ";
		print(res);
		std::cout << "\n";
		release(res);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Palindrome Linked List" problem (LeetCode #234)
// Problem:
// - Given the head of a singly linked list.
// - Return true if it is a palindrome or false otherwise.
// Input: head = [1,2,2,1]
// Output: true

BOOST_AUTO_TEST_SUITE(palindrome_suite)

ListNode* getMid(ListNode* head) {
	ListNode* fast = head->next;
	ListNode* slow = head;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

ListNode* reverse(ListNode* head) {
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


bool isPalindrome(ListNode* head) {
	if (head == nullptr) {
		return true;
	}
	ListNode* left = head;
	ListNode* mid = getMid(head);
	ListNode* right = reverse(mid->next);
	ListNode* rightHead = right; // For deallocating
	mid->next = nullptr;

	while (left != nullptr && right != nullptr) {
		if (left->val != right->val) {
			release(rightHead); // For deallocating
			return false;
		}
		left = left->next;
		right = right->next;
	}
	release(rightHead); // For deallocating
	return true;
}

BOOST_AUTO_TEST_CASE(palindrome_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(2);
		head->next->next->next = new ListNode(1);
		std::cout << "Original: ";
		print(head);
		bool res = isPalindrome(head);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(head);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		std::cout << "Original: ";
		print(head);
		bool res = isPalindrome(head);
		std::cout << std::boolalpha << "Result: " << res << "\n\n";
		release(head);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Add Two Numbers" problem (LeetCode #2)
// Problem:
// - You are given two non-empty linked lists representing two non-negative integers.
// - The digits are stored in reverse order, and each of their nodes contains a single digit.
// - Add the two numbers and return the sum as a linked list.
// Input:
// Output:

BOOST_AUTO_TEST_SUITE(add_two_numbers_suite)

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* dummyHead = new ListNode();
	ListNode* prev = dummyHead;
	ListNode* curr = l1;
	prev->next = curr;

	// The main loop
	ListNode* prevL1 = nullptr;
	ListNode* prevL2 = nullptr;
	int offset = 0;
	while (l1 != nullptr && l2 != nullptr) {
		int sum = l1->val + l2->val + offset;
		curr->val = sum % 10;
		offset = sum / 10;
		prevL1 = l1;
		l1 = l1->next;
		prevL2 = l2;
		l2 = l2->next;
		prev = curr;
		curr = curr->next;
	}
	prevL2->next = nullptr;

	// If l1 is longer
	while (l1 != nullptr) {
		int sum = l1->val + offset;
		curr->val = sum % 10;
		offset = sum / 10;
		l1 = l1->next;
		prev = curr;
		curr = curr->next;
	}

	// If l2 is longer
	curr = l2;
	prev->next = curr;
	while (l2 != nullptr) {
		int sum = l2->val + offset;
		curr->val = sum % 10;
		offset = sum / 10;
		l2 = l2->next;
		prev = curr;
		curr = curr->next;
	}

	if (offset == 1) {
		prev->next = new ListNode(1);
	}

	ListNode* l = dummyHead->next;
	delete dummyHead;
	return l;
}

BOOST_AUTO_TEST_CASE(add_two_numbers_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* l1 = new ListNode(2);
		l1->next = new ListNode(4);
		l1->next->next = new ListNode(3);
		ListNode* l2 = new ListNode(5);
		l2->next = new ListNode(6);
		l2->next->next = new ListNode(4);
		std::cout << "List 1: ";
		print(l1);
		std::cout << "List 2: ";
		print(l2);
		ListNode* l = addTwoNumbers(l1, l2);
		std::cout << "List: ";
		print(l);
		std::cout << "\n";
		release(l1);
		release(l2);
	}

	{ // Test 2
		ListNode* l1 = new ListNode(0);
		ListNode* l2 = new ListNode(0);
		std::cout << "List 1: ";
		print(l1);
		std::cout << "List 2: ";
		print(l2);
		ListNode* l = addTwoNumbers(l1, l2);
		std::cout << "List: ";
		print(l);
		std::cout << "\n";
		release(l1);
		release(l2);
	}

	{ // Test 3
		ListNode* l1 = new ListNode(9);
		l1->next = new ListNode(9);
		l1->next->next = new ListNode(9);
		l1->next->next->next = new ListNode(9);
		l1->next->next->next->next = new ListNode(9);
		l1->next->next->next->next->next = new ListNode(9);
		l1->next->next->next->next->next->next = new ListNode(9);
		ListNode* l2 = new ListNode(9);
		l2->next = new ListNode(9);
		l2->next->next = new ListNode(9);
		l2->next->next->next = new ListNode(9);
		std::cout << "List 1: ";
		print(l1);
		std::cout << "List 2: ";
		print(l2);
		ListNode* l = addTwoNumbers(l1, l2);
		std::cout << "List: ";
		print(l);
		std::cout << "\n";
		release(l1);
		release(l2);
	}

	{ // Test 4
		ListNode* l1 = new ListNode(9);
		l1->next = new ListNode(9);
		l1->next->next = new ListNode(9);
		l1->next->next->next = new ListNode(9);
		ListNode* l2 = new ListNode(9);
		l2->next = new ListNode(9);
		l2->next->next = new ListNode(9);
		l2->next->next->next = new ListNode(9);
		l2->next->next->next->next = new ListNode(9);
		l2->next->next->next->next->next = new ListNode(9);
		l2->next->next->next->next->next->next = new ListNode(9);
		std::cout << "List 1: ";
		print(l1);
		std::cout << "List 2: ";
		print(l2);
		ListNode* l = addTwoNumbers(l1, l2);
		std::cout << "List: ";
		print(l);
		std::cout << "\n";
		release(l1);
		release(l2);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Convert Sorted List to Binary Search Tree" problem (LeetCode #109)
// Problem:
// - Given the head of a singly linked list where elements are sorted in ascending order.
// - Convert it to a height balanced BST.
// Input:
// Output:

BOOST_AUTO_TEST_SUITE(convert_sorted_list_to_bst_suite)

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

TreeNode* sortedListToBST(ListNode* head) {
	if (head == nullptr) {
		return nullptr;
	}

	ListNode* fast = head->next;
	ListNode* slow = head;
	ListNode* prevSlow = nullptr;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		prevSlow = slow;
		slow = slow->next;
	}

	// Create the root
	TreeNode* root = new TreeNode(slow->val);

	// Create the left tree
	TreeNode* left;
	if (prevSlow != nullptr) {
		prevSlow->next = nullptr;
		left = sortedListToBST(head);
	} else {
		left = nullptr;
	}

	// Create the right tree
	ListNode* oldNext = slow->next;
	slow->next = nullptr;
	TreeNode* right = sortedListToBST(oldNext);

	// Delete the current node
	delete slow;

	// Create the tree
	root->left = left;
	root->right = right;
	return root;
}

BOOST_AUTO_TEST_CASE(convert_sorted_list_to_bst_test) {
	TEST_MARKER();

	{ // Test 1
		ListNode* head = new ListNode(-10);
		head->next = new ListNode(-3);
		head->next->next = new ListNode(0);
		head->next->next->next = new ListNode(5);
		head->next->next->next->next = new ListNode(9);
		std::cout << "List:\n";
		print(head);
		TreeNode* root = sortedListToBST(head);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "\n";
		release(root);
	}

	{ // Test 2
		ListNode* head = new ListNode(1);
		head->next = new ListNode(2);
		head->next->next = new ListNode(3);
		head->next->next->next = new ListNode(4);
		head->next->next->next->next = new ListNode(5);
		head->next->next->next->next->next = new ListNode(6);
		head->next->next->next->next->next->next = new ListNode(7);
		head->next->next->next->next->next->next->next = new ListNode(8);
		std::cout << "List:\n";
		print(head);
		TreeNode* root = sortedListToBST(head);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "\n";
		release(root);
	}

	{ // Test 3
		ListNode* head = new ListNode(1);
		std::cout << "List:\n";
		print(head);
		TreeNode* root = sortedListToBST(head);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "\n";
		release(root);
	}

	{ // Test 4
		ListNode* head = nullptr;
		std::cout << "List:\n";
		print(head);
		TreeNode* root = sortedListToBST(head);
		std::cout << "Tree:\n";
		print(root);
		std::cout << "\n";
		release(root);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()