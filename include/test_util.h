#include <boost/test/framework.hpp>

struct TestMarker {
	TestMarker() {
		std::cout << "\033[1m\033[32m>>>>>>>> START TEST CASE: " << boost::unit_test::framework::current_test_case().p_name << "\033[0m\n";
	}
	~TestMarker() {
		std::cout << "\033[1m\033[31m>>>>>>>> FINISH TEST CASE: " << boost::unit_test::framework::current_test_case().p_name << "\033[0m\n\n";
	}
};
#define TEST_MARKER() TestMarker testMarker