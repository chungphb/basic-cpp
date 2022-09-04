#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(builder_suite)

class Product {
public:
	std::vector<std::string> parts;
	void listParts() const {
		std::cout << "Parts: ";
		for (int i = 0; i < parts.size(); ++i) {
			std::cout << parts[i];
			if (i != parts.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "\n";
	}
};

class Builder {
public:
public:
	virtual ~Builder() = default;
	virtual void buildPartA() const = 0;
	virtual void buildPartB() const = 0;
	virtual void buildPartC() const = 0;
};

class ConcreteBuilder : public Builder {
private:
	Product* product;
public:
	ConcreteBuilder() {
		reset();
	}

	~ConcreteBuilder() {
		delete product;
	}

	void reset() {
		product = new Product();
	}

	void buildPartA() const override {
		product->parts.push_back("Part A");
	}

	void buildPartB() const override {
		product->parts.push_back("Part B");
	}

	void buildPartC() const override {
		product->parts.push_back("Part C");
	}

	Product* getProduct() {
		Product* res = product;
		reset();
		return res;
	}
};

class Director {
private:
	Builder* builder;

public:
	void setBuilder(Builder* b) {
		builder = b;
	}

	void buildMinimalViableProduct() {
		builder->buildPartA();
	}

	void buildFullFeaturedProduct() {
		builder->buildPartA();
		builder->buildPartB();
		builder->buildPartC();
	}
};

void clientRequest(Director& director) {
	ConcreteBuilder* builder = new ConcreteBuilder();
	director.setBuilder(builder);

	std::cout << "Standard product\n";
	director.buildMinimalViableProduct();
	Product* product = builder->getProduct();
	product->listParts();
	delete product;

	std::cout << "Full featured product\n";
	director.buildFullFeaturedProduct();
	product = builder->getProduct();
	product->listParts();
	delete product;

	std::cout << "Custom product\n";
	builder->buildPartA();
	builder->buildPartC();
	product = builder->getProduct();
	product->listParts();
	delete product;

	delete builder;
}

BOOST_AUTO_TEST_CASE(builder_test) {
	TEST_MARKER();
	Director* director = new Director();
	clientRequest(*director);
	delete director;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()