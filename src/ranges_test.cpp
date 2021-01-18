#include <ranges>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
	std::vector<int> numbers = {1, 2, 3, 4};
	auto range = numbers | std::views::transform([](const int& number) {
		return number * 2;
	});
	std::copy(range.begin(), range.end(), std::ostream_iterator<int>(std::cout, " "));
}