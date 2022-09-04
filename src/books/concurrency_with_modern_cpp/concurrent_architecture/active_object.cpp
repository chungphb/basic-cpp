#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>
#include <deque>
#include <mutex>
#include <future>
#include <random>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(concurrency_with_modern_cpp)

BOOST_AUTO_TEST_SUITE(active_object_suite)

class IsPrime {
public:
	std::pair<bool, int> operator()(int i) {
		for (int j = 2; j * j <= i; ++j) {
			if (i % j == 0) {
				return std::make_pair(false, i);
			}
		}
		return std::make_pair(true, i);
	}
};

class ActiveObject {
private:
	std::deque<std::pair<std::packaged_task<std::pair<bool, int>(int)>, int>> activationList;
	std::mutex activationListMutex;

	std::pair<std::packaged_task<std::pair<bool, int>(int)>, int> dequeueTask() {
		std::lock_guard<std::mutex> lockGuard(activationListMutex);
		auto myTask = std::move(activationList.front());
		activationList.pop_front();
		return myTask;
	}

	bool isEmpty() {
		std::lock_guard<std::mutex> lockGuard(activationListMutex);
		bool empty = activationList.empty();
		return empty;
	}

public:
	std::future<std::pair<bool, int>> enqueueTask(int i) {
		IsPrime isPrime;
		std::packaged_task<std::pair<bool, int>(int)> task(isPrime);
		auto fut = task.get_future();
		auto pair = std::make_pair(std::move(task), i);
		{
			std::lock_guard<std::mutex> lockGuard(activationListMutex);
			activationList.push_back(std::move(pair));
		}
		return fut;
	}

	void run() {
		std::thread worker([this] {
			while (!isEmpty()) {
				auto myTask = dequeueTask();
				myTask.first(myTask.second);
			}
		});
		worker.join();
	}
};

std::vector<int> getRandNumbers(int number) {
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution<int> dist(1000000, 1000000000);
	std::vector<int> numbers;
	for (long long i = 0; i < number; ++i) {
		numbers.push_back(dist(engine));
	}
	return numbers;
}

std::future<std::vector<std::future<std::pair<bool, int>>>> getFutures(ActiveObject& activeObject, int numberPrimes) {
	return std::async([&activeObject, numberPrimes] {
		std::vector<std::future<std::pair<bool, int>>> futures;
		auto randNumbers = getRandNumbers(numberPrimes);
		for (auto numb : randNumbers) {
			futures.push_back(activeObject.enqueueTask(numb));
		}
		return futures;
	});
}

BOOST_AUTO_TEST_CASE(active_object_test) {
	TEST_MARKER();
	ActiveObject activeObject;
	auto client1 = getFutures(activeObject, 1996);
	auto client2 = getFutures(activeObject, 2022);
	auto futures1 = client1.get();
	auto futures2 = client2.get();
	futures1.insert(futures1.end(), std::make_move_iterator(futures2.begin()), std::make_move_iterator(futures2.end()));
	activeObject.run();
	std::vector<std::pair<bool, int>> futResults;
	futResults.reserve(futures1.size());
	for (auto& fut : futures1) {
		futResults.push_back(fut.get());
	}
	std::sort(futResults.begin(), futResults.end());
	auto it = std::find_if(futResults.begin(), futResults.end(), [](std::pair<bool, int> pair) {
		return pair.first;
	});
	std::cout << "Number primes: " << std::distance(it, futResults.end()) << "\n";
	std::cout << "Primes: \n";
	std::for_each(it, futResults.end(), [](auto pair) {
		std::cout << pair.second << " ";
	});
	std::cout << "\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()