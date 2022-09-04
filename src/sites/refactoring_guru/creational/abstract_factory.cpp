#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(abstract_factory_suite)

class AbstractProductA {
public:
	virtual ~AbstractProductA() = default;
	virtual std::string functionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
	std::string functionA() const override {
		return "product A1: function A";
	}
};

class ConcreteProductA2 : public AbstractProductA {
public:
	std::string functionA() const override {
		return "product A2: function A";
	}
};

class AbstractProductB {
public:
	virtual ~AbstractProductB() = default;
	virtual std::string functionB() const = 0;
};

class ConcreteProductB1 : public AbstractProductB {
public:
	std::string functionB() const override {
		return "product B1: function B";
	}
};

class ConcreteProductB2 : public AbstractProductB {
public:
	std::string functionB() const override {
		return "product B2: function B";
	}
};

class AbstractFactory {
public:
	virtual AbstractProductA* createProductA() const = 0;
	virtual AbstractProductB* createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
	AbstractProductA* createProductA() const override {
		return new ConcreteProductA1();
	}
	AbstractProductB* createProductB() const override {
		return new ConcreteProductB1();
	}
};

class ConcreteFactory2 : public AbstractFactory {
public:
	AbstractProductA* createProductA() const override {
		return new ConcreteProductA2();
	}
	AbstractProductB* createProductB() const override {
		return new ConcreteProductB2();
	}
};

void clientRequest(const AbstractFactory& factory) {
	const AbstractProductA* productA = factory.createProductA();
	const AbstractProductB* productB = factory.createProductB();
	std::cout << productA->functionA() << "\n";
	std::cout << productB->functionB() << "\n";
	delete productA;
	delete productB;
}

BOOST_AUTO_TEST_CASE(abstract_factory_test) {
	TEST_MARKER();
	std::cout << "Family 1\n";
	ConcreteFactory1* factory1 = new ConcreteFactory1();
	clientRequest(*factory1);
	delete factory1;
	std::cout << "Family 2\n";
	ConcreteFactory2* factory2 = new ConcreteFactory2();
	clientRequest(*factory2);
	delete factory2;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()