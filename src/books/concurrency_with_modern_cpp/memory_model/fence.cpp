#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <atomic>
#include <thread>
#include <string>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(acquire_release_fence_suite)

std::atomic<std::string*> ptr;
int data;
std::atomic<int> atomicData;

void producer() {
	std::string* p = new std::string("Hello world!");
	data = 2011;
	atomicData.store(2014, std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_release);
	ptr.store(p, std::memory_order_relaxed);
}

void consumer() {
	std::string* p2;
	while (!(p2 = ptr.load(std::memory_order_relaxed)));
	std::atomic_thread_fence(std::memory_order_acquire);
	std::cout << "*p2: " << *p2 << "\n";
	std::cout << "data: " << data << "\n";
	std::cout << "atomicData:" << atomicData.load(std::memory_order_relaxed) << "\n";
}

BOOST_AUTO_TEST_CASE(acquire_release_fence_test) {
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	delete ptr;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()