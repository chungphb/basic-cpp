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

// Note: Using type2type<t> instead of t itself will avoid constructing an arbitrarily complex object.

// 2.6. TYPE SELECTION

namespace test_techniques_ns {
namespace test_type_selection_ns {

// Technique

template <bool flag, typename t, typename u>
struct type_select {
	using result = t;
};

template <typename t, typename u>
struct type_select<false, t, u> {
	using result = u;
};

// Example

struct first {
	void fun() {
		print("first class");
	}
};

struct second {
	void fun() {
		print("second class");
	}
};

}
}

BOOST_AUTO_TEST_CASE(test_type_selection) {
	TEST_MARKER();

	using namespace test_techniques_ns::test_type_selection_ns;

	using value_t = type_select<true, first, second>::result;
	value_t val;
	val.fun();
}

// 2.7. DETECTING CONVERTIBILITY AND INHERITANCE

namespace test_techniques_ns {
namespace test_detecting_convertibility_and_inheritance_ns {

// Technique

template <typename t, typename u>
class type_conversion {
	using small_type = char;
	struct big_type { char dummy[2]; };
	static small_type test(const u&);
	static big_type test(...);
	static t make_t(); // use this function to create a t because t's default constructor might be private
public:
	static constexpr bool exists = sizeof(test(make_t())) == sizeof(small_type);
	static constexpr bool same_type = false;
};

template <typename t>
class type_conversion<t, t> {
public:
	static constexpr bool exists = true;
	static constexpr bool same_type = true;
};

#define SUPERSUB(t, u) \
	(type_conversion<const u*, const t*>::exists && \
	!type_conversion<const t*, const void*>::same_type)

#define SUPERSUB_STRICT(t, u) \
	(SUPERSUB(t, u) && \
	!type_conversion<const t*, const u*>::same_type)

// Example

struct base {};

struct first : public base {};

struct second {};

template <typename t, bool = SUPERSUB(base, t)>
struct foo {
	void fun() {
		print("Derived from base");
	}
};

template <typename t>
struct foo<t, false> {
	void fun() {
		print("Not derived from base");
	}
};

}
}

BOOST_AUTO_TEST_CASE(test_detecting_convertibility_and_inheritance) {
	TEST_MARKER();

	using namespace test_techniques_ns::test_detecting_convertibility_and_inheritance_ns;

	foo<first> f_1;
	f_1.fun();

	foo<second> f_2;
	f_2.fun();
}

// 2.7. TYPE TRAITS

namespace test_techniques_ns {
namespace test_type_traits_ns {

struct null_type {};

template <typename t>
class type_traits {
// Pointer traits
private:
	template <typename u>
	struct pointer_traits {
		static constexpr bool result = false;
		using pointee_type = null_type;
	};
	template <typename u>
	struct pointer_traits<u*> {
		static constexpr bool result = true;
		using pointee_type = u;
	};
public:
	static constexpr bool is_pointer = pointer_traits<t>::result;
	using pointee_type = typename pointer_traits<t>::pointee_type;

// Reference traits
private:
	template <typename u>
	struct reference_traits {
		static constexpr bool result = false;
		using referenced_type = u;
	};
	template <typename u>
	struct reference_traits<u&> {
		static constexpr bool result = true;
		using referenced_type = u;
	};
public:
	static constexpr bool is_reference = reference_traits<t>::result;
	using referenced_type = typename reference_traits<t>::referenced_type;

// Stripping qualifiers
private:
	template <typename u>
	struct remove_const {
		using result = u;
	};
	template <typename u>
	struct remove_const<const u> {
		using result = u;
	};
public:
	using non_const_type = typename remove_const<t>::result;
};

}
}

BOOST_AUTO_TEST_CASE(test_type_traits) {
	TEST_MARKER();

	using namespace test_techniques_ns::test_type_traits_ns;

	struct foo {
	public:
		void fun(int v) {
			val = v;
			print(val);
		}
	private:
		int val;
	};

	// Pointer traits
	{
		std::cout << "foo is a pointer type? " << std::boolalpha << type_traits<foo>::is_pointer << "\n"; 
		std::cout << "foo* is a pointer type? " << std::boolalpha << type_traits<foo*>::is_pointer << "\n"; 
		std::cout << "const foo* is a pointer type? " << std::boolalpha << type_traits<const foo*>::is_pointer << "\n";
		using pointee_t = typename type_traits<foo*>::pointee_type;
		pointee_t val;
		val.fun(1);
	}

	// Reference traits
	{
		std::cout << "foo is a reference type? " << std::boolalpha << type_traits<foo>::is_reference << "\n"; 
		std::cout << "foo& is a reference type? " << std::boolalpha << type_traits<foo&>::is_reference << "\n"; 
		std::cout << "const foo& is a reference type? " << std::boolalpha << type_traits<const foo&>::is_reference << "\n";
		using referenced_t = typename type_traits<foo&>::referenced_type;
		referenced_t val;
		val.fun(2);
	}

	// Stripping qualifiers
	{
		using non_const_t = type_traits<const foo>::non_const_type;
		non_const_t val;
		val.fun(3);
	}
}

// 3. TYPELISTS

#include <typeinfo>

namespace test_typelists_ns {

template <typename T>
constexpr auto type_name() noexcept {
	std::string_view name = "Error: unsupported compiler", prefix, suffix;
#ifdef __clang__
	name = __PRETTY_FUNCTION__;
	prefix = "auto type_name() [T = ";
	suffix = "]";
#elif defined(__GNUC__)
	name = __PRETTY_FUNCTION__;
	prefix = "constexpr auto type_name() [with T = ";
	suffix = "]";
#elif defined(_MSC_VER)
	name = __FUNCSIG__;
	prefix = "auto __cdecl type_name<";
	suffix = ">(void) noexcept";
#endif
	name.remove_prefix(prefix.size());
	name.remove_suffix(suffix.size());
	return name;
}

}

// 3.1. DEFINING TYPELISTS

namespace test_typelists_ns {

struct null_type {};

template <typename t, typename u>
struct typelist {
	using head = t;
	using tail = u;
};

#define TYPELIST_1(T1) typelist<T1, null_type>
#define TYPELIST_2(T1, T2) typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) typelist<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) typelist<T1, TYPELIST_4(T2, T3, T4, T5)>
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6)>

using char_types = typelist<char, typelist<signed char, typelist<unsigned char, null_type>>>;

}

// 3.2. CALCULATING LENGTH

namespace test_typelists_ns {
namespace tl {

template <typename tlist> struct length;

template <> struct length<null_type> {
	static constexpr int value = 0;
};

template <typename t, typename u> struct length<typelist<t, u>> {
	static constexpr int value = 1 + length<u>::value;
};

}
}

BOOST_AUTO_TEST_CASE(test_length) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	int len = tl::length<char_types>::value;
	print("Length: " + std::to_string(len));
}

// 3.3. INDEXED ACCESS

namespace test_typelists_ns {
namespace tl {

template <typename tlist, unsigned int index> struct type_at;

template <typename head, typename tail>
struct type_at<typelist<head, tail>, 0> {
	using result = head;
};

template <typename head, typename tail, unsigned int index>
struct type_at<typelist<head, tail>, index> {
	using result = typename type_at<tail, index - 1>::result;
};

}
}

BOOST_AUTO_TEST_CASE(test_type_at) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	print("List of char types:");
	print(typeid(tl::type_at<char_types, 0>::result).name());
	print(typeid(tl::type_at<char_types, 1>::result).name());
	print(typeid(tl::type_at<char_types, 2>::result).name());
	// print(typeid(tl::type_at<char_types, 3>::result).name());
	// print(typeid(tl::type_at<char_types, -1>::result).name());
}

// 3.4. SEARCHING TYPELISTS

namespace test_typelists_ns {
namespace tl {

template <typename tlist, typename t> struct index_of;

template <typename t>
struct index_of<null_type, t> {
	static constexpr int result = -1;
};

template <typename t, typename tail>
struct index_of<typelist<t, tail>, t> {
	static constexpr int result = 0;
};

template <typename head, typename tail, typename t>
struct index_of<typelist<head, tail>, t> {
private:
	static constexpr int tmp = index_of<tail, t>::result;
public:
	static constexpr int result = tmp == -1 ? -1 : 1 + tmp;
};

}
}

BOOST_AUTO_TEST_CASE(test_index_of) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	int id = tl::index_of<char_types, char>::result;
	print("Index of char: " + std::to_string(id));

	id = tl::index_of<char_types, signed char>::result;
	print("Index of signed char: " + std::to_string(id));

	id = tl::index_of<char_types, unsigned char>::result;
	print("Index of unsigned char: " + std::to_string(id));

	id = tl::index_of<char_types, int>::result;
	print("Index of int: " + std::to_string(id));
}


// 3.5. APPENDING TO TYPELISTS

namespace test_typelists_ns {
namespace tl {

template <typename tlist, typename t> struct append;

template <>
struct append<null_type, null_type> {
	using result = null_type;
};

template <typename t>
struct append<null_type, t> {
	using result = TYPELIST_1(t);
};

template <typename head, typename tail>
struct append<null_type, typelist<head, tail>> {
	using result = typelist<head, tail>;
};

template <typename head, typename tail, typename t>
struct append<typelist<head, tail>, t> {
	using result = typelist<head, typename append<tail, t>::result>;
};

}
}

BOOST_AUTO_TEST_CASE(test_append) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	using signed_integrals = TYPELIST_4(signed char, short int, int, long int);

	print("BEFORE APPENDING:");
	print(typeid(tl::type_at<signed_integrals, 0>::result).name());
	print(typeid(tl::type_at<signed_integrals, 1>::result).name());
	print(typeid(tl::type_at<signed_integrals, 2>::result).name());
	print(typeid(tl::type_at<signed_integrals, 3>::result).name());

	using signed_types = typename tl::append<signed_integrals, TYPELIST_3(float, double, long double)>::result;

	print("AFTER APPENDING:");
	print(typeid(tl::type_at<signed_types, 0>::result).name());
	print(typeid(tl::type_at<signed_types, 1>::result).name());
	print(typeid(tl::type_at<signed_types, 2>::result).name());
	print(typeid(tl::type_at<signed_types, 3>::result).name());
	print(typeid(tl::type_at<signed_types, 4>::result).name());
	print(typeid(tl::type_at<signed_types, 5>::result).name());
	print(typeid(tl::type_at<signed_types, 6>::result).name());
}

// 3.6. ERASING A TYPE FROM A TYPELIST

namespace test_typelists_ns {
namespace tl {

template <typename tlist, typename t> struct erase;

template <typename t>
struct erase<null_type, t> {
	using result = null_type;
};

template <typename t, typename tail>
struct erase<typelist<t, tail>, t> {
	using result = tail;
};

template <typename head, typename tail, typename t>
struct erase<typelist<head, tail>, t> {
	using result = typelist<head, typename erase<tail, t>::result>;
};

}
}

BOOST_AUTO_TEST_CASE(test_erase) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	struct foo_1 {};
	struct foo_2 {};
	struct foo_3 {};
	using foo_types = TYPELIST_3(foo_1, foo_2, foo_3);

	print("BEFORE ERASING:");
	print(typeid(tl::type_at<foo_types, 0>::result).name());
	print(typeid(tl::type_at<foo_types, 1>::result).name());
	print(typeid(tl::type_at<foo_types, 2>::result).name());

	using some_foo_types = typename tl::erase<foo_types, foo_2>::result;

	print("AFTER ERASING:");
	print(typeid(tl::type_at<some_foo_types, 0>::result).name());
	print(typeid(tl::type_at<some_foo_types, 1>::result).name());
}

namespace test_typelists_ns {
namespace tl {

template <typename tlist, typename t> struct erase_all;

template <typename t>
struct erase_all<null_type, t> {
	using result = null_type;
};

template <typename t, typename tail>
struct erase_all<typelist<t, tail>, t> {
	using result = typename erase_all<tail, t>::result;
};

template <typename head, typename tail, typename t>
struct erase_all<typelist<head, tail>, t> {
	using result = typelist<head, typename erase_all<tail, t>::result>;
};

}
}

BOOST_AUTO_TEST_CASE(test_erase_all) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	struct foo_1 {};
	struct foo_2 {};
	struct foo_3 {};
	using foo_types = TYPELIST_4(foo_1, foo_2, foo_3, foo_1);

	print("BEFORE ERASING ALL:");
	print(typeid(tl::type_at<foo_types, 0>::result).name());
	print(typeid(tl::type_at<foo_types, 1>::result).name());
	print(typeid(tl::type_at<foo_types, 2>::result).name());
	print(typeid(tl::type_at<foo_types, 3>::result).name());

	using some_foo_types = typename tl::erase_all<foo_types, foo_1>::result;

	print("AFTER ERASING ALL:");
	print(typeid(tl::type_at<some_foo_types, 0>::result).name());
	print(typeid(tl::type_at<some_foo_types, 1>::result).name());
}

// 3.7. ERASING DUPLICATES

namespace test_typelists_ns {
namespace tl {

template <typename tlist> struct unique;

template <>
struct unique<null_type> {
	using result = null_type;
};

template <typename head, typename tail>
struct unique<typelist<head, tail>> {
private:
	using tmp_1 = typename unique<tail>::result;
	using tmp_2 = typename erase<tmp_1, head>::result;
public:
	using result = typelist<head, tmp_2>;
};

}
}

BOOST_AUTO_TEST_CASE(test_unique) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	struct foo_1 {};
	struct foo_2 {};
	struct foo_3 {};
	using foo_types = TYPELIST_6(foo_1, foo_2, foo_3, foo_1, foo_2, foo_1);

	print("BEFORE ERASING DUPLICATES:");
	print(typeid(tl::type_at<foo_types, 0>::result).name());
	print(typeid(tl::type_at<foo_types, 1>::result).name());
	print(typeid(tl::type_at<foo_types, 2>::result).name());
	print(typeid(tl::type_at<foo_types, 3>::result).name());
	print(typeid(tl::type_at<foo_types, 4>::result).name());
	print(typeid(tl::type_at<foo_types, 5>::result).name());

	using unique_foo_types = typename tl::unique<foo_types>::result;

	print("AFTER ERASING DUPLICATES:");
	print(typeid(tl::type_at<unique_foo_types, 0>::result).name());
	print(typeid(tl::type_at<unique_foo_types, 1>::result).name());
	print(typeid(tl::type_at<unique_foo_types, 2>::result).name());
}

// 3.8. REPLACING AN ELEMENT IN A TYPELIST

namespace test_typelists_ns {
namespace tl {

template <typename tlist, typename t, typename u> struct replace;

template <typename t, typename u>
struct replace<null_type, t, u> {
	using result = null_type;
};

template <typename t, typename tail, typename u>
struct replace<typelist<t, tail>, t, u> {
	using result = typelist<u, tail>;
};

template <typename head, typename tail, typename t, typename u>
struct replace<typelist<head, tail>, t, u> {
	using result = typelist<head, typename replace<tail, t, u>::result>;
};

}
}

BOOST_AUTO_TEST_CASE(test_replace) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	struct foo_1 {};
	struct foo_2 {};
	struct foo_3 {};
	struct not_foo {};
	struct foo_4 {};
	using some_types = TYPELIST_4(foo_1, foo_2, foo_3, not_foo);

	print("BEFORE REPLACING:");
	print(typeid(tl::type_at<some_types, 0>::result).name());
	print(typeid(tl::type_at<some_types, 1>::result).name());
	print(typeid(tl::type_at<some_types, 2>::result).name());
	print(typeid(tl::type_at<some_types, 3>::result).name());

	using foo_types = typename tl::replace<some_types, not_foo, foo_4>::result;

	print("AFTER REPLACING:");
	print(typeid(tl::type_at<foo_types, 0>::result).name());
	print(typeid(tl::type_at<foo_types, 1>::result).name());
	print(typeid(tl::type_at<foo_types, 2>::result).name());
	print(typeid(tl::type_at<foo_types, 3>::result).name());
}

// 3.9. PARTIALLY ORDERING TYPELISTS

namespace test_typelists_ns {
namespace tl {

using namespace test_techniques_ns::test_detecting_convertibility_and_inheritance_ns;
using namespace test_techniques_ns::test_type_selection_ns;

template <typename tlist, typename t> struct most_derived {};

template <typename t>
struct most_derived<null_type, t> {
	using result = t;
};

template <typename head, typename tail, typename t>
struct most_derived<typelist<head, tail>, t> {
private:
	using candidate = typename most_derived<tail, t>::result;
public:
	using result = typename type_select<SUPERSUB(head, candidate), candidate, head>::result;
};


template <typename tlist> struct derived_to_front;

template <>
struct derived_to_front<null_type> {
	using result = null_type;
};

template <typename head, typename tail>
struct derived_to_front<typelist<head, tail>> {
private:
	using the_most_derived = typename most_derived<tail, head>::result;
	using tmp = typename replace<tail, the_most_derived, head>::result;
	using new_tail = typename derived_to_front<tmp>::result;
public:
	using result = typelist<the_most_derived, new_tail>;
};

}
}

BOOST_AUTO_TEST_CASE(test_sort) {
	TEST_MARKER();

	using namespace test_typelists_ns;

	struct foo_1 {};
	struct foo_2 : public foo_1 {};
	struct foo_3 : public foo_1 {};
	struct foo_4 : public foo_2 {};
	using foo_types = TYPELIST_4(foo_1, foo_2, foo_3, foo_4);

	print("BEFORE SORTING:");
	print(typeid(tl::type_at<foo_types, 0>::result).name());
	print(typeid(tl::type_at<foo_types, 1>::result).name());
	print(typeid(tl::type_at<foo_types, 2>::result).name());
	print(typeid(tl::type_at<foo_types, 3>::result).name());

	using sorted_foo_types = typename tl::derived_to_front<foo_types>::result;

	print("AFTER SORTING:");
	print(typeid(tl::type_at<sorted_foo_types, 0>::result).name());
	print(typeid(tl::type_at<sorted_foo_types, 1>::result).name());
	print(typeid(tl::type_at<sorted_foo_types, 2>::result).name());
	print(typeid(tl::type_at<sorted_foo_types, 3>::result).name());
}

// 3.10. CLASS GENERATION WITH TYPELISTS

namespace test_typelists_ns {
namespace tl {

// SCATTER HIERARCHY

template <typename tlist, template <typename> class unit> struct gen_scatter_hierarchy;

template <template <typename> class unit>
struct gen_scatter_hierarchy<null_type, unit> {};

template <typename atomic_type, template <typename> class unit>
struct gen_scatter_hierarchy : public unit<atomic_type> {
	using left_base = unit<atomic_type>;
};

template <typename head, typename tail, template <typename> class unit>
struct gen_scatter_hierarchy<typelist<head, tail>, unit> : public gen_scatter_hierarchy<head, unit>, public gen_scatter_hierarchy<tail, unit> {
	using tlist = typelist<head, tail>;
	using left_base = gen_scatter_hierarchy<head, unit>;
	using right_base = gen_scatter_hierarchy<tail, unit>;
};

// LINEAR HIERARCHY

struct empty_type {};

template <
	typename tlist,
	template <typename atomic_type, typename base> class unit,
	typename root = empty_type
>
struct gen_linear_hierarchy;

template <
	typename atomic_type,
	template <typename, typename> class unit,
	typename root
>
struct gen_linear_hierarchy<TYPELIST_1(atomic_type), unit, root> : public unit<atomic_type, root> {};

template <
	typename head,
	typename tail,
	template <typename, typename> class unit,
	typename root
>
struct gen_linear_hierarchy<typelist<head, tail>, unit, root> : public unit<head, gen_linear_hierarchy<tail, unit, root>> {};

}

namespace test_generate_classes_ns {

struct foo_1 {
	void fun_1() {
		print("foo 1");
	}
};

struct foo_2 {
	void fun_2() {
		print("foo 2");
	}
};

struct foo_3 {
	void fun_3() {
		print("foo 3");
	}
};

template <typename t>
struct holder {
	t _val;
};

template <typename t, typename base>
struct another_holder : base {
	void fun(t& val) {
		val.fun();
	}
};

}
}

BOOST_AUTO_TEST_CASE(test_generate_classes) {
	TEST_MARKER();

	using namespace test_typelists_ns;
	using namespace test_typelists_ns::test_generate_classes_ns;

	using foos = tl::gen_scatter_hierarchy<TYPELIST_3(foo_1, foo_2, foo_3), holder>;
	foos f;
	foo_1 f_1 = (static_cast<holder<foo_1>&>(f))._val;
	f_1.fun_1();
	foo_2 f_2 = (static_cast<holder<foo_2>&>(f))._val;
	f_2.fun_2();
	foo_3 f_3 = (static_cast<holder<foo_3>&>(f))._val;
	f_3.fun_3();

	using another_foos = tl::gen_linear_hierarchy<TYPELIST_3(foo_1, foo_2, foo_3), another_holder>;
}