#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(observer_suite)

class IObserver {
public:
	virtual ~IObserver() = default;
	virtual void update(const std::string& message) = 0;
};

class ISubject {
public:
	virtual ~ISubject() = default;
	virtual void attach(IObserver* observer) = 0;
	virtual void detach(IObserver* observer) = 0;
	virtual void notify() = 0;
};

class Subject : public ISubject {
private:
	std::list<IObserver*> observers;
	std::string message;
public:
	virtual ~Subject() = default;
	void attach(IObserver* observer) override {
		observers.push_back(observer);
	}
	void detach(IObserver* observer) override {
		observers.remove(observer);
	}
	void notify() override {
		std::cout << "Number of observers: " << observers.size() << "\n";
		std::list<IObserver*>::iterator it = observers.begin();
		while (it != observers.end()) {
			(*it)->update(message);
			++it;
		}
	}
	void update(std::string m = "Empty") {
		message = m;
		notify();
	}
};

class Observer : IObserver {
private:
	static int ID;
	int id;
	std::string message;
	Subject& subject;
public:
	Observer(Subject& s) : subject(s) {
		id = ++ID;
		subject.attach(this);
		std::cout << "Observer " << id << ": Subscribe\n";
	}
	virtual ~Observer() {}
	void update(const std::string& m) override {
		message = m;
		std::cout << "Observer " << id << ": " << message << "\n";
	}
	void unsubscribe() {
		subject.detach(this);
		std::cout << "Observer " << id << ": Unsubscribe\n";
	}
};

int Observer::ID = 0;

void clientRequest() {
	Subject* subject = new Subject();
	Observer* observer1 = new Observer(*subject);
	Observer* observer2 = new Observer(*subject);
	Observer* observer3;
	subject->update("Message 1");
	observer2->unsubscribe();
	subject->update("Message 2");
	observer3 = new Observer(*subject);
	subject->update("Message 3");
	observer3->unsubscribe();
	observer1->unsubscribe();
	delete observer1;
	delete observer2;
	delete observer3;
	delete subject;
}

BOOST_AUTO_TEST_CASE(observer_test) {
	TEST_MARKER();
	clientRequest();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()