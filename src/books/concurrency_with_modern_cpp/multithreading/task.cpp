#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <mutex>
#include <chrono>
#include <future>
#include <random>
#include <deque>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

// ========================================
// ASYNC
// ========================================

BOOST_AUTO_TEST_SUITE(async_vs_thread_suite)

BOOST_AUTO_TEST_CASE(async_vs_thread_test) {
	TEST_MARKER();
	
	// Thread
	int res;
	std::thread t([&res] { res = 2000 + 11; });
	t.join();
	std::cout << "Res: " << res << "\n";

	// Async
	auto fut = std::async([] { return 2000 + 11; });
	std::cout << "Res: " << fut.get() << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(lazy_async_suite)

using namespace std::chrono_literals;

BOOST_AUTO_TEST_CASE(lazy_async_test) {
	TEST_MARKER();
	auto start = std::chrono::system_clock::now();
	auto asyncLazy = std::async(std::launch::deferred, [] {
		return std::chrono::system_clock::now();
	});
	auto asyncEager = std::async(std::launch::async, [] {
		return std::chrono::system_clock::now();
	});
	std::this_thread::sleep_for(1s);
	auto lazy = asyncLazy.get() - start;
	auto eager = asyncEager.get() - start;
	auto durationLazy = std::chrono::duration<double>(lazy).count();
	auto durationEager = std::chrono::duration<double>(eager).count();
	std::cout << "Lazy: " << durationLazy << "s\n";
	std::cout << "Eager: " << durationEager << "s\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(concurrent_calculation_suite)

static const int NUM = 400;

long long getDotProduct(std::vector<int>& v, std::vector<int>& w) {
	auto vSize = v.size();
	auto fut1 = std::async([&] {
		return std::inner_product(v.begin(), v.begin() + vSize / 4, w.begin(), 0LL);
	});
	auto fut2 = std::async([&] {
		return std::inner_product(v.begin() + vSize / 4, v.begin() + vSize / 2, w.begin() + vSize / 4, 0LL);
	});
	auto fut3 = std::async([&] {
		return std::inner_product(v.begin() + vSize / 2, v.begin() + 3 * vSize / 4, w.begin() + vSize / 2, 0LL);
	});
	auto fut4 = std::async([&] {
		return std::inner_product(v.begin() + 3 * vSize / 4, v.end(), w.begin() + 3 * vSize / 4, 0LL);
	});
	return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

BOOST_AUTO_TEST_CASE(concurrent_calculation_test) {
	TEST_MARKER();
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution<int> dist(0, 100);
	std::vector<int> v, w;
	for (int i = 0; i < NUM; ++i) {
		v.push_back(dist(engine));
		w.push_back(dist(engine));
	}
	std::cout << "Product: " << getDotProduct(v, w) << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

// ========================================
// PACKAGED TASK
// ========================================

BOOST_AUTO_TEST_SUITE(packaged_task_suite)

class SumUp {
public:
	int operator()(int begin, int end) {
		long long int sum(0);
		for (int i = begin; i < end; ++i) {
			sum += i;
		}
		return sum;
	}
};

BOOST_AUTO_TEST_CASE(packaged_task_test) {
	TEST_MARKER();
	SumUp sumUp1, sumUp2, sumUp3, sumUp4;
	std::packaged_task<int(int, int)> sumTask1(sumUp1);
	std::packaged_task<int(int, int)> sumTask2(sumUp2);
	std::packaged_task<int(int, int)> sumTask3(sumUp3);
	std::packaged_task<int(int, int)> sumTask4(sumUp4);
	std::future<int> sumResult1 = sumTask1.get_future();
	std::future<int> sumResult2 = sumTask2.get_future();
	std::future<int> sumResult3 = sumTask3.get_future();
	std::future<int> sumResult4 = sumTask4.get_future();
	std::deque<std::packaged_task<int(int, int)>> allTasks;
	allTasks.push_back(std::move(sumTask1));
	allTasks.push_back(std::move(sumTask2));
	allTasks.push_back(std::move(sumTask3));
	allTasks.push_back(std::move(sumTask4));
	int start(0), increment(2500), end = start + increment;
	while (!allTasks.empty()) {
		std::packaged_task<int(int, int)> sumTask = std::move(allTasks.front());
		allTasks.pop_front();
		std::thread sumThread(std::move(sumTask), start, end);
		start = end;
		end += increment;
		sumThread.detach();
	}
	auto sum = sumResult1.get() + sumResult2.get() + sumResult3.get() + sumResult4.get();
	std::cout << "Sum: " << sum << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(packaged_task_reuse_suite)

void calcProducts(std::packaged_task<int(int, int)>& task, const std::vector<std::pair<int, int>>& pairs) {
	for (auto& pair : pairs) {
		auto fut = task.get_future();
		task(pair.first, pair.second);
		std::cout << pair.first << " x " << pair.second << " = " << fut.get() << "\n";
		task.reset();
	}
}

BOOST_AUTO_TEST_CASE(packaged_task_reuse_test) {
	TEST_MARKER();
	std::vector<std::pair<int, int>> allPairs;
	allPairs.emplace_back(1, 2);
	allPairs.emplace_back(2, 3);
	allPairs.emplace_back(3, 4);
	allPairs.emplace_back(4, 5);
	std::packaged_task<int(int, int)> task([](int x, int y) {
		return x * y;
	});
	calcProducts(task, allPairs);
	std::thread t(calcProducts, std::ref(task), allPairs);
	t.join();
}

BOOST_AUTO_TEST_SUITE_END()

// ========================================
// PROMISE & FUTURE
// ========================================

BOOST_AUTO_TEST_SUITE(promise_future_suite)

void product(std::promise<int>&& intPromise, int a, int b) {
	intPromise.set_value(a * b);
}

struct Div {
	void operator()(std::promise<int>&& intPromise, int a, int b) const {
		intPromise.set_value(a / b);
	}
};

BOOST_AUTO_TEST_CASE(promise_future_test) {
	TEST_MARKER();
	int a = 20, b = 10;
	std::promise<int> prodPromise;
	std::promise<int> divPromise;
	std::future<int> prodFuture = prodPromise.get_future();
	std::future<int> divFuture = divPromise.get_future();
	std::thread prodThread(product, std::move(prodPromise), a, b);
	Div div;
	std::thread divThread(div, std::move(divPromise), a, b);
	std::cout << a << " x " << b << " = " << prodFuture.get() << "\n";
	std::cout << a << " x " << b << " = " << divFuture.get() << "\n";
	prodThread.join();
	divThread.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(wait_for_suite)

using namespace std::chrono_literals;

void getAnswer(std::promise<int>&& intProm) {
	std::this_thread::sleep_for(3s);
	intProm.set_value(25);
}

BOOST_AUTO_TEST_CASE(wait_for_test) {
	TEST_MARKER();
	std::promise<int> prom;
	auto fut = prom.get_future();
	std::thread thread(getAnswer, std::move(prom));
	std::future_status status{};
	do {
		status = fut.wait_for(0.2s);
		std::cout << "Do something else\n";
	} while (status != std::future_status::ready);
	std::cout << "The answer: " << fut.get() << "\n";
	thread.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(shared_future_suite)

std::mutex coutMutex;

struct Div {
	void operator()(std::promise<int>&& intProm, int a, int b) {
		intProm.set_value(a / b);
	}
};

struct Requestor {
	void operator()(std::shared_future<int> sharedFut) {
		std::lock_guard<std::mutex> coutGuard(coutMutex);
		std::cout << "Thread: " << std::this_thread::get_id() << "\n";
		std::cout << "20 / 10 = " << sharedFut.get() << "\n";
	}
};

BOOST_AUTO_TEST_CASE(shared_future_test) {
	TEST_MARKER();
	std::promise<int> divProm;
	std::shared_future<int> divResult = divProm.get_future();
	Div div;
	std::thread divThread(div, std::move(divProm), 20, 10);
	Requestor req;
	std::thread reqThread1(req, divResult);
	std::thread reqThread2(req, divResult);
	std::thread reqThread3(req, divResult);
	std::thread reqThread4(req, divResult);
	std::thread reqThread5(req, divResult);
	divThread.join();
	reqThread1.join();
	reqThread2.join();
	reqThread3.join();
	reqThread4.join();
	reqThread5.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(exception_suite)

struct Div {
	void operator()(std::promise<int>&& intProm, int a, int b) {
		try {
			if (b == 0) {
				std::string errMess = std::string("Illegal division by zero: ") + std::to_string(a) + " / " + std::to_string(b);
				throw std::runtime_error(errMess);
			}
			intProm.set_value(a / b);
		} catch (...) {
			intProm.set_exception(std::current_exception());
		}
	}
};

void executeDivision(int nom, int denom) {
	std::promise<int> divProm;
	std::future<int> divResult = divProm.get_future();
	Div div;
	std::thread divThread(div, std::move(divProm), nom, denom);
	try {
		std::cout << nom << " / " << denom << " = " << divResult.get() << "\n";
	} catch (std::runtime_error& err) {
		std::cout << err.what() << "\n";
	}
	divThread.join();
}

BOOST_AUTO_TEST_CASE(exception_test) {
	TEST_MARKER();
	executeDivision(20, 0);
	executeDivision(20, 10);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(promise_future_synchronise_suite)

void doTheWork() {
	std::cout << "Processing shared data.\n";
}

void waitForWork(std::future<void>&& fut) {
	std::cout << "Receiver: Waiting for work.\n";
	fut.wait();
	doTheWork();
	std::cout << "Work done.\n";
}

void setDataReady(std::promise<void>&& prom) {
	std::cout << "Sender: Data is ready.\n";
	prom.set_value();
}

BOOST_AUTO_TEST_CASE(promise_future_synchronise_test) {
	TEST_MARKER();
	std::promise<void> prom;
	std::future<void> fut = prom.get_future();
	std::thread t1(waitForWork, std::move(fut));
	std::thread t2(setDataReady, std::move(prom));
	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()