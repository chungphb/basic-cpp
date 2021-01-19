#include <range/v3/all.hpp>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
	std::vector<int> numbers = {1, 2, 3, 4};
	auto range = numbers | ranges::views::transform([](int number) {
		return number * 2;
	});
	std::copy(range.begin(), range.end(), std::ostream_iterator<int>(std::cout, " "));
}