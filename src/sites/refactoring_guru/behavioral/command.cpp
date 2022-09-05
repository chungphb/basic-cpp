#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(command_suite)

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() const = 0;
};

class SimpleCommand : public Command {
private:
	std::string payLoad;
public:
	explicit SimpleCommand(std::string pl) : payLoad(pl) {}
	void execute() const override {
		std::cout << "Simple command: " << payLoad << "\n";
	}
};

class Receiver {
public:
	void operation1(const std::string& data) {
		std::cout << "Receiver: Work on [" << data << "]\n";
	}
	void operation2(const std::string& data) {
		std::cout << "Receiver: Also work on [" << data << "]\n";
	}
};

class ComplexCommand : public Command {
private:
	Receiver* receiver;
	std::string str1;
	std::string str2;
public:
	ComplexCommand(Receiver* r, std::string s1, std::string s2) : receiver(r), str1(s1), str2(s2) {}
	void execute() const override {
		std::cout << "Complex command\n";
		receiver->operation1(str1);
		receiver->operation2(str2);
	}
};

class Invoker {
private:
	Command* onStart;
	Command* onFinish;
public:
	~Invoker() {
		delete onStart;
		delete onFinish;
	}
	void setOnStart(Command* command) {
		onStart = command;
	}
	void setOnFinish(Command* command) {
		onFinish = command;
	}
	void operation() {
		std::cout << "Invoker: Start\n";
		if (onStart) {
			onStart->execute();
		}
		std::cout << "Invoker: Finish\n";
		if (onFinish) {
			onFinish->execute();
		}
	}
};

BOOST_AUTO_TEST_CASE(command_test) {
	TEST_MARKER();
	Invoker* invoker = new Invoker();
	invoker->setOnStart(new SimpleCommand("Initialize"));
	Receiver* receiver = new Receiver();
	invoker->setOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
	invoker->operation();
	delete invoker;
	delete receiver;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()