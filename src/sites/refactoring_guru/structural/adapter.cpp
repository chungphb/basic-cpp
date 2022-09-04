#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <algorithm>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(adapter_suite)

class Adaptee {
public:
	std::string specificRequest() const {
		return "eetpadA";
	}
};

class Target {
public:
	virtual ~Target() = default;
	virtual std::string request() const {
		return "Target";
	}
};

class Adapter : public Target {
private:
	Adaptee* adaptee;
public:
	Adapter(Adaptee* a) : adaptee(a) {}
	std::string request() const override {
		std::string specialRequest = adaptee->specificRequest();
		std::reverse(specialRequest.begin(), specialRequest.end());
		return "Adapter: (TRANSLATED) " + specialRequest;
	}
};

void clientRequest(const Target* target) {
	std::cout << target->request() << "\n";
}

BOOST_AUTO_TEST_CASE(adapter_test) {
	TEST_MARKER();

	std::cout << "Target object: ";
	Target* target = new Target();
	clientRequest(target);

	std::cout << "Adaptee object: ";
	Adaptee* adaptee = new Adaptee();
	std::cout << adaptee->specificRequest() << "\n";
	
	std::cout << "Use Adapter to work with Adaptee\n";
	Adapter* adapter = new Adapter(adaptee);
	clientRequest(adapter);

	delete target;
	delete adaptee;
	delete adapter;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()