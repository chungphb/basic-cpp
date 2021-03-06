#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <type_traits>
#include <functional>
#include <ratio>

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

// Strong lambdas
// Link: https://www.fluentcpp.com/2017/02/20/strong-lambdas-strong-generic-types/

namespace test_strong_lambdas_ns {

using namespace test_strong_types_ns;

template <typename function>
using strong_lambda_1 = strong_type<function, struct strong_lambda_1_parameter>;

template <typename function>
using strong_lambda_2 = strong_type<function, struct strong_lambda_2_parameter>;

// Since we don't know exactly what the type of the lambda we pass to strong_type is, we need a function to deduce it   
template <template <typename t> class generic_type_name, typename t>
generic_type_name<t> make_named(const t& val) {
	return generic_type_name<t>{val};
}

template <typename function_1, typename function_2>
void f(strong_lambda_1<function_1> f_1, strong_lambda_2<function_2> f_2) {
	f_1.get()();
	f_2.get()();
}

}

BOOST_AUTO_TEST_CASE(test_strong_lambdas) {
	TEST_MARKER();

	using namespace test_strong_lambdas_ns;

	f(make_named<strong_lambda_1>([] {
		std::cout << "Lambda 1\n";
	}), make_named<strong_lambda_2>([] {
		std::cout << "Lambda 2\n";
	}));
}

// Performance
// Link: https://www.fluentcpp.com/2017/05/05/news-strong-types-are-free/

// Inheriting the underlying type's functionalities
// Link: https://www.fluentcpp.com/2017/05/23/strong-types-inheriting-functionalities-from-underlying/

namespace test_inheriting_the_underlying_types_functionalities_ns {

template <typename t, typename parameter, template<typename> class... funcs>
struct strong_type : funcs<strong_type<t, parameter, funcs...>>... {
public:
	explicit strong_type(const t& v) : val{v} {}
	t& get() {
		return val;
	}
	const t& get() const {
		return val;
	}
private:
	t val;
};

template <typename t, template <typename> class crtpType>
struct crtp {
	t& underlying() {
		return static_cast<t&>(*this);
	}
	const t& underlying() const {
		return static_cast<const t&>(*this);
	}
};

template <typename t>
struct addable : crtp<t, addable> {
	t operator+(const t& other) {
		return t(this->underlying().get() + other.get());
	}
};

template <typename t>
struct printable : crtp<t, printable> {
	void print(std::ostream& os) const {
		os << this->underlying().get();
	}
};

template <typename t, typename parameter, template<typename> class... funcs>
std::ostream& operator<<(std::ostream& os, const strong_type<t, parameter, funcs...>& obj) {
	obj.print(os);
	return os;
}

}

BOOST_AUTO_TEST_CASE(test_inheriting_the_underlying_types_functionalities) {
	TEST_MARKER();

	using namespace test_inheriting_the_underlying_types_functionalities_ns;
	using length_t = strong_type<double, struct length_parameter, addable, printable>;

	length_t l_1{1};
	length_t l_2{1};
	length_t l = l_1 + l_2;
	std::cout << l_1 << " + " << l_2 << " = " << l << "\n";
}

// Strong types conversions
// Link: https://www.fluentcpp.com/2017/05/26/strong-types-conversions/

namespace test_strong_types_conversions_ns {

template <typename t, t(*from)(t), t(*to)(t)>
struct convert {
	static t convertFrom(t v) {
		return from(v);
	}
	static t convertTo(t v) {
		return to(v);
	}
};

template <typename t, typename parameter, typename converter, template<typename> class... funcs>
struct strong_type_impl : funcs<strong_type_impl<t, parameter, converter, funcs...>>... {
public:
	strong_type_impl() = default;
	explicit strong_type_impl(const t& v) : val{v} {}
	template<typename t_ = t>
	explicit strong_type_impl(t&& v, typename std::enable_if<!std::is_reference<t_>{}, std::nullptr_t>::type = nullptr) : val{std::move(v)} {}
	t& get() {
		return val;
	}
	const t& get() const {
		return val;
	}
	using underlying_type = t;
	template <typename converter_2>
	operator strong_type_impl<t, parameter, converter_2, funcs...>() const {
		return strong_type_impl<t, parameter, converter_2, funcs...>(converter_2::convertFrom(converter::convertTo(get())));
	}
	template <t(*f)(t), t(*g)(t)>
	struct compose {
		static t func(t v) {
			return f(g(v));
		}
	};
	template <typename converter_1, typename converter_2>
	using compose_converter = convert<t, compose<converter_1::convertFrom, converter_2::convertFrom>::func, compose<converter_1::convertTo, converter_2::convertTo>::func>;
	template <typename converter_2>
	using get_convertible = strong_type_impl<t, parameter, compose_converter<converter, converter_2>, funcs...>;
private:
	t val;
};

template <typename t, typename ratio>
struct convert_with_ratio {
	static t convertFrom(t v) {
		return v * ratio::den / ratio::num;
	}
	static t convertTo(t v) {
		return v * ratio::num / ratio::den;
	}
};

template <typename t, typename parameter, template <typename> class... funcs>
using strong_type = strong_type_impl<t, parameter, convert_with_ratio<t, std::ratio<1>>, funcs...>;

template <typename strong_type, typename ratio>
using multiple_of = typename strong_type::template get_convertible<convert_with_ratio<typename strong_type::underlying_type, ratio>>;

template <typename strong_type, typename converter>
using convertible_to = typename strong_type::template get_convertible<converter>;

template <template <typename t> class strong_type, typename t>
strong_type<t> make_named(const t& v) {
	return strong_type<t>(v);
}

namespace ns = test_inheriting_the_underlying_types_functionalities_ns;

using meter = strong_type<double, struct meter_tag, ns::addable>;
meter operator"" _meter(unsigned long long v) {
	return meter(v);
};

using kilometer = multiple_of<meter, std::kilo>;
kilometer operator"" _kilometer(unsigned long long v) {
	return kilometer(v);
};

void print(meter m) {
	std::cout << m.get() << "m\n";
}

}

BOOST_AUTO_TEST_CASE(test_strong_types_conversions) {
	TEST_MARKER();

	using namespace test_strong_types_conversions_ns;
	
	print(1_kilometer + 500_meter);
}

// Implementing a hash function for strong types
// Link: https://www.fluentcpp.com/2017/05/30/implementing-a-hash-function-for-strong-types/

namespace std {
	
namespace ns = test_strong_types_conversions_ns;

template <typename t, typename parameter, typename converter, template<typename> class... funcs>
struct hash<ns::strong_type_impl<t, parameter, converter, funcs...>> {
	using strong_type = ns::strong_type_impl<t, parameter, converter, funcs...>;
	using check_if_hashable = typename std::enable_if<strong_type::is_hashable, void>::type;
	size_t operator()(const strong_type& val) const {
		return std::hash<t>()(val.get());
	}
};

}

namespace test_implementing_a_hash_function_for_strong_types_ns {

namespace ns = test_strong_types_conversions_ns;

template <typename t, template <typename> class crtpType>
struct crtp {
	t& underlying() {
		return static_cast<t&>(*this);
	}
	const t& underlying() const {
		return static_cast<const t&>(*this);
	}
};

template <typename t>
struct comparable : public crtp<t, comparable> {
	friend bool operator==(const comparable<t>& lhs, const t& rhs) {
		return lhs.underlying().get() == rhs.get();
	}
};

template <typename t>
struct hashable {
	static constexpr bool is_hashable = true;
};

}

BOOST_AUTO_TEST_CASE(test_implementing_a_hash_function_for_strong_types) {
	TEST_MARKER();

	using namespace test_implementing_a_hash_function_for_strong_types_ns;
	using namespace test_strong_types_conversions_ns;

	using key_t = strong_type<int, struct key_paramater, comparable, hashable>;
	using value_t = strong_type<int, struct value_parameter>;
	std::unordered_map<key_t, value_t> map{{key_t{1}, value_t{1}}, {key_t{2}, value_t{2}}};
	std::cout << map[key_t{1}].get() << "\n";
}

// Calling functions and methods on strong types
// Link: https://www.fluentcpp.com/2017/11/07/calling-functions-methods-strong-types/

namespace test_calling_functions_and_methods_on_strong_types_ns {

namespace ns = test_strong_types_conversions_ns;

template <typename t, template <typename> class crtpType>
struct crtp {
	t& underlying() {
		return static_cast<t&>(*this);
	}
	const t& underlying() const {
		return static_cast<const t&>(*this);
	}
};

// Function callable

template <typename strong_type>
struct function_callable;

template <typename t, typename parameter, typename converter, template<typename> class... funcs>
struct function_callable<ns::strong_type_impl<t, parameter, converter, funcs...>> : public crtp<ns::strong_type_impl<t, parameter, converter, funcs...>, function_callable> {
	operator t&() {
		return this->underlying().get();
	}

	operator const t&() const {
		return this->underlying().get();
	}
};

// Method callbale

template <typename strong_type>
struct method_callable;

template <typename t, typename parameter, typename converter, template<typename> class... funcs>
struct method_callable<ns::strong_type_impl<t, parameter, converter, funcs...>> : public crtp<ns::strong_type_impl<t, parameter, converter, funcs...>, method_callable> {
	t* operator->() {
		return std::addressof(this->underlying().get());
	}

	const t* operator->() const {
		return std::addressof(this->underlying().get());
	}
};

// Callable

template <typename strong_type>
struct callable : function_callable<strong_type>, method_callable<strong_type> {};

}

BOOST_AUTO_TEST_CASE(test_calling_functions_and_methods_on_strong_types) {
	TEST_MARKER();

	using namespace test_calling_functions_and_methods_on_strong_types_ns;
	using namespace test_strong_types_conversions_ns;

	// Test calling functions

	using id_t = strong_type<int, struct id_tag, function_callable>;
	auto incr = [](int& val) {
		val++;
	};
	auto func = [&incr](id_t& id) {
		incr(id);
		std::cout << id << "\n";
	};
	id_t id{0};
	func(id);

	// Test calling methods

	struct foo {
	public:
		foo(int v) : val{v} {}
		void func() {
			std::cout << val << "\n";
		}
	private:
		int val;
	};
	using strong_foo = strong_type<foo, struct strong_foo_tag, method_callable>;
	foo f{1};
	strong_foo sf{f};
	sf->func();
}

// Strong types implicit conversions
// Link: https://www.fluentcpp.com/2018/01/05/making-strong-types-implicitly-convertible/

namespace test_strong_types_implicit_conversions_ns {

namespace ns = test_strong_types_conversions_ns;

template <typename t, template <typename> class crtpType>
struct crtp {
	t& underlying() {
		return static_cast<t&>(*this);
	}
	const t& underlying() const {
		return static_cast<const t&>(*this);
	}
};

template <typename dst_t>
struct implicitly_convertible_to {
	template <typename src_t>
	struct impl : crtp<src_t, impl> {
		operator dst_t() const {
			return this->underlying().get();
		}
	};
};

}

BOOST_AUTO_TEST_CASE(test_strong_types_implicit_conversions) {
	TEST_MARKER();

	using namespace test_strong_types_implicit_conversions_ns;
	using namespace test_strong_types_conversions_ns;

	using id_t = strong_type<int, struct id_tag, implicitly_convertible_to<long>::impl>;
	auto print = [](long val) {
		std::cout << val << "\n";
	};
	auto func = [&print](id_t& id) {
		print(id);
	};
	id_t id{1};
	func(id);
}

// CRTP (CURIOUSLY RECURRING TEMPLATE PATTERN)

// Example
// Link: https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/

namespace test_crtp_example_ns {

template <typename t>
struct base {
public:
	void func() {
		std::cout << "Hello from base!\n";
		t& derived_obj = static_cast<t&>(*this);
		derived_obj.func_2();
	}
private:
	// Prevents two classes deriving from the same base crtp class
	base() {}
	friend t;
};

struct derived : public base<derived> {
public:
	void func_2() {
		std::cout << "Hello from derived!\n";
	}
};

// struct derived_2 : public base<derived> {}; /// Failed

}

BOOST_AUTO_TEST_CASE(test_crtp_example) {
	TEST_MARKER();
	using namespace test_crtp_example_ns;
	derived derived_obj;
	derived_obj.func();
}

// Usage
// Link: https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/

namespace test_crtp_usage_ns {
	
template <typename t>
struct addable {
	t operator+(t other) {
		t& underlying = static_cast<t&>(*this);
		return underlying.get_value() + other.get_value();
	}
};

template <typename t>
struct printable {
	void print() {
		t& underlying = static_cast<t&>(*this);
		std::cout << underlying.get_value() << "\n";
	}
};

struct foo : public addable<foo>, printable<foo> {
	foo(double v) : val{v} {}
	double get_value() {
		return val;
	}
	void set_value(double v) {
		val = v;
	}
private:
	double val;
};

}

BOOST_AUTO_TEST_CASE(test_crtp_usage) {
	TEST_MARKER();
	using namespace test_crtp_usage_ns;
	foo f_1{1}, f_2{2};
	foo f = f_1 + f_2;
	f.print();
}

// Implementation
// Link: https://www.fluentcpp.com/2017/05/19/crtp-helper/

namespace test_crtp_implementation_ns {

template <typename t, template<typename> class crtp_type>
struct crtp {
public:
	t& underlying() {
		return static_cast<t&>(*this);
	}
	const t& underlying() const {
		return static_cast<const t&>(*this);
	}
private:
	crtp() {}
	friend crtp_type<t>;
};

template <typename t>
struct addable : crtp<t, addable> {
public:
	t operator+(const t& other) {
		return t(this->underlying().get_value() + other.get_value());
	}
private:
	addable() {}
	friend t;
};

template <typename t>
struct printable : crtp<t, printable> {
public:
	void print() {
		std::cout << this->underlying().get_value() << "\n";
	}
private:
	printable() {}
	friend t;
};

struct foo : public addable<foo>, public printable<foo> {
public:
	foo() = default;
	foo(double v) : val{v} {}
	double& get_value() {
		return val;
	}
	const double& get_value() const {
		return val;
	}
	void set_value(double v) {
		val = v;
	}
private:
	double val;
};

}

BOOST_AUTO_TEST_CASE(test_crtp_implementation) {
	TEST_MARKER();
	using namespace test_crtp_implementation_ns;
	foo f_1{1}, f_2{2};
	foo f = f_1 + f_2;
	f.print();
}

// SFINAE (SUBSTITUTION FAILURE IS NOT AN ERROR)

// Example & Usage
// Link: https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/

namespace test_sfinae_usage_ns {

template <typename t>
struct foo {
public:
	void func(const t&) {
		std::cout << "lvalue\n";
	}
	template <typename t_ = t>
	void func(t&&, typename std::enable_if<!std::is_reference<t_>{}, std::nullptr_t>::type = nullptr) {
		std::cout << "rvalue\n";
	}
};

}

BOOST_AUTO_TEST_CASE(test_sfinae_usage) {
	TEST_MARKER();
	using namespace test_sfinae_usage_ns;
	foo<int> f;
	int val = 1;
	f.func(val);
	f.func(1);
	foo<int&> f_ref;
	f_ref.func(val);
}

// Implementation
// Link: https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/

namespace test_sfinae_implementation_ns {

template <typename t>
using is_not_reference = std::enable_if_t<!std::is_reference_v<t>>;

template <typename t>
struct foo {
public:
	void func(const t&) {
		std::cout << "lvalue\n";
	}
	template <typename t_ = t, typename = is_not_reference<t_>>
	void func(t&&) {
		std::cout << "rvalue\n";
	}
};
}

BOOST_AUTO_TEST_CASE(test_sfinae_implementation) {
	TEST_MARKER();
	using namespace test_sfinae_implementation_ns;
	foo<int> f;
	int val = 1;
	f.func(val);
	f.func(1);
	foo<int&> f_ref;
	f_ref.func(val);
}