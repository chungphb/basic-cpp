#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(mediator_suite)

class BaseComponent;

class Mediator {
public:
	virtual void notify(BaseComponent* sender, std::string event) const = 0;
};

class BaseComponent {
protected:
	Mediator* mediator;
public:
	BaseComponent(Mediator* m = nullptr) : mediator(m) {}
	void setMediator(Mediator* m) {
		mediator = m;
	}
};

class Component1 : public BaseComponent {
public:
	void operationA() {
		std::cout << "Component 1: Operation A\n";
		mediator->notify(this, "A");
	}
	void operationB() {
		std::cout << "Component 1: Operation B\n";
		mediator->notify(this, "B");
	}
};

class Component2 : public BaseComponent {
public:
	void operationC() {
		std::cout << "Component 2: Operation C\n";
		mediator->notify(this, "C");
	}
	void operationD() {
		std::cout << "Component 2: Operation D\n";
		mediator->notify(this, "D");
	}
};

class ConcreteMediator : public Mediator {
private:
	Component1* component1;
	Component2* component2;
public:
	ConcreteMediator(Component1* c1, Component2* c2) : component1(c1), component2(c2) {
		component1->setMediator(this);
		component2->setMediator(this);
	}
	void notify(BaseComponent* sender, std::string event) const override {
		if (event == "A") {
			std::cout << "Mediator: React on A\n";
			component2->operationC();
		}
		if (event == "D") {
			std::cout << "Mediator: React on D\n";
			component1->operationB();
			component2->operationC();
		}
	}
};

void clientRequest() {
	Component1* component1 = new Component1();
	Component2* component2 = new Component2();
	ConcreteMediator* mediator = new ConcreteMediator(component1, component2);
	std::cout << "Client: Trigger operation A\n";
	component1->operationA();
	std::cout << "Client: Trigger operation D\n";
	component2->operationD();
	delete component1;
	delete component2;
	delete mediator;

}

BOOST_AUTO_TEST_CASE(mediator_test) {
	TEST_MARKER();
	clientRequest();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()