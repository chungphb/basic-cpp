#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <atomic>
#include <thread>
#include <string>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(consume_release_suite)

std::atomic<std::string*> ptr;

void producer() {
	std::string* p = new std::string("Hello world!");
	ptr.store(p, std::memory_order_release);
}

void consumer() {
	std::string* p2;
	while (!(p2 = ptr.load(std::memory_order_consume)));
	std::cout << "*p2 = " << *p2 << "\n";
}

BOOST_AUTO_TEST_CASE(spinlock_acquire_release_test) {
	TEST_MARKER();
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	delete ptr;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()