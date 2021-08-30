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

// Search, insert, and delete in an sorted array
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

// Find two elements of an array with a given sum
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
BOOST_AUTO_TEST_CASE(test_9) {
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
	std::cout << "The missing number is " << sum;

	// Use XOR
	int result_1 = arr[0];
	for (int i = 1; i < size; ++i) {
		result_1 ^= arr[i];
	}
	int result_2 = 1;
	for (int k = 2; k <= n; ++k) {
		result_2 ^= k;
	}
	std::cout << "The missing number is " << (result_1 ^ result_2);
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

// Rotate an array
BOOST_AUTO_TEST_CASE(test_8) {
	TEST_MARKER();

	int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8};
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int size = 8;
	int rotating_size = 3;

	print(arr, size, "Array");

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

BOOST_AUTO_TEST_SUITE_END()