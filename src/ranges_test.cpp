#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/none_of.hpp>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/count_if.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/find_if_not.hpp>
#include <range/v3/algorithm/is_sorted.hpp>
#include <range/v3/algorithm/is_partitioned.hpp>
#include <range/v3/range/access.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/repeat_n.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/unique.hpp>
#include <iostream>
#include <vector>
#include <map>

// TEST ALGORITHMS

// Test for_each
void test_1() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	auto print = [](const int& val) {
		std::cout << val * val << " ";
	};
	std::cout << "Vector " << ranges::views::all(vec) << "\n";
	std::cout << "- Square vector: ";
	ranges::for_each(vec, print);
	std::cout << "\n";
	std::map<int, int> map;
	ranges::for_each(vec, [&map](const int& val) {
		map.emplace(val, val * val);
	});
	auto printm = [](const std::pair<int, int>& val) {
		std::cout << "(" << val.first << ", " << val.second << ") ";
	};
	std::cout << "- Square map: ";
	ranges::for_each(map, printm);
	std::cout << "\n\n";
}

// Test any_of, all_of, none_of
void test_2() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	auto is_even = [](const int& val) {
		return val % 2 == 0;
	};
	std::cout << std::boolalpha;
	std::cout << "Vector " << ranges::views::all(vec) << "\n";
	std::cout << "- Has at least one even element: " << ranges::any_of(vec, is_even) << "\n";
	std::cout << "- Has all even elements: " << ranges::all_of(vec, is_even) << "\n";
	std::cout << "- Has all odd elements: " << ranges::none_of(vec, is_even) << "\n";
	std::cout << "\n";
}

// Test count, count_if
void test_3() {
	std::vector<int> vec{1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6};
	auto is_even = [](const int& val) {
		return val % 2 == 0;
	};
	std::cout << std::boolalpha;
	std::cout << "Vector " << ranges::views::all(vec) << "\n";
	std::cout << "- Number of elements: " << ranges::count(vec, 1) << "\n";
	std::cout << "- Number of even elements: " << ranges::count_if(vec, is_even) << "\n";
	std::cout << "\n";
}

// Test find, find_if, find_if_not
void test_4() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	auto is_even = [](const int& val) {
		return val % 2 == 0;
	};
	std::cout << std::boolalpha;
	std::cout << "Vector " << ranges::views::all(vec) << "\n";
	{
		auto it = ranges::find(vec, 2);
		if (it != ranges::end(vec)) {
			std::cout << "- Has element " << *it << "\n";
		}
	}
	{
		auto it = ranges::find(vec, 0);
		if (it == ranges::end(vec)) {
			std::cout << "- Not have 0\n";
		}
	}
	{
		auto it = ranges::find_if(vec, is_even);
		if (it != ranges::end(vec)) {
			std::cout << "- The first even element is " << *it << "\n";
		}
	}
	{
		auto it = ranges::find_if_not(vec, is_even);
		if (it != ranges::end(vec)) {
			std::cout << "- The first odd element is " << *it << "\n";
		}
	}
	std::cout << "\n";
}

// Test is_sorted, is_partitioned
void test_5() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	auto is_even = [](const int& val) {
		return val % 2 == 0;
	};
	std::cout << std::boolalpha;
	std::cout << "Vector " << ranges::views::all(vec) << " is sorted: " << ranges::is_sorted(vec) << "\n";
	vec = {2, 4, 6, 8, 10, 12, 1, 3, 5, 7, 9, 11};
	std::cout << "Vector " << ranges::views::all(vec) << " is partitioned: " << ranges::is_partitioned(vec, is_even) << "\n";
	std::cout << "\n";
}

// TEST VIEWS

// Filter and transform
void test_6() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	std::cout << "Vector " << ranges::views::all(vec) << "\n";
	auto is_even = [](int val) {
		return val % 2 == 0;
	};
	auto sqr = [](int val) {
		return val * val;
	};
	auto rng = vec | ranges::views::filter(is_even) | ranges::views::transform(sqr);
	std::cout << "- Square of even elements: " << rng << "\n";
	std::cout << "\n";
}

// Generate ints and accumulate
void test_7() {
	auto sqr = [](int val) {
		return val * val;
	};
	int sum = ranges::accumulate(
		ranges::views::ints(1, ranges::unreachable) | 
		ranges::views::transform(sqr) | 
		ranges::views::take(12),
		0
	);
	std::cout << "1^2 + 2^2 + ... + 10^2 + 11^2 + 12^2 = " << sum << "\n";
	std::cout << "\n";
}

// Convert a range comprehension to a vector
void test_8() {
	auto vec = ranges::views::for_each(
		ranges::views::ints(1, 13),
		[](int i) {
			return ranges::yield_from(ranges::views::repeat_n(i, i));
		}
	) | ranges::to<std::vector>();
	std::cout << "Generated vector: " << ranges::views::all(vec) << "\n";
	std::cout << "\n";
}

// TEST ACTIONS

// Sort and remove non-unique elements from a container
void test_9() {
	std::vector<int> vec{2, 1, 5, 4, 6, 7, 2, 3, 8, 2, 1, 9, 10, 7, 11, 12, 4, 8, 8, 6, 5, 2, 4, 3, 1, 9, 11, 10, 12};
	std::cout << "Vector " << ranges::views::all(vec) << "\n";
	vec |= ranges::actions::sort;
	std::cout << "- After sorting: " << ranges::views::all(vec) << "\n";
	vec |= ranges::actions::unique;
	std::cout << "- After removing non-unique elements: " << ranges::views::all(vec) << "\n";
}

int main(int argc, char** argv) {
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
	test_7();
	test_8();
	test_9();
}