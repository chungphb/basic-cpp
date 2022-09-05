#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(strategy_suite)

class Strategy {
public:
	virtual ~Strategy() = default;
	virtual std::string doAlgorithm(std::string_view data) const = 0;
};

class Context {
private:
	std::unique_ptr<Strategy> strategy;
public:
	explicit Context(std::unique_ptr<Strategy>&& s = {}) : strategy(std::move(s)) {}
	void setStrategy(std::unique_ptr<Strategy>&& s) {
		strategy = std::move(s);
	}
	void operation() const {
		if (strategy) {
			std::cout << "Context: Sort the data\n";
			std::string res = strategy->doAlgorithm("aecbd");
			std::cout << res << "\n";
		} else {
			std::cout << "Context: Strategy isn't set\n";
		}
	}
};

class ConcreteStrategyA : public Strategy {
public:
	std::string doAlgorithm(std::string_view data) const override {
		std::string res(data);
		std::sort(res.begin(), res.end());
		return res;
	}
};

class ConcreteStrategyB : public Strategy {
public:
	std::string doAlgorithm(std::string_view data) const override {
		std::string res(data);
		std::sort(res.begin(), res.end(), std::greater<>());
		return res;
	}
};

void clientRequest() {
	std::cout << "Client: Normal sorting\n";
	Context context(std::make_unique<ConcreteStrategyA>());
	context.operation();
	std::cout << "Client: Reverse sorting\n";
	context.setStrategy(std::make_unique<ConcreteStrategyB>());
	context.operation();
}

BOOST_AUTO_TEST_CASE(strategy_test) {
	TEST_MARKER();
	clientRequest();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()