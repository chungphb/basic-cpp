#include <iostream>
#include <random>

int main(int argc, char** argv) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution uid(0, 100);
	auto r = uid(mt);
	std::cout << "Hello " << r << std::endl;
}