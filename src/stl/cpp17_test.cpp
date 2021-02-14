#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <random>
#include <vector>

#include "test_util.h"

// RANDOM

BOOST_AUTO_TEST_CASE(test_random) {
	TEST_MARKER();
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution uid(0, 100);
	auto r = uid(mt);
	std::cout << r << "\n";
}

// TAG DISPATCHING

BOOST_AUTO_TEST_CASE(test_tag_dispatching) {
	TEST_MARKER();
	struct foo {
		struct tag_1 {};
		struct tag_2 {};
		foo() {
			std::cout << "Default constructor\n";
		}
		explicit foo(tag_1) {
			std::cout << "Constructor 1\n";
		}
		explicit foo(tag_2) {
			std::cout << "Constructor 2\n";
		}
	};
	foo f;
	foo f_1{foo::tag_1{}};
	foo f_2{foo::tag_2{}};
}