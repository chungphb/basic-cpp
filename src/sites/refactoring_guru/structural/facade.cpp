#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(facade_suite)

class Subsystem1 {
public:
	std::string operationA() const {
		return "Subsytem 1: Ready!\n";
	}
	std::string operationB() const {
		return "Subsytem 1: Go!\n";
	}
};

class Subsystem2 {
public:
	std::string operationC() const {
		return "Subsytem 2: Ready!\n";
	}
	std::string operationD() const {
		return "Subsytem 2: Fire!\n";
	}
};

class Facade {
protected:
	Subsystem1* subsystem1;
	Subsystem2* subsystem2;
public:
	Facade(Subsystem1* s1 = nullptr, Subsystem2* s2 = nullptr) {
		subsystem1 = s1;
		subsystem2 = s2;
	}
	~Facade() {
		delete subsystem1;
		delete subsystem2;
	}
	std::string operation() {
		std::string res;
		res += subsystem1->operationA();
		res += subsystem2->operationC();
		res += subsystem1->operationB();
		res += subsystem2->operationD();
		return res;
	}
};

void clientRequest(Facade* facade) {
	std::cout << facade->operation() << "\n";
}

BOOST_AUTO_TEST_CASE(facade_test) {
	TEST_MARKER();
	Subsystem1* subsystem1 = new Subsystem1();
	Subsystem2* subsystem2 = new Subsystem2();
	Facade* facade = new Facade(subsystem1, subsystem2);
	clientRequest(facade);
	delete facade;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()