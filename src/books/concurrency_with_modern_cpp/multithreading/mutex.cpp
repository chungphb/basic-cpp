#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include <utility>
#include <chrono>
#include <mutex>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(mutex_suite)

using namespace std::chrono_literals;

std::mutex coutMutex;

class Worker {
private:
	std::string name;
public:
	Worker(std::string name_) : name(name_) {}
	void operator()() {
		for (int i = 1; i <= 3; ++i) {
			std::this_thread::sleep_for(200ms);
			coutMutex.lock();
			std::cout << name << ": Work " << i << " done\n";
			coutMutex.unlock();
		}
	}
};

BOOST_AUTO_TEST_CASE(mutex_test) {
	TEST_MARKER();
	std::thread w1(Worker("A"));
	std::thread w2(Worker("\tB"));
	std::thread w3(Worker("\t\tC"));
	std::thread w4(Worker("\t\t\tD"));
	w1.join();
	w2.join();
	w3.join();
	w4.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()