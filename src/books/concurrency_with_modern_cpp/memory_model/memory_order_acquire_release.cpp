#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <atomic>
#include <thread>
#include <vector>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(spinlock_acquire_release_suite)

class Spinlock {
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	Spinlock() {}

	void lock() {
		while (flag.test_and_set(std::memory_order_acquire));
	}

	void unlock() {
		flag.clear(std::memory_order_release);
	}
};

int counter = 0;
Spinlock spin;

void workOnResource() {
	spin.lock();
	++counter;
	spin.unlock();
}

BOOST_AUTO_TEST_CASE(spinlock_acquire_release_test) {
	TEST_MARKER();
	std::thread t1(workOnResource);
	std::thread t2(workOnResource);
	t1.join();
	t2.join();
	std::cout << counter << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(transitivity_acquire_release_suite)

std::vector<int> mySharedWork;
std::atomic<bool> dataProduced(false); 
std::atomic<bool> dataConsumed(false);

void dataProducer() {
	mySharedWork = { 1, 0, 3 };
	dataProduced.store(true, std::memory_order_release);
}

void delivery() {
	while (!dataProduced.load(std::memory_order_acquire));
	dataConsumed.store(true, std::memory_order_release);
}

void dataConsumer() {
	while (!dataConsumed.load(std::memory_order_acquire));
	mySharedWork[1] = 2;
}

BOOST_AUTO_TEST_CASE(transitivity_acquire_release_test) {
	TEST_MARKER();
	std::thread t1(dataProducer);
	std::thread t2(delivery);
	std::thread t3(dataConsumer);
	t1.join();
	t2.join();
	t3.join();
	for (auto val : mySharedWork) {
		std::cout << val << " ";
	}
	std::cout << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(release_sequence_acquire_release_suite)

std::atomic<int> atom(0);
int somethingShared(0);

using namespace std::chrono_literals;

void writeShared() {
	somethingShared = 2011;
	atom.store(2, std::memory_order_release);
}

void readShared() {
	// A second call to fetch_sub is a ready-modify-write operation without a memory_order_release tag.
	// This means the second call does not synchronize-with the first call and a data race may occur on sharedVariable.
	// However, the release sequence prevents this from happenning.
	while (!atom.fetch_sub(1, std::memory_order_acquire) > 0) {
		std::this_thread::sleep_for(100ms);
	}
	std::cout << "somethingShared: " << somethingShared << "\n";
}

BOOST_AUTO_TEST_CASE(release_sequence_acquire_release_test) {
	TEST_MARKER();
	std::thread t1(writeShared);
	std::thread t2(readShared);
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()