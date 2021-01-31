#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include <boost/intrusive/list.hpp>

#include <list>

#include "test_util.h"

// HOW TO USE BOOST.TEST

// 1. Using base hooks

BOOST_AUTO_TEST_CASE(test_intrusive_containers_vs_non_intrusive_containers) {
	TEST_MARKER();
	
	// Intrusive containers
	struct foo : public boost::intrusive::list_base_hook<> {};
	using foo_list = boost::intrusive::list<foo>;
	foo f;
	foo_list fl;
	fl.push_back(f);
	BOOST_CHECK(&f == &fl.front());

	// Non-intrusive containers
	struct foo_2 {};
	using foo_2_list = std::list<foo_2>;
	foo_2 f2;
	foo_2_list f2l;
	f2l.push_back(f2);
	BOOST_CHECK(&f2 != &f2l.front());
}

BOOST_AUTO_TEST_CASE(test_multiple_base_hooks) {
	TEST_MARKER();
	using namespace boost::intrusive;
	struct tag_1;
	struct tag_2;
	using base_hook_1 = list_base_hook<tag<tag_1>>;
	using base_hook_2 = list_base_hook<tag<tag_2>>;
	struct foo : public base_hook_1, public base_hook_2 {};
	using foo_list = list<foo, base_hook<base_hook_1>>;
	using foo_list_2 = list<foo, base_hook<base_hook_2>>;

	foo f;
	foo_list fl;
	fl.push_back(f);
	foo_list_2 fl2;
	fl2.push_back(f);

	BOOST_CHECK(&f == &fl.front());
	BOOST_CHECK(&f == &fl2.front());
}