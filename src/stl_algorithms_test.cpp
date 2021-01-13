#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <random>

void log(std::string_view txt, const std::vector<int>& vec) {
	std::cout << txt << '\n';
	for (const auto& elm : vec) {
		std::cout << elm << ' ';
	}
	std::cout << '\n';
}

// make_heap, pop_heap, push_heap, sort_heap
void test_heap() {
	std::cout << "[TEST HEAP]\n";

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before make_heap: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::make_heap(vec.begin(), vec.end());
	log("After make_heap: ", vec);
	// Result: 12 11 7 9 10 6 1 8 4 2 5 3

	std::pop_heap(vec.begin(), vec.end());
	log("After pop_heap: ", vec);
	// Result: 11 10 7 9 5 6 1 8 4 2 3 12

	vec.pop_back();
	log("After pop_back: ", vec);
	// Result: 11 10 7 9 5 6 1 8 4 2 3

	vec.push_back(12);
	std::push_heap(vec.begin(), vec.end());
	log("After push_heap: ", vec);
	// Result: 12 10 11 9 5 7 1 8 4 2 3 6

	std::sort_heap(vec.begin(), vec.end());
	log("After sort_heap: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12
}

// sort, partial_sort, nth_element, inplace_merge
void test_sorting() {
	std::cout << "\n[TEST SORTING]\n";

	std::vector vec = {6, 5, 4, 3, 2, 1, 12, 11, 10, 9, 8, 7};
	log("Before sort: ", vec);
	// Result: 6 5 4 3 2 1 12 11 10 9 8 7

	std::sort(vec.begin(), vec.end());
	log("After sort: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	vec = {6, 5, 4, 3, 2, 1, 12, 11, 10, 9, 8, 7};
	log("Before partial_sort ", vec);
	// Result: 6 5 4 3 2 1 12 11 10 9 8 7

	std::partial_sort(vec.begin(), vec.begin() + 6, vec.end());
	log("After partial_sort: ", vec);
	// Result: 1 2 3 4 5 6 12 11 10 9 8 7

	vec = {6, 12, 5, 11, 4, 10, 3, 9, 2, 8, 1, 7};
	log("Before nth_element: ", vec);
	// Result: 6 12 5 11 4 10 3 9 2 8 1 7

	std::nth_element(vec.begin(), vec.begin() + 1, vec.end());
	std::cout << "The second smallest element is: " << vec[1] << '\n';
	// Result: 2

	vec = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12};
	log("Before inplace_merge: ", vec);
	// Result: 1 3 5 7 9 11 2 4 6 8 10 12

	std::inplace_merge(vec.begin(), vec.begin() + 6, vec.end());
	log("After inplace_merge: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12
}

// partition, partition_point
void test_partition() {
	std::cout << "\n[TEST PARTITION]\n";

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before partition: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::partition(vec.begin(), vec.end(), [](const int& elm) {
		return elm % 2;
	});
	log("After partition: ", vec);
	// Result: 1 11 3 9 5 7 6 8 4 1 2 12

	auto pp = std::partition_point(vec.begin(), vec.end(), [](const int& elm) {
		return elm % 2;
	});

	std::cout << "First half: ";
	std::copy(vec.begin(), pp, std::ostream_iterator<int>(std::cout, " "));
	// Result: 1 11 3 9 5 7

	std::cout << "\nSecond half: ";
	std::copy(pp, vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';
	// Result: 6 8 4 10 2 12
}

// reverse, rotate, shuffle, next_permutation, prev_permutation
void test_other_permutation_algorithms() {
	std::cout << "\n[TEST OTHER PERMUTATION ALGORITHMS]\n";

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before reverse: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12
	
	std::reverse(vec.begin(), vec.end());
	log("After reverse: ", vec);
	// Result: 12 11 10 9 8 7 6 5 4 3 2 1

	std::rotate(vec.begin(), vec.begin() + vec.size() / 2, vec.end());
	log("After rotate: ", vec);
	// Result: 6 5 4 3 2 1 12 11 10 9 8 7

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::shuffle(vec.begin(), vec.end(), dre);
	log("After shuffle: ", vec);
	// Result: Anything possible

	vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before next_permutation: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::next_permutation(vec.begin(), vec.end());
	log("After next_permutation: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 12 11

	vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before prev_permutation: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::prev_permutation(vec.begin(), vec.end());
	log("After prev_permutation: ", vec);
	// Result: 12 11 10 9 8 7 6 5 4 3 2 1
}

int main(int argv, char** argc) {
	test_heap();
	test_sorting();
	test_partition();
	test_other_permutation_algorithms();
}

