#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <random>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(monitor_object_suite)

template <typename T>
class Monitor {
private:
	mutable std::recursive_mutex mutex;
	mutable std::condition_variable_any condVar;

public:
	void lock() const {
		mutex.lock();
	}

	void unlock() const {
		mutex.unlock();
	}

	void notify_one() const noexcept {
		condVar.notify_one();
	}

	void wait() const {
		std::unique_lock<std::recursive_mutex> lock(mutex);
		condVar.wait(lock);
	}
};

template <typename T>
class ThreadSafeQueue : public Monitor<ThreadSafeQueue<T>> {
private:
	std::queue<T> queue;
	ThreadSafeQueue<T>& derived = static_cast<ThreadSafeQueue<T>&>(*this);

public:
	void add(T val) {
		derived.lock();
		queue.push(val);
		derived.unlock();
		derived.notify_one();
	}

	T get() {
		derived.lock();
		while (queue.empty()) {
			derived.wait();
		}
		auto val = queue.front();
		queue.pop();
		derived.unlock();
		return val;
	}
};

class Dice {
private:
	std::function<int()> rand = std::bind(std::uniform_int_distribution<>(1, 6), std::default_random_engine());

public:
	int operator()() {
		return rand();
	}
};

BOOST_AUTO_TEST_CASE(monitor_object_test) {
	TEST_MARKER();
	constexpr auto NUM = 100;
	ThreadSafeQueue<int> safeQueue;
	auto addLambda = [&safeQueue](int val) { safeQueue.add(val); };
	auto getLambda = [&safeQueue]() {
		std::cout << safeQueue.get() << ": " << std::this_thread::get_id() << ", ";
	};
	
	std::vector<std::thread> addThreads(NUM);
	Dice dice;
	for (auto& thread : addThreads) {
		thread = std::thread(addLambda, dice());
	}
	
	std::vector<std::thread> getThreads(NUM);
	for (auto& thread : getThreads) {
		thread = std::thread(getLambda);
	}

	for (auto& thread : addThreads) {
		thread.join();
	}
	
	for (auto& thread : getThreads) {
		thread.join();
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()