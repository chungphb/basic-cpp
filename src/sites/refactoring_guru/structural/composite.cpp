#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <list>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(composite_suite)

class Component {
protected:
	Component* parent;
public:
	virtual ~Component() = default;
	void setParent(Component* p) {
		parent = p;
	}
	Component* getParent() {
		return parent;
	}
	virtual void add(Component* component) {}
	virtual void remove(Component* component) {}
	virtual bool isComposite() const {
		return false;
	}
	virtual std::string operation() const = 0;
};

class Leaf : public Component {
public:
	std::string operation() const override {
		return "Leaf";
	}
};

class Composite : public Component {
protected:
	std::list<Component*> children;
public:
	void add(Component* component) override {
		children.push_back(component);
		component->setParent(this);
	}
	void remove(Component* component) override {
		children.remove(component);
		component->setParent(nullptr);
	}
	bool isComposite() const override {
		return true;
	}
	std::string operation() const override {
		std::string res;
		for (const Component* child : children) {
			res += child->operation();
			if (child != children.back()) {
				res += " + ";
			}
		}
		return "Branch (" + res + ")";
	}
};

void clientRequest(Component* component) {
	std::cout << "Result: " << component->operation() << "\n";
}

void clientRequest(Component* component1, Component* component2) {
	if (component1->isComposite()) {
		component1->add(component2);
	}
	std::cout << "Result: " << component1->operation() << "\n";
}

BOOST_AUTO_TEST_CASE(composite_test) {
	TEST_MARKER();

	std::cout << "Simple component\n";
	Component* simple = new Leaf();
	clientRequest(simple);

	std::cout << "Complex component\n";
	Component* tree = new Composite();
	Component* branch1 = new Composite();
	Component* branch2 = new Composite();
	Component* leaf1 = new Leaf();
	Component* leaf2 = new Leaf();
	Component* leaf3 = new Leaf();
	branch1->add(leaf1);
	branch1->add(leaf2);
	branch2->add(leaf3);
	tree->add(branch1);
	tree->add(branch2);
	clientRequest(tree);

	std::cout << "Complex component 2\n";
	clientRequest(tree, simple);

	delete simple;
	delete tree;
	delete branch1;
	delete branch2;
	delete leaf1;
	delete leaf2;
	delete leaf3;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()