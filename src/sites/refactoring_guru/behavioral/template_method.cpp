#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(template_method_suite)

class AbstractClass {
protected:
	void baseOperation1() const {
		std::cout << "Abstract class: Base operation 1\n";
	}
	void baseOperation2() const {
		std::cout << "Abstract class: Base operation 2\n";
	}
	virtual void requiredOperation1() const = 0;
	virtual void requiredOperation2() const = 0;
	virtual void optionalOperation1() const {}
	virtual void optionalOperation2() const {}
public:
	void templateMethod() const {
		baseOperation1();
		requiredOperation1();
		optionalOperation1();
		baseOperation2();
		requiredOperation2();
		optionalOperation2();
	}
};

class ConcreteClass1 : public AbstractClass {
protected:
	void requiredOperation1() const override {
		std::cout << "Concrete class 1: Required operation 1\n";
	}
	void requiredOperation2() const override {
		std::cout << "Concrete class 1: Required operation 2\n";
	}
};

class ConcreteClass2 : public AbstractClass {
protected:
	void requiredOperation1() const override {
		std::cout << "Concrete class 2: Required operation 1\n";
	}
	void requiredOperation2() const override {
		std::cout << "Concrete class 2: Required operation 2\n";
	}
	void optionalOperation1() const override {
		std::cout << "Concrete class 2: Optional operation 1\n";
	}
};

void clientRequest(AbstractClass* clazz) {
	clazz->templateMethod();
}

BOOST_AUTO_TEST_CASE(template_method_test) {
	TEST_MARKER();
	ConcreteClass1* concreteClass1 = new ConcreteClass1();
	clientRequest(concreteClass1);
	ConcreteClass2* concreteClass2 = new ConcreteClass2();
	clientRequest(concreteClass2);
	delete concreteClass1;
	delete concreteClass2;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()