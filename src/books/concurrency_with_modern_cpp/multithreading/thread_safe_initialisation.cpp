#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include <mutex>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(constant_expressions_suite)

class MyDouble {
private:
	double myVal1;
	double myVal2;
public:
	constexpr MyDouble(double v1, double v2) : myVal1(v1), myVal2(v2) {}
	constexpr double getSum() const {
		return myVal1 + myVal2;
	}
};

BOOST_AUTO_TEST_CASE(constant_expressions_test) {
	TEST_MARKER();
	constexpr double myStatVal = 2.0;
	constexpr MyDouble myStat(10.5, myStatVal);
	constexpr double sumStat = myStat.getSum();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(call_once_and_once_flag_suite)

std::once_flag onceFlag;

void doOnce() {
	std::call_once(onceFlag, [] {
		std::cout << "Only once.\n";
	});
}

void doOnce2() {
	std::call_once(onceFlag, [] {
		std::cout << "Only once 2.\n";
	});
}

BOOST_AUTO_TEST_CASE(call_once_and_once_flag_test) {
	TEST_MARKER();
	std::thread t1(doOnce);
	std::thread t2(doOnce);
	std::thread t3(doOnce2);
	std::thread t4(doOnce2);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(meyers_singleton_suite)

class Singleton {
private:
public:
	Singleton();
	~Singleton();
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
};

Singleton::Singleton() = default;
Singleton::~Singleton() = default;

BOOST_AUTO_TEST_CASE(meyers_singleton_test) {
	TEST_MARKER();
	Singleton::getInstance();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()