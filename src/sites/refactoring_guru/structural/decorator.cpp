#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(decorator_suite)

class Component {
public:
	virtual ~Component() = default;
	virtual std::string operation() const = 0;
};

class ConcreteComponent : public Component {
public:
	std::string operation() const override {
		return "Concrete Component";
	}
};

class Decorator : public Component {
protected:
	Component* component;
public:
	Decorator(Component* c) : component(c) {}
	std::string operation() const override {
		return component->operation();
	}
};

class ConcreteDecorator1 : public Decorator {
public:
	ConcreteDecorator1(Component* component) : Decorator(component) {}
	std::string operation() const override {
		return "Concrete Decorator 1 (" + Decorator::operation() + ")";
	}
};

class ConcreteDecorator2 : public Decorator {
public:
	ConcreteDecorator2(Component* component) : Decorator(component) {}
	std::string operation() const override {
		return "Concrete Decorator 2 (" + Decorator::operation() + ")";
	}
};

void clientRequest(Component* component) {
	std::cout << "Result: " << component->operation() << "\n";
}

BOOST_AUTO_TEST_CASE(decorator_test) {
	TEST_MARKER();

	std::cout << "Simple component\n";
	Component* component = new ConcreteComponent();
	clientRequest(component);

	std::cout << "Decorated component\n";
	Component* decorator1 = new ConcreteDecorator1(component);
	Component* decorator2 = new ConcreteDecorator2(decorator1);
	clientRequest(decorator2);
	
	delete component;
	delete decorator1;
	delete decorator2;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
