#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(factory_method_suite)

class Product {
public:
	virtual ~Product() = default;
	virtual std::string function() const = 0;
};

class ConcreteProduct1 : public Product {
public:
	std::string function() const override {
		return "Product 1";
	}
};

class ConcreteProduct2 : public Product {
public:
	std::string function() const override {
		return "Product 2";
	}
};

class Creator {
public:
	virtual ~Creator() = default;
	virtual Product* factoryMethod() const = 0;
};

class ConcreteCreator1 : public Creator {
public:
	Product* factoryMethod() const override {
		return new ConcreteProduct1();
	}
};

class ConcreteCreator2 : public Creator {
public:
	Product* factoryMethod() const override {
		return new ConcreteProduct2();
	}
};

void clientRequest(const Creator& creator) {
	Product* product = creator.factoryMethod();
	std::string result = product->function();
	std::cout << result << "\n";
	delete product;
}

BOOST_AUTO_TEST_CASE(factory_method_test) {
	TEST_MARKER();
	Creator* creator1 = new ConcreteCreator1();
	clientRequest(*creator1);
	delete creator1;
	Creator* creator2 = new ConcreteCreator2();
	clientRequest(*creator2);
	delete creator2;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()