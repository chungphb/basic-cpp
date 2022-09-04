#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include <thread>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(strategized_lock_suite)

class Critical {
private:
	mutable std::mutex mutex;
	void implementation1() const {
		std::cout << "implementation1: " << std::this_thread::get_id() << "\n";
	}
	void implementation2() {
		std::cout << "implementation2: " << std::this_thread::get_id() << "\n";
	}
	void implementation3() {
		std::cout << "implementation3: " << std::this_thread::get_id() << "\n";
	}
public:
	void interface1() const {
		std::lock_guard<std::mutex> lockGuard(mutex);
		implementation1();
	}
	void interface2() {
		std::lock_guard<std::mutex> lockGuard(mutex);
		implementation2();
		implementation3();
		implementation1();
	}
};

BOOST_AUTO_TEST_CASE(strategized_lock_test) {
	TEST_MARKER();
	std::thread t1([] {
		const Critical crit;
		crit.interface1();
	});
	std::thread t2([] {
		Critical crit;
		crit.interface2();
		crit.interface1();
	});
	Critical crit;
	crit.interface1();
	crit.interface2();
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()