#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(bridge_suite)

class Implementation {
public:
	virtual ~Implementation() = default;
	virtual std::string implOperation() const = 0;
};

class ConcreteImplementation1 : public Implementation {
public:
	std::string implOperation() const override {
		return "Implementation 1";
	}
};

class ConcreteImplementation2 : public Implementation {
public:
	std::string implOperation() const override {
		return "Implementation 2";
	}
};

class Abstraction {
protected:
	Implementation* implementation;
public:
	Abstraction(Implementation* impl) : implementation(impl) {}
	virtual ~Abstraction() = default;
	virtual std::string absOperation() const {
		return "Abstraction: " + implementation->implOperation();
	}
};

class ExtendedAbstraction : public Abstraction {
public:
	ExtendedAbstraction(Implementation* impl) : Abstraction(impl) {}
	std::string absOperation() const override {
		return "Extended Abstraction: " + implementation->implOperation();
	}
};

void clientRequest(const Abstraction& abstraction) {
	std::cout << abstraction.absOperation() << "\n";
}

BOOST_AUTO_TEST_CASE(bridge_test) {
	TEST_MARKER();
	
	Implementation* impl = new ConcreteImplementation1();
	Abstraction* abs = new Abstraction(impl);
	clientRequest(*abs);
	delete impl;
	delete abs;

	impl = new ConcreteImplementation2();
	abs = new ExtendedAbstraction(impl);
	clientRequest(*abs);
	delete impl;
	delete abs;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()