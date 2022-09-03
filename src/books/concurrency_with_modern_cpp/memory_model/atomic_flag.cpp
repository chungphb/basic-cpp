#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <atomic>
#include <thread>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(spinlock_suite)

class Spinlock {
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	void lock() {
		while (flag.test_and_set());
	}

	void unlock() {
		flag.clear();
	}
};

int counter = 0;
Spinlock spin;

void workOnResource() {
	spin.lock();
	++counter;
	spin.unlock();
}

BOOST_AUTO_TEST_CASE(spinlock_test) {
	TEST_MARKER();
	std::thread t1(workOnResource);
	std::thread t2(workOnResource);
	t1.join();
	t2.join();
	std::cout << counter << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()