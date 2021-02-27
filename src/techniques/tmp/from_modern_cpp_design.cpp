#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include "test_util.h"

void print(std::string_view str) {
	std::cout << str << "\n";
}

void print(long val) {
	std::cout << val << "\n";
}

// 1. POLICY-BASED CLASS DESIGN

// 1.1. GENERAL FORM

namespace test_policy_based_class_design_ns {

// Policy classes

template <class t>
struct policy_class_1 {
	static void apply() {
		print("policy class 1");
	}
};

template <class t>
struct policy_class_2 {
	static void apply() {
		print("policy class 2");
	}
};

template <class t>
struct policy_class_3 {
public:
	void apply() {
		print("policy class 3");
	}
	void fun() {
		print("policy class 3: an enriched function");
	}
private:
	t var;
};

// Host class

template <class policy>
class host_class : public policy {};

}

BOOST_AUTO_TEST_CASE(test_general_form) {
	TEST_MARKER();

	using namespace test_policy_based_class_design_ns;

	struct foo {};

	using my_host_1 = host_class<policy_class_1<foo>>;
	my_host_1 host_1;
	host_1.apply();

	using my_host_2 = host_class<policy_class_2<foo>>;
	my_host_2 host_2;
	host_2.apply();

	using my_host_3 = host_class<policy_class_3<foo>>;
	my_host_3 host_3;
	host_3.apply();
}

// 1.2. IMPLEMENTING POLICY CLASSES WITH TEMPLATE TEMPLATE PARAMETERS

namespace test_policy_based_class_design_ns {

// Host class

struct specific_class {};

struct another_specific_class {};

template <template <class> class policy>
class specific_host_class : public policy<specific_class> {
	void fun() {
		policy<another_specific_class>().apply();
	}
};

}

BOOST_AUTO_TEST_CASE(test_implementing_policy_classes_with_template_template_parameters) {
	TEST_MARKER();

	using namespace test_policy_based_class_design_ns;

	using my_specific_host_1 = specific_host_class<policy_class_1>;
	my_specific_host_1 specific_host_1;
	specific_host_1.apply();

	using my_specific_host_2 = specific_host_class<policy_class_2>;
	my_specific_host_2 specific_host_2;
	specific_host_2.apply();

	using my_specific_host_3 = specific_host_class<policy_class_3>;
	my_specific_host_3 specific_host_3;
	specific_host_3.apply();
}

// 1.3. DESTRUCTORS OF POLICY CLASSES

namespace test_policy_based_class_design_ns {

// Policy classes

template <class t>
struct policy_class_4 {
	static void* apply() {
		print("policy class 4");
	}
protected:
	~policy_class_4() {}
};

}

BOOST_AUTO_TEST_CASE(test_destructors_of_policy_classes) {
	TEST_MARKER();

	using namespace test_policy_based_class_design_ns;

	using my_specific_host = specific_host_class<policy_class_4>;
	my_specific_host specific_host;
	policy_class_4<specific_class>* policy_ptr = &specific_host; // legal code
	// delete policy_ptr; /// prevent applying delete to a pointer to a policy class from the outsiders
}

// 1.4. COMBINING POLICY CLASSES

namespace test_policy_based_class_design_ns {

template <class t>
struct first_policy_class_1 {
	static void apply_first_policy() {
		print("first policy class 1");
	}
};

template <class t>
struct first_policy_class_2 {
	static void apply_first_policy() {
		print("first policy class 2");
	}
};

template <class t>
struct second_policy_class_1 {
	static void apply_second_policy() {
		print("second policy class 1");
	}
};

template <class t>
struct second_policy_class_2 {
	static void apply_second_policy() {
		print("another policy class 2");
	}
};

// Host class

template
<
	class t,
	template <class> class first_policy,
	template <class> class second_policy
>
struct combined_host_class : first_policy<t>, second_policy<t> {};

}

BOOST_AUTO_TEST_CASE(test_combining_policy_classes) {
	TEST_MARKER();

	using namespace test_policy_based_class_design_ns;

	struct foo {};

	using my_combined_host_11 = combined_host_class<foo, first_policy_class_1, second_policy_class_1>;
	my_combined_host_11 combined_host_11;
	combined_host_11.apply_first_policy();
	combined_host_11.apply_second_policy();

	using my_combined_host_12 = combined_host_class<foo, first_policy_class_1, second_policy_class_2>;
	my_combined_host_12 combined_host_12;
	combined_host_12.apply_first_policy();
	combined_host_12.apply_second_policy();

	using my_combined_host_21 = combined_host_class<foo, first_policy_class_2, second_policy_class_1>;
	my_combined_host_21 combined_host_21;
	combined_host_21.apply_first_policy();
	combined_host_21.apply_second_policy();

	using my_combined_host_22 = combined_host_class<foo, first_policy_class_2, second_policy_class_2>;
	my_combined_host_22 combined_host_22;
	combined_host_22.apply_first_policy();
	combined_host_22.apply_second_policy();
}

// 1.5. COMPATIBLE AND INCOMPATIBLE POLICIES

namespace test_policy_based_class_design_ns {
namespace test_compatible_and_incompatible_policies_ns {

// Policy classes

template <class t>
struct policy_class_1 {
	static void apply() {
		print("third policy class 1");
	}
};

template <class t>
struct policy_class_2 {
	static void apply() {
		print("third policy class 2");
	}
	policy_class_2(const policy_class_1<t>&) {}
};

// Host class

template
<
	class t,
	template <class> class policy
>
struct host_class : policy<t> {
	host_class() {}
	template
	<
		class t_1,
		template <class> class policy_1
	>
	host_class(const host_class<t_1, policy_1>& other) : var{other.var}, policy<t>{other} {}
	template <class t_1, template <class> class policy_1>
	friend struct host_class;
private:
	t var;	
};

}
}

BOOST_AUTO_TEST_CASE(test_compatible_and_incompatible_policies) {
	TEST_MARKER();

	using namespace test_policy_based_class_design_ns::test_compatible_and_incompatible_policies_ns;

	struct foo {};

	using my_host_1 = host_class<foo, policy_class_1>;
	using my_host_2 = host_class<foo, policy_class_2>;

	my_host_1 host_1;
	my_host_2 host_2{host_1}; // legal conversion
	// my_host_1 host_3{host_2}; /// illegal conversion
}

// 2. TECHNIQUES

// 2.1. COMPILE-TIME ASSERTIONS

namespace test_techniques_ns {

template<bool> struct compile_time_checker {
	compile_time_checker(...);
};

template<> struct compile_time_checker<false> {};

#define STATIC_CHECK(expr, msg) \
{ \
	class ERROR_##msg {}; \
	(void)sizeof(compile_time_checker<expr>(ERROR_##msg{})); \
}

}

BOOST_AUTO_TEST_CASE(test_compile_time_assertions) {
	TEST_MARKER();

	using namespace test_techniques_ns;

	STATIC_CHECK(1 + 1 == 2, WRONG_RESULT);
	// STATIC_CHECK(1 + 1 == 3, WRONG_RESULT);
}

// 2.2. PARTIAL TEMPLATE SPECIALIZATION

namespace test_techniques_ns {

template <class t, class u>
struct foo {
	void fun() {
		print("foo<t, u>");
	}
};

struct t_1 {};

struct t_2 {};

struct u_1 {};

struct u_2 {};
 
template <>
struct foo<t_1, u_1> {
	void fun() {
		print("foo<t_1, u_1>");
	}
};
 
template <class t>
struct foo<t, u_1> {
	void fun() {
		print("foo<t, u_1>");
	}
};

struct tt_a {};

struct tt_b {};

template <class tt>
struct t_3 {};

template <class tt>
struct foo<t_3<tt>, u_1> {
	void fun() {
		print("foo<t_3, u_1>");
	}
};

}

BOOST_AUTO_TEST_CASE(test_partial_template_specialization) {
	TEST_MARKER();

	using namespace test_techniques_ns;

	foo<t_1, u_1> f_11;
	f_11.fun();
	foo<t_1, u_2> f_12;
	f_12.fun();

	foo<t_2, u_1> f_21;
	f_21.fun();
	foo<t_2, u_2> f_22;
	f_22.fun();

	foo<t_3<tt_a>, u_1> f_3a1;
	f_3a1.fun();
	foo<t_3<tt_a>, u_2> f_3a2;
	f_3a2.fun();
	foo<t_3<tt_b>, u_1> f_3b1;
	f_3b1.fun();
	foo<t_3<tt_b>, u_2> f_3b2;
	f_3b2.fun();
}

// 2.3. LOCAL CLASSES

namespace test_techniques_ns {

struct adapter {
	virtual void fun() = 0;
};

template <class obj_t, class par_t>
adapter* make_adapter(const obj_t& obj, const par_t& arg) {
	class local : public adapter {
	public:
		local(const obj_t& obj, const par_t& arg) : _obj{obj}, _arg{arg} {}
		virtual void fun() {
			_obj.fun(_arg);
		}
	private:
		obj_t _obj;
		par_t _arg;
	};
	return new local(obj, arg);
}

struct foo_arg {
	int var;
};

struct foo_obj {
	void fun(foo_arg arg) {
		print(arg.var);
	}
};

}

BOOST_AUTO_TEST_CASE(test_local_classes) {
	TEST_MARKER();

	using namespace test_techniques_ns;

	foo_obj fo;
	foo_arg fa;
	fa.var = 1;
	adapter* f_adapter = make_adapter(fo, fa);
	f_adapter->fun();
	delete f_adapter;
}

// 2.4. MAPPING INTEGRAL CONSTANTS TO TYPES

namespace test_techniques_ns {
namespace test_mapping_integral_constants_to_types_ns {

// Technique

template <int v>
struct int2type {
	static constexpr int value = v;
};

// Example

class small_type {
public:
	void sfun() {
		print("small type");
	}
private:
	int var = 0;
};

class big_type {
public:
	void bfun() {
		print("big type");
	}
private:
	int var_1 = 0;
	int var_2 = 0;
};

template <class t>
class foo {
private:
	void fun(t obj, int2type<true>) {
		obj.sfun();
	}
	void fun(t obj, int2type<false>) {
		obj.bfun();
	}
public:
	void fun(t obj) {
		fun(obj, int2type<sizeof(t) == sizeof(int)>());
	}
};

}
}

BOOST_AUTO_TEST_CASE(test_mapping_integral_constants_to_types) {
	TEST_MARKER();

	using namespace test_techniques_ns::test_mapping_integral_constants_to_types_ns;

	small_type s;
	foo<small_type> sf;
	sf.fun(s);

	big_type b;
	foo<big_type> bf;
	bf.fun(b);
}

// 2.5. TYPE-TO-TYPE MAPPING

namespace test_techniques_ns {
namespace test_type_to_type_mapping_ns {

// Technique

template <typename t>
struct type2type {
	using original_type = t;
};

// Example

struct simple_1 {
	simple_1(int arg) {
		print("simple 1");
	}
};

struct simple_2 {
	simple_2(int arg) {
		print("simple 2");
	}
};

struct complicated {
	complicated(int arg_1, int arg_2) {
		print("complicated");
	}
};

template <class obj_t, class arg_t>
obj_t* create(const arg_t& arg, type2type<obj_t>) {
	return new obj_t(arg);	
}

template <class arg_t>
complicated* create(const arg_t& arg, type2type<complicated>) {
	return new complicated(arg, -1);	
}

}
}

BOOST_AUTO_TEST_CASE(test_type_to_type_mapping) {
	TEST_MARKER();

	using namespace test_techniques_ns::test_type_to_type_mapping_ns;

	simple_1* s_1 = create(1, type2type<simple_1>());
	simple_2* s_2 = create(1, type2type<simple_2>());
	complicated* c = create(1, type2type<complicated>());

	delete s_1;
	delete s_2;
	delete c;
}