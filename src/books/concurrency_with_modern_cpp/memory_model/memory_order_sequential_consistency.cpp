#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <atomic>
#include <thread>
#include <string>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(sequential_consistency_suite)

std::string word;
std::atomic<bool> ready{false};

void consumer() {
	while (!ready.load()) {}
	std::cout << word << std::endl;
}

void producer() {
	word = "Done";
	ready = true;
}

BOOST_AUTO_TEST_CASE(producer_consumer_sequential_consistency_test) {
	std::thread prod(producer);
	std::thread con(consumer);
	prod.join();
	con.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()