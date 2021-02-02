#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <random>
#include <vector>

#include "test_util.h"

BOOST_AUTO_TEST_CASE(test_random) {
	TEST_MARKER();
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution uid(0, 100);
	auto r = uid(mt);
	std::cout << "Hello " << r << std::endl;
}

BOOST_AUTO_TEST_CASE(test_vector) {
	TEST_MARKER();
	std::vector<int> vec{1, 2, 3, 4};
	BOOST_TEST((vec == std::vector{1, 2, 3, 4}));
}