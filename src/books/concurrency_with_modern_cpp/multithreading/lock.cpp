#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <thread>
#include <utility>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <map>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(lock_guard_suite)

std::mutex mutex;
int shared;

void increase(int n) {
	std::lock_guard<std::mutex> lockGuard(mutex);
	shared += n;
}

void decrease(int n) {
	std::lock_guard<std::mutex> lockGuard(mutex);
	shared -= n;
}

BOOST_AUTO_TEST_CASE(lock_guard_test) {
	TEST_MARKER();
	shared = 0;
	std::thread t1(increase, 4);
	std::thread t2(decrease, 4);
	t1.join();
	t2.join();
	std::cout << shared << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unique_lock_suite)

using namespace std::chrono_literals;

struct CriticalData {
	std::mutex mut;
};

void deadLock(CriticalData& c1, CriticalData& c2) {
	std::unique_lock<std::mutex> l1(c1.mut, std::defer_lock);
	std::this_thread::sleep_for(1ms);
	std::unique_lock<std::mutex> l2(c2.mut, std::defer_lock);
	std::lock(l1, l2);
}

BOOST_AUTO_TEST_CASE(unique_lock_test) {
	TEST_MARKER();
	CriticalData c1;
	CriticalData c2;
	std::thread t1(deadLock, std::ref(c1), std::ref(c2));
	std::thread t2(deadLock, std::ref(c2), std::ref(c1));
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(shared_lock_suite)

using namespace std::chrono_literals;

std::map<std::string, int> teleBook{
	{ "Dijkstra", 1972 },
	{ "Scott", 1976 },
	{ "Ritchie", 1983 }
};
std::shared_timed_mutex teleBookMutex;

void addToTeleBook(const std::string& name, int tele) {
	std::lock_guard<std::shared_timed_mutex> writerLock(teleBookMutex);
	std::cout << "Update " << name << "\n";
	std::this_thread::sleep_for(500ms);
	teleBook[name] = tele;
}

void printNumber(const std::string& name) {
	std::shared_lock<std::shared_timed_mutex> readerLock(teleBookMutex);
	auto it = teleBook.find(name);
	if (it != teleBook.end()) {
		std::cout << it->first << ": " << it->second << "\n";
	} else {
		std::cout << name << " not found!\n";
	}
}

BOOST_AUTO_TEST_CASE(shared_lock_test) {
	TEST_MARKER();

	std::thread r1([] { printNumber("Scott"); });
	std::thread r2([] { printNumber("Ritchie"); });
	std::thread w1([] { addToTeleBook("Scott", 1968); });
	std::thread r3([] { printNumber("Dijkstra"); });
	std::thread r4([] { printNumber("Scott"); });
	std::thread w2([] { addToTeleBook("Bjarne", 1965); });
	std::thread r5([] { printNumber("Scott"); });
	std::thread r6([] { printNumber("Ritchie"); });
	std::thread r7([] { printNumber("Dijkstra"); });
	std::thread r8([] { printNumber("Bjarne"); });

	r1.join();
	r2.join();
	r3.join();
	r4.join();
	r5.join();
	r6.join();
	r7.join();
	r8.join();
	w1.join();
	w2.join();

	std::cout << "\nTelephone book:\n";
	for (auto entry : teleBook) {
		std::cout << entry.first << ": " << entry.second << "\n";
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()