#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <chrono>
#include <vector>
#include <atomic>
#include <thread>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(atomic_condition_suite)

std::vector<int> mySharedWork;
std::atomic<bool> dataReady(false);

void waitingForWork() {
	std::cout << "Waiting...\n";
	while (!dataReady.load()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	mySharedWork[1] = 2;
	std::cout << "Done\n";
}

void setDataReady() {
	mySharedWork = { 1, 0, 3 };
	dataReady = true;
	std::cout << "Data prepared\n";
}

BOOST_AUTO_TEST_CASE(atomic_condition_test) {
	TEST_MARKER();
	std::thread t1(waitingForWork);
	std::thread t2(setDataReady);
	t1.join();
	t2.join();
	for (auto val : mySharedWork) {
		std::cout << val << " ";
	}
	std::cout << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(fetch_mult_suite)

template <typename T>
T fetch_mult(std::atomic<T>& shared, T mult) {
	T oldValue = shared.load();
	while (!shared.compare_exchange_strong(oldValue, oldValue * mult));
	return oldValue;
}

BOOST_AUTO_TEST_CASE(fetch_mult_test) {
	TEST_MARKER();
	std::atomic<int> myInt{ 5 };
	std::cout << myInt << std::endl;
	fetch_mult(myInt, 5);
	std::cout << myInt << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()