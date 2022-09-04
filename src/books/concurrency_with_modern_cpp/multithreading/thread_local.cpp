#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(thread_local_suite)

std::mutex coutMutex;

thread_local std::string s("Hello from ");

void addThreadLocal(const std::string& s2) {
	s += s2;
	std::lock_guard<std::mutex> lockGuard(coutMutex);
	std::cout << s << "\n";
	std::cout << &s << "\n";
}

BOOST_AUTO_TEST_CASE(thread_methods_test) {
	TEST_MARKER();
	std::thread t1(addThreadLocal, "t1");
	std::thread t2(addThreadLocal, "t2");
	std::thread t3(addThreadLocal, "t3");
	std::thread t4(addThreadLocal, "t4");
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()