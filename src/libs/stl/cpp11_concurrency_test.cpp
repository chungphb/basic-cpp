#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <thread>
#include <iostream>

#include "test_util.h"

// THREAD

BOOST_AUTO_TEST_SUITE(test_thread)

void task() {
	std::cout << "Hello from thread #" << std::this_thread::get_id() << std::endl;
}

BOOST_AUTO_TEST_CASE(test_starting_thread) {
	TEST_MARKER();
	std::thread thread{task};
	thread.join();
}

BOOST_AUTO_TEST_CASE(test_starting_multiple_threads) {
	TEST_MARKER();
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{task});
	}
	for (auto& thread : threads) {
		thread.join();
	}
}

BOOST_AUTO_TEST_CASE(test_starting_multiple_threads_with_lambdas) {
	TEST_MARKER();
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{[] {
			std::cout << "Hello from thread #" << std::this_thread::get_id() << std::endl;
		}});
	}
	for (auto& thread : threads) {
		thread.join();
	}
}

BOOST_AUTO_TEST_SUITE_END()
