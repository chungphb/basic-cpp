#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include <utility>
#include <chrono>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(create_thread_suite)

void helloFunction() {
	std::cout << "Hello from a function.\n";
}

class HelloFunctionObject {
public:
	void operator()() {
		std::cout << "Hello from a function object.\n";
	}
};

BOOST_AUTO_TEST_CASE(create_thread_test) {
	TEST_MARKER();
	std::thread t1(helloFunction);
	HelloFunctionObject helloFunctionObject;
	std::thread t2(helloFunctionObject);
	std::thread t3([] {
		std::cout << "Hello from a lambda.\n";
	});
	t1.join();
	t2.join();
	t3.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(scoped_thread_suite)

class scoped_thread {
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
		if (!t.joinable()) {
			throw std::logic_error("No thread");
		}
	}
	~scoped_thread() {
		t.join();
	}
	scoped_thread(const scoped_thread&) = delete;
	scoped_thread& operator=(const scoped_thread&) = delete;
};

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(thread_arguments_suite)

using namespace std::chrono_literals;

class Sleeper {
private:
	int& i;
public:
	Sleeper(int& i_) : i(i_) {}
	void operator()(int k) {
		for (int j = 0; j <= 5; ++j) {
			std::this_thread::sleep_for(100ms);
			i += k;
		}
		std::cout << std::this_thread::get_id() << "\n";
	}
};

BOOST_AUTO_TEST_CASE(thread_arguments_test) {
	TEST_MARKER();
	int val = 1000;
	std::thread t(Sleeper(val), 5);
	t.join();
	std::cout << "val = " << val << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(thread_methods_suite)

BOOST_AUTO_TEST_CASE(thread_methods_test) {
	TEST_MARKER();
	std::cout << std::boolalpha << "\n";
	std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency() << "\n";
	std::thread t1([] {
		std::cout << "t1: " << std::this_thread::get_id() << "\n";
	});
	std::thread t2([] {
		std::cout << "t2: " << std::this_thread::get_id() << "\n";
	});
	std::cout << "From main: t1 " << t1.get_id() << "\n";
	std::cout << "From main: t2 " << t2.get_id() << "\n";
	std::swap(t1, t2);
	std::cout << "From main: t1 " << t1.get_id() << "\n";
	std::cout << "From main: t2 " << t2.get_id() << "\n";
	std::cout << "From main: main " << std::this_thread::get_id() << "\n";
	std::cout << "Is t1 joinable: " << t1.joinable() << "\n";
	t1.join();
	t2.join();
	std::cout << "Is t1 joinable: " << t1.joinable() << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()