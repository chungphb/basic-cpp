#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <atomic>
#include <thread>
#include <vector>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(counter_suite)

std::atomic<int> count(0);

void add() {
	for (int n = 0; n < 1000; ++n) {
		count.fetch_add(1, std::memory_order_relaxed);
	}
}

BOOST_AUTO_TEST_CASE(counter_test) {
	std::vector<std::thread> threads;
	for (int n = 0; n < 10; ++n) {
		threads.emplace_back(add);
	}
	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << "Counter: " << count << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()