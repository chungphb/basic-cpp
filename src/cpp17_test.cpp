#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <random>

BOOST_AUTO_TEST_CASE(test_sample) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution uid(0, 100);
	auto r = uid(mt);
	std::cout << "Hello " << r << std::endl;
}