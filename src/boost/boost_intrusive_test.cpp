#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include <boost/intrusive/list.hpp>

#include <list>

#include "test_util.h"

// HOW TO USE BOOST.INSTRUSIVE

// 1. Using base hooks

BOOST_AUTO_TEST_CASE(test_base_hook) {
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

// 2. Using member hooks

BOOST_AUTO_TEST_CASE(test_member_hook) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo {
		list_member_hook<> hook;
	};
	using member_hook_option = member_hook<foo, list_member_hook<>, &foo::hook>;
	using foo_list = list<foo, member_hook_option>;

	foo f;
	foo_list fl;
	fl.push_back(f);

	BOOST_CHECK(&f == &fl.front());
}

BOOST_AUTO_TEST_CASE(test_multiple_member_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo {
		list_member_hook<> hook_1;
		list_member_hook<> hook_2;
	};
	using member_hook_option_1 = member_hook<foo, list_member_hook<>, &foo::hook_1>;
	using foo_list_1 = list<foo, member_hook_option_1>;
	using member_hook_option_2 = member_hook<foo, list_member_hook<>, &foo::hook_2>;
	using foo_list_2 = list<foo, member_hook_option_2>;

	foo f;
	foo_list_1 fl1;
	fl1.push_back(f);
	foo_list_2 fl2;
	fl2.push_back(f);

	BOOST_CHECK(&f == &fl1.front());
	BOOST_CHECK(&f == &fl2.front());
}

// 3. Using both hooks

BOOST_AUTO_TEST_CASE(test_both_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public list_base_hook<> {
		list_member_hook<> hook;
	};
	using foo_list = list<foo>;
	using member_hook_option = member_hook<foo, list_member_hook<>, &foo::hook>;
	using foo_list_2 = list<foo, member_hook_option>;

	foo f;
	foo_list fl;
	fl.push_back(f);
	foo_list_2 fl2;
	fl2.push_back(f);

	BOOST_CHECK(&f == &fl.front());
	BOOST_CHECK(&f == &fl2.front());
}

// WHEN TO USE BOOST.INTRUSIVE

using namespace boost::intrusive;
struct base : public list_base_hook<> {
	using object_list = list<base>;
	static object_list ol;
	base() {
		ol.push_back(*this);
	}
	virtual ~base() {
		ol.erase(ol.s_iterator_to(*this));
	}
	virtual void func() {
		std::cout << "base\n";
	}
};

base::object_list base::ol;

struct derived_0 : public base {
	int val = 0;
	void func() {
		std::cout << "derived_0\n";
	}
};

struct derived_1 : public base {
	int val = 0;
	void func() {
		std::cout << "derived_1\n";
	}
};

void func_all() {
	auto e = base::ol.end();
	for (auto i = base::ol.begin(); i != e; i++) {
		i->func();
	}
}

BOOST_AUTO_TEST_CASE(test_storing_base_and_derived_objects_in_the_same_container) {
	TEST_MARKER();
	base b;
	derived_0 d0;
	derived_1 d1;
	func_all();
}