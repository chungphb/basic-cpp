#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(chain_of_responsibility_suite)

class Handler {
public:
	virtual Handler* setNext(Handler* handler) = 0;
	virtual std::string handle(std::string request) = 0;
};

class AbstractHandler : public Handler {
private:
	Handler* nextHandler;
public:
	AbstractHandler() : nextHandler(nullptr) {}
	Handler* setNext(Handler* handler) override {
		nextHandler = handler;
		return handler;
	}
	std::string handle(std::string request) override {
		if (nextHandler) {
			return nextHandler->handle(request);
		}
		return {};
	}
};

class ConcreteHandler1 : public AbstractHandler {
public:
	std::string handle(std::string request) override {
		if (request == "1") {
			return "Handler 1";
		} else {
			return AbstractHandler::handle(request);
		}
	}
};

class ConcreteHandler2 : public AbstractHandler {
public:
	std::string handle(std::string request) override {
		if (request == "2") {
			return "Handler 2";
		}
		else {
			return AbstractHandler::handle(request);
		}
	}
};

class ConcreteHandler3 : public AbstractHandler {
public:
	std::string handle(std::string request) override {
		if (request == "3") {
			return "Handler 3";
		}
		else {
			return AbstractHandler::handle(request);
		}
	}
};

void clientRequest(Handler& handler) {
	std::vector<std::string> requests = { "1", "2", "4" };
	for (const auto& request : requests) {
		std::cout << "Request: " << request << "\n";
		std::string response = handler.handle(request);
		std::cout << "Response: " << response << "\n";
	}
}

BOOST_AUTO_TEST_CASE(chain_of_responsibility_test) {
	TEST_MARKER();
	ConcreteHandler1* handler1 = new ConcreteHandler1();
	ConcreteHandler2* handler2 = new ConcreteHandler2();
	ConcreteHandler3* handler3 = new ConcreteHandler3();
	handler1->setNext(handler2)->setNext(handler3);
	std::cout << "Chain: 1 -> 2 -> 3\n";
	clientRequest(*handler1);
	std::cout << "Subchain: 2 -> 3\n";
	clientRequest(*handler2);
	delete handler1;
	delete handler2;
	delete handler3;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()