#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(iterator_suite)

template <typename T, typename U>
class Iterator {
	using ItType = std::vector<T>::iterator;
private:
	U* _container;
	ItType _it;
public:
	Iterator(U* container, bool reverse = false) : _container(container) {
		_it = _container->_data.begin();
	}
	void first() {
		_it = _container->_data.begin();
	}
	void next() {
		_it++;
	}
	bool isDone() {
		return _it == _container->_data.end();
	}
	ItType current() {
		return _it;
	}
};

template <typename T>
class Container {
	friend class Iterator<T, Container>;
private:
	std::vector<T> _data;
public:
	void add(T d) {
		_data.push_back(d);
	}
	Iterator<T, Container>* createIterator() {
		return new Iterator<T, Container>(this);
	}
};

class Data {
private:
	int _data;
public:
	Data(int d = 0) : _data(d) {}
	void setData(int d) {
		_data = d;
	}
	int data() {
		return _data;
	}
};

void clientRequest() {
	std::cout << "Iterator with int\n";
	Container<int> container;
	for (int i = 0; i < 10; ++i) {
		container.add(i);
	}
	Iterator<int, Container<int>>* it = container.createIterator();
	for (it->first(); !it->isDone(); it->next()) {
		std::cout << *(it->current()) << "\n";
	}

	std::cout << "Iterator with Data\n";
	Container<Data> container2;
	Data a(100), b(1000), c(10000);
	container2.add(a);
	container2.add(b);
	container2.add(c);
	Iterator<Data, Container<Data>>* it2 = container2.createIterator();
	for (it2->first(); !it2->isDone(); it2->next()) {
		std::cout << it2->current()->data() << "\n";
	}
	delete it;
	delete it2;
}

BOOST_AUTO_TEST_CASE(iterator_test) {
	TEST_MARKER();
	clientRequest();
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()