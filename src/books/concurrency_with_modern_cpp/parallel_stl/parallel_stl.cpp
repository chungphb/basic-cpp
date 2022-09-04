#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include <execution>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

template <typename T>
void print(std::vector<T>& arr) {
	for (T item : arr) {
		std::cout << item << " ";
	}
	std::cout << "\n";
}

template <typename T>
void print(std::vector<std::vector<T>>& arr2d) {
	for (std::vector<T>& arr : arr2d) {
		print(arr);
	}
	std::cout << "\n";
}

BOOST_AUTO_TEST_SUITE(execution_policy_suite)

BOOST_AUTO_TEST_CASE(execution_policy_test) {
	TEST_MARKER();
	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// Standard sequential sort
	std::sort(vec.begin(), vec.end());
	
	// Note: If an exception occurs during the usage of an algorithm with an execution policy, std::terminate is called
	// Sequential execution
	std::sort(std::execution::seq, vec.begin(), vec.end());
	
	// Parallel execution
	std::sort(std::execution::par, vec.begin(), vec.end());
	
	// Parallel and vectorised execution
	std::sort(std::execution::par_unseq, vec.begin(), vec.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(new_algorithm_suite)

BOOST_AUTO_TEST_CASE(new_algorithm_test) {
	TEST_MARKER();

	// for_each_n
	std::vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::for_each_n(std::execution::par, vec1.begin(), 5, [](int& val) {
		val *= val;
	});
	print(vec1);

	// exclusive_scan and inclusive_scam
	std::vector<int> vec2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::exclusive_scan(std::execution::par, vec2.begin(), vec2.end(), vec2.begin(), 1, [](int x, int y) { return x * y; });
	print(vec2);

	std::vector<int> vec3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::inclusive_scan(std::execution::par, vec3.begin(), vec3.end(), vec3.begin(), [](int x, int y) { return x * y; }, 1);
	print(vec3);

	// transform_exclusive_scan and transform_inclusive_scan
	std::vector<int> vec4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::transform_exclusive_scan(std::execution::par, vec4.begin(), vec4.end(), vec4.begin(), 1, [](int x, int y) { return x * y; }, [](int val) { return val *= val; });
	print(vec4);

	std::vector<std::string> strVec = { "Only", "for", "testing", "purpose" };
	std::vector<std::size_t> vec5(strVec.size());
	std::transform_inclusive_scan(std::execution::par, strVec.begin(), strVec.end(), vec5.begin(), [](auto x, auto y) { return x + y; }, [](auto s) { return s.length(); }, std::size_t(0));
	print(vec5);

	// reduce and transform_reduce
	std::vector<std::string> strVec2 = { "Only", "for", "testing", "purpose" };
	std::string str = std::reduce(std::execution::par, strVec2.begin() + 1, strVec2.end(), strVec2[0], [](auto x, auto y) { return x + ":" + y;  });
	std::cout << "String: " << str << "\n";

	std::vector<int> vec6 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum = std::transform_reduce(std::execution::par, vec6.begin(), vec6.end(), 0, [](auto x, auto y) { return x + y; }, [](auto val) { return val * val; });
	std::cout << "Sum: " << sum << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()