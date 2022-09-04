#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <unordered_map>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(prototype_suite)

enum class Type {
	TYPE_1,
	TYPE_2
};

class Prototype {
public:
	Prototype() = default;
	virtual ~Prototype() = default;
	virtual Prototype* clone() const = 0;
	virtual void function() const = 0;
};

class ConcretePrototype1 : public Prototype {
public:
	Prototype* clone() const override {
		return new ConcretePrototype1(*this);
	}
	void function() const override {
		std::cout << "Prototype 1\n";
	}
};

class ConcretePrototype2 : public Prototype {
public:
	Prototype* clone() const override {
		return new ConcretePrototype2(*this);
	}
	void function() const override {
		std::cout << "Prototype 2\n";
	}
};

class PrototypeFactory {
private:
	std::unordered_map<Type, Prototype*> prototypes;
public:
	PrototypeFactory() {
		prototypes[Type::TYPE_1] = new ConcretePrototype1();
		prototypes[Type::TYPE_2] = new ConcretePrototype2();
	}
	~PrototypeFactory() {
		delete prototypes[Type::TYPE_1];
		delete prototypes[Type::TYPE_2];
	}
	Prototype* createPrototype(Type type) {
		return prototypes[type]->clone();
	}
};

void clientRequest(PrototypeFactory& prototypeFactory) {
	Prototype* prototype = prototypeFactory.createPrototype(Type::TYPE_1);
	prototype->function();
	delete prototype;
	prototype = prototypeFactory.createPrototype(Type::TYPE_2);
	prototype->function();
	delete prototype;
}

BOOST_AUTO_TEST_CASE(prototype_test) {
	TEST_MARKER();
	PrototypeFactory* prototypeFactory = new PrototypeFactory();
	clientRequest(*prototypeFactory);
	delete prototypeFactory;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()