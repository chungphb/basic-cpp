#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include <atomic>
#include <random>
#include <future>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

constexpr long long size = 100000000;
constexpr long long fir = 25000000;
constexpr long long sec = 50000000;
constexpr long long thi = 75000000;
constexpr long long fou = 100000000;

BOOST_AUTO_TEST_SUITE(lock_guard_suite)

std::mutex mutex;

void sumUp(unsigned long long& sum, const std::vector<int>& val, unsigned long long begin, unsigned long long end) {
	unsigned long long tmpSum = 0;
	for (auto i = begin; i < end; ++i) {
		tmpSum += val[i];
	}
	std::lock_guard<std::mutex> lockGuard(mutex);
	sum += tmpSum;
}

BOOST_AUTO_TEST_CASE(lock_guard_test) {
	TEST_MARKER();
	std::vector<int> randValues;
	randValues.reserve(size);
	std::mt19937 engine;
	std::uniform_int_distribution<int> dist(1, 10);
	for (long long i = 0; i < size; ++i) {
		randValues.push_back(dist(engine));
	}
	unsigned long long sum = 0;
	const auto start = std::chrono::system_clock::now();
	std::thread t1(sumUp, std::ref(sum), std::ref(randValues), 0, fir);
	std::thread t2(sumUp, std::ref(sum), std::ref(randValues), fir, sec);
	std::thread t3(sumUp, std::ref(sum), std::ref(randValues), sec, thi);
	std::thread t4(sumUp, std::ref(sum), std::ref(randValues), thi, fou);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	const std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Sum: " << sum << "\n";
	std::cout << "Time: " << dur.count() << "s\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(atomic_sequential_consistency_suite)

void sumUp(std::atomic<unsigned long long>& sum, const std::vector<int>& val, unsigned long long begin, unsigned long long end) {
	unsigned long long tmpSum = 0;
	for (auto i = begin; i < end; ++i) {
		tmpSum += val[i];
	}
	sum += tmpSum;
}

BOOST_AUTO_TEST_CASE(atomic_sequential_consistency_test) {
	TEST_MARKER();
	std::vector<int> randValues;
	randValues.reserve(size);
	std::mt19937 engine;
	std::uniform_int_distribution<int> dist(1, 10);
	for (long long i = 0; i < size; ++i) {
		randValues.push_back(dist(engine));
	}
	std::atomic<unsigned long long> sum = 0;
	const auto start = std::chrono::system_clock::now();
	std::thread t1(sumUp, std::ref(sum), std::ref(randValues), 0, fir);
	std::thread t2(sumUp, std::ref(sum), std::ref(randValues), fir, sec);
	std::thread t3(sumUp, std::ref(sum), std::ref(randValues), sec, thi);
	std::thread t4(sumUp, std::ref(sum), std::ref(randValues), thi, fou);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	const std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Sum: " << sum << "\n";
	std::cout << "Time: " << dur.count() << "s\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(atomic_relaxed_suite)

void sumUp(std::atomic<unsigned long long>& sum, const std::vector<int>& val, unsigned long long begin, unsigned long long end) {
	unsigned long long tmpSum = 0;
	for (auto i = begin; i < end; ++i) {
		tmpSum += val[i];
	}
	sum.fetch_add(tmpSum, std::memory_order_relaxed);
}

BOOST_AUTO_TEST_CASE(atomic_relaxed_test) {
	TEST_MARKER();
	std::vector<int> randValues;
	randValues.reserve(size);
	std::mt19937 engine;
	std::uniform_int_distribution<int> dist(1, 10);
	for (long long i = 0; i < size; ++i) {
		randValues.push_back(dist(engine));
	}
	std::atomic<unsigned long long> sum = 0;
	const auto start = std::chrono::system_clock::now();
	std::thread t1(sumUp, std::ref(sum), std::ref(randValues), 0, fir);
	std::thread t2(sumUp, std::ref(sum), std::ref(randValues), fir, sec);
	std::thread t3(sumUp, std::ref(sum), std::ref(randValues), sec, thi);
	std::thread t4(sumUp, std::ref(sum), std::ref(randValues), thi, fou);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	const std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Sum: " << sum << "\n";
	std::cout << "Time: " << dur.count() << "s\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(thread_local_suite)

thread_local unsigned long long tmpSum = 0;

void sumUp(std::atomic<unsigned long long>& sum, const std::vector<int>& val, unsigned long long begin, unsigned long long end) {
	for (auto i = begin; i < end; ++i) {
		tmpSum += val[i];
	}
	sum.fetch_add(tmpSum, std::memory_order_relaxed);
}

BOOST_AUTO_TEST_CASE(thread_local_test) {
	TEST_MARKER();
	std::vector<int> randValues;
	randValues.reserve(size);
	std::mt19937 engine;
	std::uniform_int_distribution<int> dist(1, 10);
	for (long long i = 0; i < size; ++i) {
		randValues.push_back(dist(engine));
	}
	std::atomic<unsigned long long> sum = 0;
	const auto start = std::chrono::system_clock::now();
	std::thread t1(sumUp, std::ref(sum), std::ref(randValues), 0, fir);
	std::thread t2(sumUp, std::ref(sum), std::ref(randValues), fir, sec);
	std::thread t3(sumUp, std::ref(sum), std::ref(randValues), sec, thi);
	std::thread t4(sumUp, std::ref(sum), std::ref(randValues), thi, fou);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	const std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Sum: " << sum << "\n";
	std::cout << "Time: " << dur.count() << "s\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(task_suite)

void sumUp(std::promise<unsigned long long>&& prom, const std::vector<int>& val, unsigned long long begin, unsigned long long end) {
	unsigned long long sum = 0;
	for (auto i = begin; i < end; ++i) {
		sum += val[i];
	}
	prom.set_value(sum);
}

BOOST_AUTO_TEST_CASE(task_test) {
	TEST_MARKER();
	std::vector<int> randValues;
	randValues.reserve(size);
	std::mt19937 engine;
	std::uniform_int_distribution<int> dist(1, 10);
	for (long long i = 0; i < size; ++i) {
		randValues.push_back(dist(engine));
	}
	std::promise<unsigned long long> prom1;
	std::promise<unsigned long long> prom2;
	std::promise<unsigned long long> prom3;
	std::promise<unsigned long long> prom4;
	auto fut1 = prom1.get_future();
	auto fut2 = prom2.get_future();
	auto fut3 = prom3.get_future();
	auto fut4 = prom4.get_future();
	const auto start = std::chrono::system_clock::now();
	std::thread t1(sumUp, std::move(prom1), std::ref(randValues), 0, fir);
	std::thread t2(sumUp, std::move(prom2), std::ref(randValues), fir, sec);
	std::thread t3(sumUp, std::move(prom3), std::ref(randValues), sec, thi);
	std::thread t4(sumUp, std::move(prom4), std::ref(randValues), thi, fou);
	auto sum = fut1.get() + fut2.get() + fut3.get() + fut4.get();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	const std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "Sum: " << sum << "\n";
	std::cout << "Time: " << dur.count() << "s\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()