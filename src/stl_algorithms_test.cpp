#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <execution>
#include <iostream>
#include <random>

void log(std::string_view txt, const std::vector<int>& vec) {
	std::cout << txt << "\n";
	for (const auto& ele : vec) {
		std::cout << ele << ' ';
	}
	std::cout << "\n";
}

// TEST PERMUTATION ALGORITHMS

// make_heap, pop_heap, push_heap, sort_heap
void test_heap_algorithms() {
	std::cout << "[TEST HEAP ALGORITHMS]\n";

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
	std::cout << "\n[TEST SORTING ALGORITHMS]\n";

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
	std::cout << "The second smallest element is: " << vec[1] << "\n";
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
	std::cout << "\n[TEST PARTITIONING ALGORITHMS]\n";

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
	// Result: 1 11 3 9 5 7

	std::cout << "\nSecond half: ";
	std::copy(pp, vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
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

// TEST PREFIXES AND POSTFIXES

// stable_sort, stable_partition
void test_stable() {
	std::cout << "\n[TEST STABLE_*]\n";

	struct interval {
		int start;
		int finish;
		interval(int s, int f) : start{s}, finish{f} {}
	};
	auto i_log = [](std::string txt, const std::vector<interval>& vec) {
		std::cout << txt << "\n";
		for (const auto& ele : vec) {
			std::cout << '(' << ele.start << ", " << ele.finish << ") ";
		}
		std::cout << "\n";
	};
	std::vector<interval> i_vec;
	i_vec.emplace_back(1, 3);
	i_vec.emplace_back(2, 4);
	i_vec.emplace_back(1, 2);
	i_vec.emplace_back(3, 3);
	i_log("Before stable_sort: ", i_vec);
	// Result: (1, 3) (2, 4) (1, 2) (3, 3)

	std::stable_sort(i_vec.begin(), i_vec.end(), [](const interval& lhs, const interval& rhs) {
		return lhs.start < rhs.start;
	});
	i_log("After stable_sort: ", i_vec);
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
	std::cout << "\n[TEST IS_*]\n";

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
	std::cout << "\n[TEST IS_*_UNTIL]\n";

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
	std::cout << "\n[TEST VALUE QUERY ALGORITHMS]\n";

	// 1. On one range

	std::vector<int> vec = {1, 2, 3, 4, 1, 5, 1, 6, 7, 8, 9, 10};
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	auto count = std::count(vec.begin(), vec.end(), 1);
	std::cout << "- Number of elements equal 1: " << count << "\n";

	auto sum = std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << "- Sum of all elements (accumulate): " << sum << "\n";

	sum = std::reduce(vec.begin(), vec.end(), 0);
	std::cout << "- Sum of all elements (reduce): " << sum << "\n";

	auto sqr_sum = std::transform_reduce(
		vec.begin(),
		vec.end(),
		0,
		std::plus<int>{},
		[](const int& ele) {
			return ele * ele;
		}
	);
	std::cout << "- Sum of squares (transform_reduce): " << sqr_sum << "\n";
	
	std::cout << "- Partial sum (partial_sum): ";
	std::partial_sum(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	
	std::cout << "- Partial sum (inclusive_scan): ";
	std::inclusive_scan(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	std::cout << "- Partial sum (exclusive_scan): ";
	std::exclusive_scan(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "), 0);
	std::cout << "\n";

	std::cout << "- Partial sum of squares (transform_inclusive_scan): ";
	std::transform_inclusive_scan(
		vec.begin(),
		vec.end(),
		std::ostream_iterator<int>(std::cout, " "),
		std::plus<int>{},
		[](const int& ele) {
			return ele * ele;
		}
	);
	std::cout << "\n";

	std::cout << "- Partial sum of squares (transform_exclusive_scan): ";
	std::transform_exclusive_scan(
		vec.begin(),
		vec.end(),
		std::ostream_iterator<int>(std::cout, " "),
		0,
		std::plus<int>{},
		[](const int& ele) {
			return ele * ele;
		}
	);
	std::cout << "\n";

	std::cout << "- Adjacent difference: ";
	std::adjacent_difference(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	std::cout << "- Sample: ";
	std::sample(
		vec.begin(),
		vec.end(), 
		std::ostream_iterator<int>(std::cout, " "),
		vec.size() / 2,
		std::mt19937{std::random_device{}()}
	);
	std::cout << "\n";

	// 2. On two ranges

	std::vector<int> vec1 = {1, 2, 3, 4};
	std::vector<int> vec2 = { 5, 6, 7, 8 };
	std::cout << "\nVector 1: ";
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\nVector 2: ";
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	auto prd = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
	std::cout << "- Inner product: " << prd << "\n";
}

// all_of, any_of, none_of, equal, is_permutation, lexicographical_compare, mismatch
void test_property_query_algorithms() {
	std::cout << "\n[TEST PROPERTY QUERY ALGORITHMS]\n";

	// 1. On one range

	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	auto res = std::all_of(vec.begin(), vec.end(), [](const auto& ele) {
		return ele > 0;
	});
	std::cout << "- Has all positive elements: " << std::boolalpha << res << "\n";

	res = std::any_of(vec.begin(), vec.end(), [](const auto& ele) {
		return ele % 2 == 1;
	});
	std::cout << "- Has some odd elements: " << std::boolalpha << res << "\n";

	res = std::none_of(vec.begin(), vec.end(), [](const auto& ele) {
		return ele % 2 == 0;
	});
	std::cout << "- Has no even elements: " << std::boolalpha << res << "\n";

	// 2. On two ranges

	std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	std::vector<int> vec2 = {7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6};
	std::cout << "\nVector 1: ";
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\nVector 2: ";
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	
	res = std::equal(vec1.begin(), vec1.end(), vec2.begin());
	std::cout << "- Are equal: " << std::boolalpha << res << "\n";

	res = std::is_permutation(vec1.begin(), vec1.end(), vec2.begin());
	std::cout << "- Are permutations: " << std::boolalpha << res << "\n";

	res = std::lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
	std::cout << "- Vector 1 < Vector 2: " << std::boolalpha << res << "\n";

	std::string str = "HelloqwertyolleH";
	std::string mir = std::string(str.begin(), std::mismatch(str.begin(), str.end(), str.rbegin()).first);
	std::cout << "\nThe mirror substring of \"" << str << "\" is \"" << mir << "\".\n";
}

// find, adjacent_find, equal_range, lower_bound, upper_bound, search, find_end, find_first_of,
// min_element, max_element, minmax_element
void test_searching_algorithms() {
	std::cout << "\n[TEST SEARCHING ALGORITHMS]\n";

	// 1. Searching a value

	std::vector<int> vec = { 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::cout << "Vector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	// 1.1. On unsorted ranges

	auto it = std::find(vec.begin(), vec.end(), 4);
	std::cout << "- Has at least one element equal to 4: " << std::boolalpha << (it != vec.end()) << "\n";
	if (it != vec.end()) {
		std::cout << "  At index " << std::distance(vec.begin(), it) << "\n";
	}

	it = std::adjacent_find(vec.begin(), vec.end(), std::greater<int>{});
	std::cout << "- Is strictly increasing: " << std::boolalpha << (it != vec.end()) << "\n";

	// 1.2. On sorted ranges

	auto p_it = std::equal_range(vec.begin(), vec.end(), 3);
	std::cout << "- Has at least two elements equal to 3: " << std::boolalpha << (p_it.second - p_it.first > 0) << "\n";
	if (p_it.first != vec.end()) {
		std::cout << "  From index " << std::distance(vec.begin(), p_it.first);
		std::cout << " to index " << std::distance(vec.begin(), p_it.second) << "\n";
	}

	it = std::lower_bound(vec.begin(), vec.end(), 4);
	std::cout << "- Has at least one element not less than 4: " << std::boolalpha << (it != vec.end()) << "\n";
	if (it != vec.end()) {
		std::cout << "  First element not less than 4 is " << *it << "\n";
	}

	it = std::upper_bound(vec.begin(), vec.end(), 4);
	std::cout << "- Has at least one element greater than 4: " << std::boolalpha << (it != vec.end()) << "\n";
	if (it != vec.end()) {
		std::cout << "  First element greater than 4 is " << *it << "\n";
	}

	auto found = std::binary_search(vec.begin(), vec.end(), 4);
	std::cout << "- Has at least one element equal to 4: " << std::boolalpha << found << "\n";

	// 2. Searching a range

	std::vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 7, 8, 9, 10, 11, 12 };
	std::vector<int> vec2 = { 1, 2, 3 };
	std::vector<int> vec3 = { 4, 7, 10 };
	std::cout << "\nVector 1: ";
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\nVector 2: ";
	std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\nVector 3: ";
	std::copy(vec3.begin(), vec3.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	it = std::search(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
	std::cout << "- Vector 2 is a subrange of Vector 1: " << std::boolalpha << (it != vec1.end()) << "\n";
	if (it != vec1.end()) {
		std::cout << "  First appearance starts at index " << std::distance(vec1.begin(), it) << "\n";
		it = std::find_end(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
		std::cout << "  Last appearance starts at index " << std::distance(vec1.begin(), it) << "\n";
	}

	it = std::find_first_of(vec1.begin(), vec1.end(), vec3.begin(), vec3.end());
	std::cout << "- Vector 1 contains at least one element of Vector 3: " << std::boolalpha << (it != vec1.end()) << "\n";
	if (it != vec1.end()) {
		std::cout << "  First element is " << *it << " at index " << std::distance(vec1.begin(), it) << "\n";
	}

	// 3. Searching a relative value

	vec = {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12};
	std::cout << "\nVector ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	std::cout << "- Min element: " << *std::min_element(vec.begin(), vec.end()) << "\n";
	std::cout << "- Max element: " << *std::max_element(vec.begin(), vec.end()) << "\n";
}

// TEST QUERY ALGORITHMS

// set_difference, set_union, set_intersection, set_symmetric_difference, includes, merge
void test_set_algorithms() {
	std::cout << "\n[TEST SET ALGORITHMS]\n";

	std::set<int> set1 = {1, 2, 3, 4, 5, 6, 7, 8};
	std::set<int> set2 = {6, 7, 8, 9, 10, 11, 12};
	std::cout << "Set 1: ";
	std::copy(set1.begin(), set1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\nSet 2: ";
	std::copy(set2.begin(), set2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	std::vector<int> res;
	std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	std::cout << "- Set 1 \\ Set 2: ";
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	res = {};
	std::set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(), std::back_inserter(res));
	std::cout << "- Set 2 \\ Set 1: ";
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	res = {};
	std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	std::cout << "- Set 2 ^ Set 1: ";
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	res = {};
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	std::cout << "- Set 2 v Set 1: ";
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	res = {};
	std::set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	std::cout << "- Set 2 \\ Set 1 ^ Set 1 \\ Set 2: ";
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	auto is_subset = std::includes(set1.begin(), set1.end(), set2.begin(), set2.end());
	std::cout << "- Set 2 is a subset of Set 1: " << std::boolalpha << is_subset << "\n";

	res = {};
	std::merge(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
	std::cout << "- Set 1 + Set 2: ";
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
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
}