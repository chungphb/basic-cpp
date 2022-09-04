#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <unordered_map>
#include "test_util.h"

BOOST_AUTO_TEST_SUITE(design_patterns_test)

BOOST_AUTO_TEST_SUITE(flyweight_suite)

struct SharedState {
	std::string brand;
	std::string model;
	std::string color;
	SharedState(const std::string& b, const std::string& m, const std::string& c) : brand(b), model(m), color(c) {}
	friend std::ostream& operator<<(std::ostream& os, const SharedState& ss) {
		return os << "[" << ss.brand << ", " << ss.model << ", " << ss.color << "]";
	}
};

struct UniqueState {
	std::string owner;
	std::string plates;
	UniqueState(const std::string& o, const std::string& p) : owner(o), plates(p) {}
	friend std::ostream& operator<<(std::ostream& os, const UniqueState& us) {
		return os << "[" << us.owner << ", " << us.plates << "]";
	}
};

class Flyweight {
private:
	SharedState* sharedState;
public:
	Flyweight() = default;
	Flyweight(const SharedState* ss) : sharedState(new SharedState(*ss)) {}
	Flyweight(const Flyweight& o) : sharedState(new SharedState(*o.sharedState)) {}
	~Flyweight() {
		delete sharedState;
	}
	SharedState* getSharedState() const {
		return sharedState;
	}
	void operation(const UniqueState& uniqueState) const {
		std::cout << "Flyweight: Shared " << *sharedState << " & Unique " << uniqueState << ".\n";
	}
};

class FlyweightFactory {
private:
	std::unordered_map<std::string, Flyweight> flyweights;

	std::string getKey(const SharedState& sharedState) const {
		return sharedState.brand + "_" + sharedState.model + "_" + sharedState.color;
	}

public:
	FlyweightFactory(std::initializer_list<SharedState> sharedStates) {
		for (const SharedState& sharedState : sharedStates) {
			flyweights.emplace(getKey(sharedState), Flyweight(&sharedState));
		}
	}

	Flyweight getFlyweight(const SharedState& sharedState) {
		std::string key = getKey(sharedState);
		if (flyweights.find(key) == flyweights.end()) {
			flyweights.emplace(key, Flyweight(&sharedState));
		}
		return flyweights[key];
	}

	void listFlyweights() const {
		std::cout << "Number of flyweights: " << flyweights.size() << "\n";
		for (std::pair<std::string, Flyweight> entry : flyweights) {
			std::cout << entry.first << "\n";
		}
	}
};

void addCar(FlyweightFactory& ff, const std::string& plates, const std::string& owner, const std::string& brand, const std::string& model, const std::string& color) {
	const Flyweight& flyWeight = ff.getFlyweight({ brand, model, color });
	flyWeight.operation({ owner, plates });
}

BOOST_AUTO_TEST_CASE(flyweight_test) {
	TEST_MARKER();
	FlyweightFactory* ff = new FlyweightFactory({
		{ "Chevrolet", "Camaro2018", "pink" },
		{ "Mercedes Benz", "C300", "black" },
		{ "Mercedes Benz", "C500", "red" },
		{ "BMW", "M5", "red" },
		{ "BMW", "X6", "white" }
	});
	ff->listFlyweights();
	addCar(*ff, "CL234IR", "James Doe", "BMW", "M5", "red");
	addCar(*ff, "CL234IR", "James Doe", "BMW", "X1", "red");
	ff->listFlyweights();
	delete ff;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()