#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include "test_util.h"

void print(std::string_view str) {
	std::cout << str << "\n";
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