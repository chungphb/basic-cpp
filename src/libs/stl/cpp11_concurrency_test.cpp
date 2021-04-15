#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include "test_util.h"

// THREAD

BOOST_AUTO_TEST_SUITE(test_thread)

void task() {
	std::cout << "Hello from thread #" << std::this_thread::get_id() << std::endl;
}

BOOST_AUTO_TEST_CASE(test_starting_thread) {
	TEST_MARKER();
	std::thread thread{task};
	thread.join();
}

BOOST_AUTO_TEST_CASE(test_starting_multiple_threads) {
	TEST_MARKER();
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{task});
	}
	for (auto& thread : threads) {
		thread.join();
	}
}

BOOST_AUTO_TEST_CASE(test_starting_multiple_threads_with_lambdas) {
	TEST_MARKER();
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{[] {
			std::cout << "Hello from thread #" << std::this_thread::get_id() << std::endl;
		}});
	}
	for (auto& thread : threads) {
		thread.join();
	}
}

BOOST_AUTO_TEST_SUITE_END()

// MUTEX

BOOST_AUTO_TEST_SUITE(test_mutex)

BOOST_AUTO_TEST_CASE(test_protecting_shared_data_with_mutexes) {
	TEST_MARKER();

	struct foo {
	public:
		foo() : value{0} {}
		void increase() {
			mutex.lock();
			value++;
			mutex.unlock();
		}
	public:
		int value;
		std::mutex mutex;
	};

	foo f;
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{[&f] {
			const int NUM_INCREMENTS = 100;
			for (int i = 0; i < NUM_INCREMENTS; i++) {
				f.increase();
			}
		}});
	}
	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << f.value << std::endl;
}

BOOST_AUTO_TEST_CASE(test_managing_locks_with_lock_guards) {
	TEST_MARKER();

	struct foo {
	public:
		foo() : value{0} {}
		void increase() {
			value++;
		}
		void decrease() {
			if (value == 0) {
				throw std::runtime_error("Value cannot be negative");
			}
			value--;
		}
	public:
		int value;
	};

	struct concurrent_safe_foo {
	public:
		void increase() {
			std::lock_guard<std::mutex> guard{mutex};
			f.increase();
		}
		void decrease() {
			std::lock_guard<std::mutex> guard{mutex};
			f.decrease();
		}
		int value() {
			return f.value;
		}
	public:
		foo f;
		std::mutex mutex;
	};

	concurrent_safe_foo f;
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{[&f] {
			const int NUM_INCREMENTS = 100;
			for (int i = 0; i < NUM_INCREMENTS; i++) {
				f.increase();
			}
		}});
		threads.push_back(std::thread{[&f] {
			const int NUM_DECREMENTS = 100;
			for (int i = 0; i < NUM_DECREMENTS; i++) {
				try {
					f.decrease();
				} catch (std::runtime_error& err) {
					std::cout << "Error: " << err.what() << std::endl;
				}
				
			}
		}});
	}
	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << f.value() << std::endl;
}

BOOST_AUTO_TEST_CASE(test_recursive_locking) {
	TEST_MARKER();

	struct foo {
	public:
		foo() : value{0} {}
		void add(int v) {
			std::lock_guard<std::recursive_mutex> guard{mutex};
			value += v;
		}
		void add_and_print(int v) { // Create deadlock if using std::mutex
			std::lock_guard<std::recursive_mutex> guard{mutex};
			add(v);
			std::cout << value << std::endl;
		}
	public:
		int value;
		std::recursive_mutex mutex;
	};

	foo f;
	std::thread t{[&f] {
		f.add_and_print(4);
	}};
	t.join();
}

BOOST_AUTO_TEST_CASE(test_timed_locking) {
	TEST_MARKER();

	using namespace std::chrono_literals;

	std::timed_mutex mutex;
	auto task = [&mutex] {
		auto timeout = 40ms;
		if (mutex.try_lock_for(timeout)) {
			std::cout << "Start task (with mutex)" << std::endl;
			std::this_thread::sleep_for(100ms);
			std::cout << "End task (with mutex)" << std::endl;
		} else {
			std::cout << "Start task (without mutex)" << std::endl;
			std::this_thread::sleep_for(40ms);
			std::cout << "End task (without mutex)" << std::endl;
		}
	};

	std::thread t1{task};
	std::thread t2{task};
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_CASE(test_call_once) {
	TEST_MARKER();
	
	std::once_flag flag;
	auto task = [&flag] {
		std::call_once(flag, [] {
			std::cout << "Called once" << std::endl;
		});
		std::cout << "Called each time" << std::endl;
	};

	std::thread t1{task};
	std::thread t2{task};
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END()

// CONDITION VARIABLE

BOOST_AUTO_TEST_SUITE(test_condition_variable)

using namespace std::chrono_literals;

struct bounded_buffer {
public:
	bounded_buffer(int c) : capacity{c}, front{0}, rear{0}, size{0} {
		buffer = new int[capacity];
	}

	~bounded_buffer() {
		delete[] buffer;
	}

	void push(int value) {
		std::unique_lock<std::mutex> lock{mutex};
		not_full.wait(lock, [this] {
			return size != capacity;
		});
		buffer[rear] = value;
		rear = (rear + 1) % capacity;
		++size;
		lock.unlock();
		not_empty.notify_one();
	}

	int pop() {
		std::unique_lock<std::mutex> lock{mutex};
		not_empty.wait(lock, [this] {
			return size != 0;
		});
		auto result = buffer[front];
		front = (front + 1) % capacity;
		--size;
		lock.unlock();
		not_full.notify_one();
		return result;
	}

private:
	int* buffer;
	int capacity;
	int front;
	int rear;
	int size;
	std::mutex mutex;
	std::condition_variable not_full;
	std::condition_variable not_empty;
};

void producer(int id, bounded_buffer& buffer) {
	for (int i = 0; i < 10; i++) {
		buffer.push(i);
		printf("Producer %d: %d\n", id, i);
		std::this_thread::sleep_for(100ms);
	}
}

void consumer(int id, bounded_buffer& buffer) {
	for (int i = 0; i < 5; i++) {
		int value = buffer.pop();
		printf("Consumer %d: %d\n", id, value);
		std::this_thread::sleep_for(250ms);
	}
}

BOOST_AUTO_TEST_CASE(test_using_condition_variables) {
	TEST_MARKER();
	
	bounded_buffer buffer{15};
	std::thread p1{producer, 1, std::ref(buffer)};
	std::thread p2{producer, 2, std::ref(buffer)};
	std::thread c1{consumer, 1, std::ref(buffer)};
	std::thread c2{consumer, 2, std::ref(buffer)};
	std::thread c3{consumer, 3, std::ref(buffer)};
	p1.join();
	p2.join();
	c1.join();
	c2.join();
	c3.join();
}

BOOST_AUTO_TEST_SUITE_END()

// ATOMIC

BOOST_AUTO_TEST_SUITE(test_atomic_types)

BOOST_AUTO_TEST_CASE(test_using_atomic_type) {
	TEST_MARKER();

	struct foo {
	public:
		foo() : value{0} {}
		void increase() {
			value++;
		}
		void decrease() {
			value--;
		}
		int get() {
			return value.load();
		}
	public:
		std::atomic<int> value; // Perform better than std::mutex, especially on integral types
	};

	foo f;
	const int NUM_THREADS = 4;
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread{[&f] {
			const int NUM_INCREMENTS = 100;
			for (int i = 0; i < NUM_INCREMENTS; i++) {
				f.increase();
			}
		}});
		threads.push_back(std::thread{[&f] {
			const int NUM_DECREMENTS = 100;
			for (int i = 0; i < NUM_DECREMENTS; i++) {
				try {
					f.decrease();
				} catch (std::runtime_error& err) {
					std::cout << "Error: " << err.what() << std::endl;
				}
				
			}
		}});
	}
	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << f.get() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()