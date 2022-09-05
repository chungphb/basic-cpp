#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(state_suite)

class Context;

class State {
protected:
	Context* context;
public:
	virtual ~State() = default;
	void setContext(Context* c) {
		context = c;
	}
	virtual void handle1() = 0;
	virtual void handle2() = 0;
};

class Context {
private:
	State* state;
public:
	Context(State* s) : state(nullptr) {
		transitionTo(s);
	}
	~Context() {
		delete state;
	}
	void transitionTo(State* s) {
		std::cout << "Context: Transition to state " << typeid(*s).name() << "\n";
		if (state != nullptr) {
			delete state;
		}
		state = s;
		state->setContext(this);
	}
	void request1() {
		state->handle1();
	}
	void request2() {
		state->handle2();
	}
};

class ConcreteStateA : public State {
public:
	void handle1() override;
	void handle2() override {
		std::cout << "Concrete state A: Handle request 2\n";
	}
};

class ConcreteStateB : public State {
public:
	void handle1() override {
		std::cout << "Concrete state B: Handle request 1\n";
	}
	void handle2() override {
		std::cout << "Concrete state B: Handle request 2\n";
		std::cout << "Concrete state B: Change the state to A\n";
		context->transitionTo(new ConcreteStateA());
	}
};

void ConcreteStateA::handle1() {
	std::cout << "Concrete state A: Handle request 1\n";
	std::cout << "Concrete state A: Change the state to B\n";
	context->transitionTo(new ConcreteStateB());
}

void clientRequest() {
	Context* context = new Context(new ConcreteStateA());
	context->request1();
	context->request2();
	delete context;
}

BOOST_AUTO_TEST_CASE(state_test) {
	TEST_MARKER();
	clientRequest();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()