#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(proxy_suite)

class Subject {
public:
	virtual void request() const = 0;
};

class RealSubject : public Subject{
public:
	void request() const override {
		std::cout << "Real object: Handle request.\n";
	}
};

class Proxy : public Subject {
private:
	RealSubject* realSubject;
	bool checkAccess() const {
		std::cout << "Proxy: Check access.\n";
		return true;
	}
	void logAccess() const {
		std::cout << "Proxy: Log access.\n";
	}
public:
	Proxy(RealSubject* subject) : realSubject(new RealSubject(*subject)) {}
	~Proxy() {
		delete realSubject;
	}
	void request() const override {
		if (checkAccess()) {
			realSubject->request();
			logAccess();
		}
	}
};

void clientRequest(const Subject& subject) {
	subject.request();
}

BOOST_AUTO_TEST_CASE(proxy_test) {
	TEST_MARKER();
	
	std::cout << "Handle real subject\n";
	RealSubject* realSubject = new RealSubject();
	clientRequest(*realSubject);

	std::cout << "Handle proxy\n";
	Proxy* proxy = new Proxy(realSubject);
	clientRequest(*proxy);

	delete realSubject;
	delete proxy;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()