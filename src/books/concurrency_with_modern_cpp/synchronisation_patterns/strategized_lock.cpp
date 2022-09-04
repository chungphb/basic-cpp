#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include <shared_mutex>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(strategized_lock_suite)

class Lock {
public:
	virtual void lock() const = 0;
	virtual void unlock() const = 0;
};

class StrategizedLocking {
	Lock& lock;
public:
	StrategizedLocking(Lock& l) : lock(l) {
		lock.lock();
	}
	~StrategizedLocking() {
		lock.unlock();
	}
};

struct NullObjectMutex {
	void lock() {}
	void unlock() {}
};

class NoLock : public Lock {
	mutable NullObjectMutex nullObjectMutex;
	void lock() const override {
		std::cout << "NoLock::lock: \n";
		nullObjectMutex.lock();
	}
	void unlock() const override {
		std::cout << "NoLock::unlock: \n";
		nullObjectMutex.unlock();
	}
};

class ExclusiveLock : public Lock {
	mutable std::mutex mutex;
	void lock() const override {
		std::cout << "ExclusiveLock::lock: \n";
		mutex.lock();
	}
	void unlock() const override {
		std::cout << "ExclusiveLock::unlock: \n";
		mutex.unlock();
	}
};

class SharedLock : public Lock {
	mutable std::shared_mutex sharedMutex;
	void lock() const override {
		std::cout << "SharedLock::lock: \n";
		sharedMutex.lock();
	}
	void unlock() const override {
		std::cout << "SharedLock::unlock: \n";
		sharedMutex.unlock();
	}
};

BOOST_AUTO_TEST_CASE(strategized_lock_test) {
	TEST_MARKER();
	NoLock noLock;
	StrategizedLocking stratLock1(noLock);
	{
		ExclusiveLock exclusiveLock;
		StrategizedLocking stratLock2(exclusiveLock);
		{
			SharedLock sharedLock;
			StrategizedLocking stratLock3(sharedLock);
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()