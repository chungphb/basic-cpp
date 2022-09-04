#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(singleton_suite)

class Singleton {
public:
	Singleton();
	~Singleton();
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
};

Singleton::Singleton() = default;
Singleton::~Singleton() = default;

BOOST_AUTO_TEST_CASE(singleton_test) {
	auto lambda = [] {
		std::cout << &Singleton::getInstance() << "\n";
	};
	std::thread t1(lambda);
	std::thread t2(lambda);
	std::thread t3(lambda);
	t1.join();
	t2.join();
	t3.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()