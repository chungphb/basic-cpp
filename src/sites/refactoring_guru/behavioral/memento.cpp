#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(memento_suite)

class Memento {
public:
	virtual ~Memento() = default;
	virtual std::string getName() const = 0;
	virtual std::string getState() const = 0;
	virtual std::string getDate() const = 0;
};

class ConcreteMemento : public Memento {
private:
	std::string state;
	std::string date;
public:
	ConcreteMemento(std::string s) : state(s) {
		std::time_t now = std::time(0);
		date = std::ctime(&now);
	}
	std::string getName() const override {
		return date + " / (" + state.substr(0, 9) + ")";
	}
	std::string getState() const override {
		return state;
	}
	std::string getDate() const override {
		return date;
	}
};

class Originator {
private:
	std::string state;
	std::string generateRandomString(int length = 10) {
		const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		int alphanumSize = sizeof(alphanum) - 1;
		std::string randStr;
		for (int i = 0; i < length; ++i) {
			randStr += alphanum[std::rand() % alphanumSize];
		}
		return randStr;
	}
public:
	Originator(std::string s) : state(s) {
		std::cout << "Originator: Initialize state\n";
		std::cout << "Originator: State = " << state << "\n";
	}
	void operation() {
		state = generateRandomString(30);
		std::cout << "Originator: Update state\n";
		std::cout << "Originator: State = " << state << "\n";
	}
	Memento* save() {
		return new ConcreteMemento(state);
	}
	void restore(Memento* memento) {
		state = memento->getState();
		std::cout << "Originator: Restore state\n";
		std::cout << "Originator: State = " << state << "\n";
		delete memento;
	}
};

class Caretaker {
private:
	std::vector<Memento*> mementos;
	Originator* originator;
public:
	Caretaker(Originator* o) : originator(o) {}
	~Caretaker() {
		for (auto memento : mementos) {
			delete memento;
		}
	}
	void backup() {
		std::cout << "Caretaker: Save state\n";
		mementos.push_back(originator->save());
	}
	void undo() {
		if (mementos.size() == 0) {
			return;
		}
		Memento* memento = mementos.back();
		mementos.pop_back();
		std::cout << "Caretaker: Restore state to " << memento->getName() << "\n";
		try {
			originator->restore(memento);
		} catch (...) {
			undo();
		}
	}
	void showHistory() const {
		std::cout << "Care taker: The list of mementos\n";
		for (Memento* memento : mementos) {
			std::cout << memento->getName() << "\n";
		}
	}
};

void clientRequest() {
	Originator* originator = new Originator("State 0");
	Caretaker* caretaker = new Caretaker(originator);
	caretaker->backup();
	originator->operation();
	caretaker->backup();
	originator->operation();
	caretaker->backup();
	originator->operation();
	caretaker->showHistory();
	caretaker->undo();
	caretaker->undo();
	delete originator;
	delete caretaker;
}

BOOST_AUTO_TEST_CASE(memento_test) {
	TEST_MARKER();
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	clientRequest();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()