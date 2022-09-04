#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include <condition_variable>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(condition_variable_suite)

std::mutex mutex;
std::condition_variable condVar;
bool dataReady(false);

void doTheWork() {
	std::cout << "Processing shared data.\n";
}

void waitForWork() {
	std::cout << "Receiver: Waiting for work.\n";
	std::unique_lock<std::mutex> lock(mutex);
	condVar.wait(lock, [] { return dataReady; });
	doTheWork();
	std::cout << "Work done.\n";
}

void setDataReady() {
	{
		std::lock_guard<std::mutex> lock(mutex);
		dataReady = true;
	}
	std::cout << "Sender: Data is ready.\n";
	condVar.notify_one();
}

BOOST_AUTO_TEST_CASE(condition_variable_test) {
	TEST_MARKER();
	std::thread t1(waitForWork);
	std::thread t2(setDataReady);
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()