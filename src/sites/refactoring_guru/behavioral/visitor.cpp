#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <array>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(visitor_suite)

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
	virtual void visitA(const ConcreteComponentA* element) const = 0;
	virtual void visitB(const ConcreteComponentB* element) const = 0;
};

class Component {
public:
	virtual ~Component() = default;
	virtual void accept(Visitor* visitor) const = 0;
};

class ConcreteComponentA : public Component {
public:
	void accept(Visitor* visitor) const override {
		visitor->visitA(this);
	}
	std::string operationA() const {
		return "A";
	}
};

class ConcreteComponentB : public Component {
public:
	void accept(Visitor* visitor) const override {
		visitor->visitB(this);
	}
	std::string operationB() const {
		return "B";
	}
};

class ConcreteVisitor1 : public Visitor {
public:
	void visitA(const ConcreteComponentA* element) const override {
		std::cout << "Visitor 1: " << element->operationA() << "\n";
	}
	void visitB(const ConcreteComponentB* element) const override {
		std::cout << "Visitor 1: " << element->operationB() << "\n";
	}
};

class ConcreteVisitor2 : public Visitor {
public:
	void visitA(const ConcreteComponentA* element) const override {
		std::cout << "Visitor 2: " << element->operationA() << "\n";
	}
	void visitB(const ConcreteComponentB* element) const override {
		std::cout << "Visitor 2: " << element->operationB() << "\n";
	}
};

void clientRequest(std::array<const Component*, 2> components, Visitor* visitor) {
	for (const Component* component : components) {
		component->accept(visitor);
	}
}

BOOST_AUTO_TEST_CASE(visitor_test) {
	TEST_MARKER();
	std::array<const Component*, 2> components;
	components[0] = new ConcreteComponentA();
	components[1] = new ConcreteComponentB();
	ConcreteVisitor1* visitor1 = new ConcreteVisitor1();
	clientRequest(components, visitor1);
	ConcreteVisitor2* visitor2 = new ConcreteVisitor2();
	clientRequest(components, visitor2);
	for (const Component* component : components) {
		delete component;
	}
	delete visitor1;
	delete visitor2;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()