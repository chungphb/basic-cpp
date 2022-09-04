#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(scoped_lock_suite)

class ScopedLock {
private:
	std::mutex& mutex;
public:
	explicit ScopedLock(std::mutex& mut) : mutex(mut) {
		mutex.lock();
		std::cout << "Lock the mutex: " << &mutex << "\n";
	}

	~ScopedLock() {
		std::cout << "Unlock the mutex: " << &mutex << "\n";
		mutex.unlock();
	}
};

BOOST_AUTO_TEST_CASE(scoped_lock_test) {
	TEST_MARKER();
	std::mutex mutex1;
	ScopedLock scopedLock1(mutex1);

	std::cout << "Before local scope\n";
	{
		std::mutex mutex2;
		ScopedLock scopedLock2(mutex2);
	}
	std::cout << "After local scope\n";

	std::cout << "Before try-catch block\n";
	try {
		std::mutex mutex3;
		ScopedLock scopedLock3(mutex3);
		throw std::bad_alloc();
	} catch (std::bad_alloc& err) {
		std::cout << err.what() << "\n";
	}
	std::cout << "After try-catch block\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()