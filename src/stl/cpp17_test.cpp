#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <type_traits>

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
// Link: https://www.fluentcpp.com/2018/04/27/tag-dispatching/

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

// EXPRESSIVE TYPES

// Strongly typed constructors
// Link: https://www.fluentcpp.com/2016/12/05/named-constructors/

BOOST_AUTO_TEST_CASE(test_strongly_typed_constructors) {
	TEST_MARKER();

	struct expressive_type_1 {
	public:
		expressive_type_1(int v) : val{v} {}
		int get() const {
			return val;
		}
	private:
		int val;
	};

	struct expressive_type_2 {
	public:
		expressive_type_2(int v) : val{v} {}
		int get() const {
			return val;
		}
	private:
		int val;
	};

	struct foo {
	public:
		foo(expressive_type_1 v) : val{v.get()} {
			std::cout << "Constructor 1\n";
		}
		foo(expressive_type_2 v) : val{v.get() + 1} {
			std::cout << "Constructor 2\n";
		}
	private:
		int val;
	};

	foo f_1{expressive_type_1{1}};
	foo f_2{expressive_type_2{2}};
}

// Strongly types
// Link: https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/

namespace test_strong_types_ns {

template <typename t, typename parameter>
struct strong_type {
public:
	explicit strong_type(const t& v) : val{v} {}
	explicit strong_type(t&& v) : val{std::move(v)} {}
	t& get() {
		return val;
	}
	const t& get() const {
		return val;
	}
private:
	t val;
};

}

BOOST_AUTO_TEST_CASE(test_strong_types) {
	TEST_MARKER();

	using namespace test_strong_types_ns;
	using strong_type_1 = strong_type<int, struct strong_type_1_parameter>;
	using strong_type_2 = strong_type<int, struct strong_type_2_parameter>;

	struct foo {
	public:
		foo(strong_type_1 v_1, strong_type_2 v_2) : val_1{v_1.get()}, val_2{v_2.get()} {}
	private:
		int val_1;
		int val_2;
	};
	foo f(strong_type_1{1}, strong_type_2{1});
}

// Passing strong types by reference
// Link: https://www.fluentcpp.com/2016/12/12/passing-strong-types-by-reference/
// Link: https://www.fluentcpp.com/2017/03/06/passing-strong-types-reference-revisited/

namespace test_passing_strong_types_by_reference_ns {

template <typename t, typename parameter>
struct strong_type {
public:
	explicit strong_type(const t& v) : val{v} {}
	template<typename t_ = t>
	explicit strong_type(t&& v, typename std::enable_if<!std::is_reference<t_>{}, std::nullptr_t>::value = nullptr) : val{std::move(v)} {}
	t& get() {
		return val;
	}
	const t& get() const {
		return val;
	}
private:
	t val;
};

}

BOOST_AUTO_TEST_CASE(test_passing_strong_types_by_reference) {
	TEST_MARKER();

	using namespace test_passing_strong_types_by_reference_ns;
	using strong_type_1_ref = strong_type<int&, struct strong_type_1_parameter>;
	using strong_type_2_ref = strong_type<int&, struct strong_type_2_parameter>;

	struct foo {
		foo(strong_type_1_ref v_1, strong_type_2_ref v_2) : val_1{v_1.get()}, val_2{v_2.get()} {}
		int& val_1;
		int& val_2;
	};
	int val_1 = 1;
	int val_2 = 1;
	foo f(strong_type_1_ref{val_1}, strong_type_2_ref{val_2});
	f.val_1 = 2;
	f.val_2 = 2;
	BOOST_CHECK(val_1 == 2);
	BOOST_CHECK(val_2 == 2);
}