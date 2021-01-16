#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <execution>
#include <iostream>
#include <random>

void log(std::string_view txt) {
	std::cout << txt << "\n";
}

void log(std::string_view txt, int64_t val, bool tag = false) {
	if (tag) {
		std::cout << txt << std::boolalpha << (bool)val << "\n";
	} else {
		std::cout << txt << std::noboolalpha << val << "\n";
	}
}

void log(std::string_view txt, const std::vector<int>& vec) {
	std::cout << txt;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout,  " "));
	std::cout << "\n";
}

// TEST PERMUTATION ALGORITHMS

// make_heap, pop_heap, push_heap, sort_heap
void test_heap_algorithms() {
	log("[TEST HEAP ALGORITHMS]");

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
void test_sorting_algorithms() {
	log("");
	log("[TEST SORTING ALGORITHMS]");

	std::vector vec = {6, 5, 4, 3, 2, 1, 12, 11, 10, 9, 8, 7};
	log("Before sort: ", vec);
	// Result: 6 5 4 3 2 1 12 11 10 9 8 7

	std::sort(vec.begin(), vec.end());
	log("After sort: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	vec = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	log("Before partial_sort ", vec);
	// Result: 12 11 10 9 8 7 6 5 4 3 2 1

	std::partial_sort(vec.begin(), vec.begin() + 6, vec.end());
	log("After partial_sort: ", vec);
	// Result: 1 2 3 4 5 6 12 11 10 9 8 7

	vec = {6, 12, 5, 11, 4, 10, 3, 9, 2, 8, 1, 7};
	log("Before nth_element: ", vec);
	// Result: 6 12 5 11 4 10 3 9 2 8 1 7

	std::nth_element(vec.begin(), vec.begin() + 1, vec.end());
	log("The second smallest element is: ", vec[1]);
	// Result: 2

	vec = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12};
	log("Before inplace_merge: ", vec);
	// Result: 1 3 5 7 9 11 2 4 6 8 10 12

	std::inplace_merge(vec.begin(), vec.begin() + 6, vec.end());
	log("After inplace_merge: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12
}

// partition, partition_point
void test_partitioning_algorithms() {
	log("");
	log("[TEST PARTITIONING ALGORITHMS]");

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before partition: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::partition(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2;
	});
	log("After partition: ", vec);
	// Result: 1 11 3 9 5 7 6 8 4 1 2 12

	auto pp = std::partition_point(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2;
	});

	std::cout << "First half: ";
	std::copy(vec.begin(), pp, std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	// Result: 1 11 3 9 5 7

	std::cout << "Second half: ";
	std::copy(pp, vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	// Result: 6 8 4 10 2 12
}

// reverse, rotate, shuffle, next_permutation, prev_permutation
void test_other_permutation_algorithms() {
	log("");
	log("[TEST OTHER PERMUTATION ALGORITHMS]");

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

// TEST PREFIXES AND POSTFIXES

struct interval {
	int start;
	int finish;
	interval(int s, int f) : start{ s }, finish{ f } {}
};

void log(std::string_view txt, const std::vector<interval>& vec) {
	std::cout << txt;
	for (const auto& ele : vec) {
		std::cout << '(' << ele.start << ", " << ele.finish << ") ";
	}
	std::cout << "\n";
}

// stable_sort, stable_partition
void test_stable() {
	log("");
	log("[TEST STABLE_*]");

	std::vector<interval> interval_vec;
	interval_vec.emplace_back(1, 3);
	interval_vec.emplace_back(2, 4);
	interval_vec.emplace_back(1, 2);
	interval_vec.emplace_back(3, 3);
	log("Before stable_sort: ", interval_vec);
	// Result: (1, 3) (2, 4) (1, 2) (3, 3)

	std::stable_sort(interval_vec.begin(), interval_vec.end(), [](const interval& lhs, const interval& rhs) {
		return lhs.start < rhs.start;
	});
	log("After stable_sort: ", interval_vec);
	// Result: (1, 3) (1, 2) (2, 4) (3, 3)

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before stable_partition: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::stable_partition(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2;
	});
	log("After stable_partition: ", vec);
	// Result: 1 3 5 7 9 11 2 4 6 8 10 12
}

// is_sorted, is_partitioned, is_heap
void test_is() {
	log("");
	log("[TEST IS_*]");

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "is " << (std::is_sorted(vec.begin(), vec.end()) ? "sorted.\n" : "not sorted.\n");

	vec = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12};
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "is " << (std::is_partitioned(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2;
	}) ? "partitioned.\n" : "not partitioned.\n");

	vec = {12, 11, 7, 9, 10, 6, 1, 8, 4, 2, 5, 3};
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "is " << (std::is_heap(vec.begin(), vec.end()) ? "a heap.\n" : "not a heap.\n");
}

// is_sorted_until, is_heap_until
void test_is_until() {
	log("");
	log("[TEST IS_*_UNTIL]");

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 12, 11, 10, 9, 8, 7};
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "is sorted until " << (std::is_sorted_until(vec.begin(), vec.end()) - vec.begin()) << "th element.\n";

	vec = {12, 10, 7, 9, 11, 6, 1, 8, 4, 2, 5, 3};
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "is heap until " << (std::is_heap_until(vec.begin(), vec.end()) - vec.begin()) << "th element.\n";
}

// TEST QUERY ALGORITHMS

// count, accumulate, (transform_)reduce, partial_sum, (transform_)inclusive_scan, (transform_)exclusive_scan,
// adjacent_difference, sample, inner_product
void test_value_query_algorithms() {
	log("");
	log("[TEST VALUE QUERY ALGORITHMS]");

	// 1. On one range

	std::vector<int> vec = {1, 2, 3, 4, 1, 5, 1, 6, 7, 8, 9, 10};
	log("Vector ", vec);

	auto count = std::count(vec.begin(), vec.end(), 1);
	log("- Number of elements equal 1: ", count);

	auto sum = std::accumulate(vec.begin(), vec.end(), 0);
	log("- Sum of all elements (accumulate): ", sum);

	sum = std::reduce(vec.begin(), vec.end(), 0);
	log("- Sum of all elements (reduce): ", sum);

	sum = std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<int>{}, [](const int& ele) {
		return ele * ele;
	});
	log("- Sum of squares (transform_reduce): ", sum);
	
	std::vector<int> res;
	std::adjacent_difference(vec.begin(), vec.end(), std::back_inserter(res));
	log("- Adjacent difference: ", res);

	res = {};
	std::partial_sum(vec.begin(), vec.end(), std::back_inserter(res));
	log("- Partial sum (partial_sum): ", res);
	
	res = {};
	std::inclusive_scan(vec.begin(), vec.end(), std::back_inserter(res));
	log("- Partial sum (inclusive_scan): ", res);

	res = {};
	std::exclusive_scan(vec.begin(), vec.end(), std::back_inserter(res), 0);
	log("- Partial sum (exclusive_scan): ", res);

	res = {};
	std::transform_inclusive_scan(
		vec.begin(),
		vec.end(),
		std::back_inserter(res),
		std::plus<int>{},
		[](const int& ele) {
			return ele * ele;
		}
	);
	log("- Partial sum of squares (transform_inclusive_scan): ", res);

	res = {};
	std::transform_exclusive_scan(
		vec.begin(),
		vec.end(),
		std::back_inserter(res),
		0,
		std::plus<int>{},
		[](const int& ele) {
			return ele * ele;
		}
	);
	log("- Partial sum of squares (transform_exclusive_scan): ", res);

	res = {};
	std::sample(
		vec.begin(),
		vec.end(), 
		std::back_inserter(res),
		vec.size() / 2,
		std::mt19937{std::random_device{}()}
	);
	log("- Sample: ", res);

	// 2. On two ranges

	std::vector<int> vec1 = {1, 2, 3, 4};
	std::vector<int> vec2 = {5, 6, 7, 8};
	log("");
	log("Vector 1: ", vec1);
	log("Vector 2: ", vec2);

	auto prd = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
	log("- Inner product: ", prd);
}

// all_of, any_of, none_of, equal, is_permutation, lexicographical_compare, mismatch
void test_property_query_algorithms() {
	log("");
	log("[TEST PROPERTY QUERY ALGORITHMS]");

	// 1. On one range

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Vector ", vec);

	auto res = std::all_of(vec.begin(), vec.end(), [](const auto& ele) {
		return ele > 0;
	});
	log("- Has all positive elements: ", res, true);

	res = std::any_of(vec.begin(), vec.end(), [](const auto& ele) {
		return ele % 2 == 1;
	});
	log("- Has some odd elements: ", res, true);

	res = std::none_of(vec.begin(), vec.end(), [](const auto& ele) {
		return ele % 2 == 0;
	});
	log("- Has no even elements: ", res, true);

	// 2. On two ranges
	std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	std::vector<int> vec2 = {7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6};
	log("");
	log("Vector 1: ", vec1);
	log("Vector 2: ", vec2);

	res = std::equal(vec1.begin(), vec1.end(), vec2.begin());
	log("- Are equal: ", res, true);

	res = std::is_permutation(vec1.begin(), vec1.end(), vec2.begin());
	log("- Are permutations: ", res, true);

	res = std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
	log("- Vector 1 < Vector 2: ", res, true);

	std::string str = "HelloqwertyolleH";
	std::string mir = std::string(str.begin(), std::mismatch(str.begin(), str.end(), str.rbegin()).first);
	log("\nThe mirror substring of \"" + str + "\" is \"" + mir + "\".");
}

// find, adjacent_find, equal_range, lower_bound, upper_bound, search, find_end, find_first_of,
// min_element, max_element, minmax_element
void test_searching_algorithms() {
	log("");
	log("[TEST SEARCHING ALGORITHMS]");

	// 1. Searching a value

	std::vector<int> vec = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Vector ", vec);

	// 1.1. On unsorted ranges

	auto it = std::find(vec.begin(), vec.end(), 4);
	log("- Has at least one element equal to 4: ", it != vec.end(), true);
	if (it != vec.end()) {
		log("  At index ", std::distance(vec.begin(), it));
	}

	it = std::adjacent_find(vec.begin(), vec.end(), std::greater<int>{});
	log("- Is strictly increasing: ", it != vec.end(), true);

	// 1.2. On sorted ranges

	auto p_it = std::equal_range(vec.begin(), vec.end(), 3);
	log("- Has at least two elements equal to 3: ", p_it.second - p_it.first > 0, true);
	if (p_it.first != vec.end()) {
		log("  From index ", std::distance(vec.begin(), p_it.first));
		log("  To index ", std::distance(vec.begin(), p_it.second));
	}

	it = std::lower_bound(vec.begin(), vec.end(), 4);
	log("- Has at least one element not less than 4: ", it != vec.end(), true);
	if (it != vec.end()) {
		log("  First element not less than 4 is ", *it);
	}

	it = std::upper_bound(vec.begin(), vec.end(), 4);
	log("- Has at least one element greater than 4: ", it != vec.end(), true);
	if (it != vec.end()) {
		log("  First element greater than 4 is ", *it);
	}

	auto found = std::binary_search(vec.begin(), vec.end(), 4);
	log("- Has at least one element equal to 4: ", found, true);

	// 2. Searching a range
	std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 1, 2, 3, 7, 8, 9, 10, 11, 12};
	std::vector<int> vec2 = {1, 2, 3};
	std::vector<int> vec3 = {4, 7, 10};
	log("");
	log("Vector 1: ", vec1);
	log("Vector 2: ", vec2);
	log("Vector 3: ", vec3);

	it = std::search(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
	log("- Vector 2 is a subrange of Vector 1: ", it != vec1.end(), true);
	if (it != vec1.end()) {
		log("  First appearance starts at index ", std::distance(vec1.begin(), it));
		it = std::find_end(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		log("  Last appearance starts at index ", std::distance(vec1.begin(), it));
	}

	it = std::find_first_of(vec1.begin(), vec1.end(), vec3.begin(), vec3.end());
	log("- Vector 1 contains at least one element of Vector 3: ", it != vec1.end(), true);
	if (it != vec1.end()) {
		log("  First element is ", *it);
	}

	// 3. Searching a relative value
	vec = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12};
	log("");
	log("Vector ", vec);
	log("- Min element: ", *std::min_element(vec.begin(), vec.end()));
	log("- Max element: ", *std::max_element(vec.begin(), vec.end()));
}

// TEST SET ALGORITHMS

// set_difference, set_union, set_intersection, set_symmetric_difference, includes, merge
void test_set_algorithms() {
	log("");
	log("[TEST SET ALGORITHMS]");

	std::vector<int> set1 = {1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> set2 = {6, 7, 8, 9, 10, 11, 12};
	log("Set 1: ", set1);
	log("Set 2: ", set2);

	std::vector<int> res;
	std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	log("- Set 1 \\ Set 2: ", res);

	res = {};
	std::set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(), std::back_inserter(res));
	log("- Set 2 \\ Set 2: ", res);

	res = {};
	std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	log("- Set 1 ^ Set 2: ", res);

	res = {};
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	log("- Set 1 v Set 2: ", res);

	res = {};
	std::set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	log("- Set 1 \\ Set 2 ^ Set 2 \\ Set 1: ", res);

	auto is_subset = std::includes(set1.begin(), set1.end(), set2.begin(), set2.end());
	log("- Set 2 is a subset of Set 1: ", is_subset, true);

	res = {};
	std::merge(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	log("- Set 1 + Set 2: ", res);
}

// TEST COPYING AND MOVING ALGORITHMS

// copy, copy_backward, move, move_backward, swap_ranges
void test_copying_and_moving_algorithms() {
	log("");
	log("[TEST COPYING AND MOVING ALGORITHMS]");

	// 1. Copying

	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("Before copy: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::copy(vec.begin(), vec.begin() + vec.size() / 2, vec.begin() + vec.size() / 2);
	log("After copy: ", vec);
	// Result: 1 2 3 4 5 6 1 2 3 4 5 6

	vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	log("");
	log("Before copy_backward: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::copy_backward(vec.begin(), vec.begin() + vec.size() * 2 / 3, vec.end());
	log("After copy_backward: ", vec);
	// Result: 1 2 3 4 1 2 3 4 5 6 7 8

	// 2. Moving

	std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	std::vector<int> vec2;
	log("");
	log("Before move:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::move(vec1.begin(), vec1.end(), std::back_inserter(vec2)); // std::move() didn't move the elements in this case
	log("After move:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	log("");
	log("Before move_backward:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::move_backward(vec1.begin(), vec1.end(), vec2.end());
	log("After move_backward:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	// 3. Swapping ranges

	vec1 = {1, 2, 3, 4, 5, 6};
	vec2 = {7, 8, 9, 10, 11, 12};
	log("");
	log("Before swap_ranges:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::swap_ranges(vec1.begin(), vec1.end(), vec2.begin());
	log("After swap_ranges:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);
}

// TEST VALUE MODIFYING ALGORITHMS

// fill, generate, iota, replace
void test_value_modifying_algorithms() {
	log("");
	log("[TEST VALUE MODIFYING ALGORITHMS]");

	std::vector<int> vec;
	vec.resize(12);
	log("Before fill: ", vec);
	// Result: 0 0 0 0 0 0 0 0 0 0 0 0

	std::fill(vec.begin(), vec.end(), -1);
	log("After fill: ", vec);
	// Result: -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1

	std::generate(vec.begin(), vec.end(), [] {
		std::random_device rd;
		std::mt19937 mt{rd()};
		std::uniform_int_distribution<int> uid(1, 12);
		return uid(mt);
	});
	log("After generate: ", vec);
	// Result: Anything possible

	std::iota(vec.begin(), vec.end(), 1);
	log("After iota: ", vec);
	// Result: 1 2 3 4 5 6 7 8 9 10 11 12

	std::replace(vec.begin(), vec.end(), 1, -1);
	log("After replace: ", vec);
	// Result: -1 2 3 4 5 6 7 8 9 10 11 12
}

// TEST STRUCTURE CHANGING ALGORITHMS

// remove, unique
void test_structure_changing_algorithms() {
	log("");
	log("[TEST STRUCTURE CHANGING ALGORITHMS]");

	std::vector<int> vec = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 12};
	log("Before remove: ", vec);
	// Result: 1 1 2 2 3 4 5 6 7 8 9 9 10 11 12 12

	auto it = std::remove(vec.begin(), vec.end(), 9);
	vec.erase(it, vec.end());
	log("After remove: ", vec);
	// Result: 1 1 2 2 3 4 5 6 7 8 10 11 12 12

	it = std::unique(vec.begin(), vec.end());
	vec.erase(it, vec.end());
	log("After unique: ", vec);
	// Result: 1 2 3 4 5 6 7 8 10 11 12
}

// TEST PREFIXES AND POSTFIXES (CONT.)

// remove_copy, unique_copy, reverse_copy, rotate_copy, replace_copy, partition_copy, partial_sort_copy
void test_copy() {
	log("");
	log("[TEST *_COPY]");

	std::vector<int> vec1 = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 12};
	std::vector<int> vec2;
	std::vector<int> vec3;
	log("Before remove_copy:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::remove_copy(vec1.begin(), vec1.end(), std::back_inserter(vec2), 9);
	log("After remove_copy:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec2 = {};
	std::unique_copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));
	log("After unique_copy:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec2 = {};
	std::reverse_copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));
	log("After reverse_copy:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec2 = {};
	std::rotate_copy(vec1.begin(), vec1.begin() + vec1.size() / 2, vec1.end(), std::back_inserter(vec2));
	log("After rotate_copy:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec2 = {};
	std::replace_copy(vec1.begin(), vec1.end(), std::back_inserter(vec2), 1, -1);
	log("After replace_copy:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec2 = {};
	std::partition_copy(vec1.begin(), vec1.end(), std::back_inserter(vec2), std::back_inserter(vec3), [](const int& ele) {
		return ele % 2 == 1;
	});
	log("After partition_copy:");
	log("- Vector 1: ", vec1);
	log("- Odd elements: ", vec2);
	log("- Even elements: ", vec3);

	vec2 = {};
	vec2.resize(3);
	std::partial_sort_copy(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
	log("After partial_sort_copy:");
	log("- Vector 1: ", vec1);
	log("- First 3 smallest elements: ", vec2);
}

// find_if, find_if_not, count_if, remove_if, remove_copy_if, replace_if, replace_copy_if, copy_if
void test_if() {
	log("");
	log("[TEST *_IF]");

	std::vector<int> vec = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 12};
	log("Vector ", vec);

	auto it = std::find_if(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2 == 0;
	});
	if (it != vec.end()) {
		log("- First even element: ", *it);
	}

	it = std::find_if_not(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2 == 0;
	});
	if (it != vec.end()) {
		log("- First odd element: ", *it);
	}

	auto count = std::count_if(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2 == 0;
	});
	log("- Number of even elements: ", count);

	it = std::remove_if(vec.begin(), vec.end(), [](const int& ele) {
		return ele % 2 == 0;
	});
	vec.erase(it, vec.end());
	log("After remove_if: ", vec);

	std::replace_if(vec.begin(), vec.end(), [](const int& ele) {
		return ele > 7;
	}, 8);
	log("After replace_if: ", vec);

	std::vector<int> vec1 = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 12};
	std::vector<int> vec2;
	log("");
	log("Before remove_copy_if:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::remove_copy_if(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](const int& ele) {
		return ele % 2 == 0;
	});
	log("After remove_copy_if:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec1 = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 12};
	vec2 = {};
	log("");
	log("Before replace_copy_if:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::replace_copy_if(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](const int& ele) {
		return ele > 7;
	}, 8);
	log("After replace_copy_if:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	vec1 = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 12};
	vec2 = {};
	log("");
	log("Before copy_if:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);

	std::copy_if(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](const int& ele) {
		return ele % 2 == 0;
	});
	log("After copy_if:");
	log("- Vector 1: ", vec1);
	log("- Vector 2: ", vec2);
}

int main(int argv, char** argc) {
	test_heap_algorithms();
	test_sorting_algorithms();
	test_partitioning_algorithms();
	test_other_permutation_algorithms();
	test_stable();
	test_is();
	test_is_until();
	test_value_query_algorithms();
	test_property_query_algorithms();
	test_searching_algorithms();
	test_set_algorithms();
	test_copying_and_moving_algorithms();
	test_value_modifying_algorithms();
	test_structure_changing_algorithms();
	test_copy();
	test_if();
}