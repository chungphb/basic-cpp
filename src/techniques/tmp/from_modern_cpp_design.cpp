#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include "test_util.h"

namespace test_sample_ns {

template <typename t>
class sample {
public:
	sample(t v) : val{v} {}
	void fun() {
		std::cout << val << "\n";
	}
private:
	t val;
};

struct foo {
	int val;
	explicit foo(int v) : val{v} {}
	friend std::ostream& operator<<(std::ostream& os, const foo& f) {
		return os << "foo: " << f.val;
	}
};

}

BOOST_AUTO_TEST_CASE(test_sample) {
	TEST_MARKER();

	using namespace test_sample_ns;

	sample<int> s_1{1};
	s_1.fun();
	sample<std::string> s_2{"Hello world!"};
	s_2.fun();
	sample<foo> s_3{foo{1}};
	s_3.fun();
}