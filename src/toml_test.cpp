#include <toml/toml.h>
#include <iostream>

void test_table(std::string file) {
	std::ifstream ifs(file);
	toml::ParseResult pr = toml::parse(ifs);
	if (!pr.valid()) {
		std::cerr << pr.errorReason << "\n";
		return;
	}
	const toml::Value& val = pr.value;
	const toml::Value* name = val.find("album.name");
	if (name && name->is<std::string>()) {
		std::cout << name->as<std::string>() << "\n";
	}
	const toml::Value* artist = val.find("album.artist");
	if (artist && artist->is<std::string>()) {
		std::cout << artist->as<std::string>() << "\n";
	}
	const toml::Value* year = val.find("album.year");
	if (year && year->is<int>()) {
		std::cout << year->as<int>() << "\n";
	}
}

void test_array_table(std::string file) {
	std::ifstream ifs(file);
	toml::ParseResult pr = toml::parse(ifs);
	if (!pr.valid()) {
		std::cerr << pr.errorReason << "\n";
		return;
	}
	const toml::Value& val = pr.value;
	const toml::Value* res = val.find("album");
	if (!res || !(res->is<toml::Array>())) {
		return;
	}
	const toml::Array& albums = res->as<toml::Array>();
	for (const toml::Value& album : albums) {
		const toml::Value* name = album.find("name");
		if (name && name->is<std::string>()) {
			std::cout << name->as<std::string>() << "\n";
		}
		const toml::Value* res = album.find("singles");
		if (!res || !(res->is<toml::Array>())) {
			continue;
		}
		const toml::Array& singles = res->as<toml::Array>();
		for (const toml::Value& single : singles) {
			if (single.is<std::string>()) {
				std::cout << "\t" << single.as<std::string>() << "\n";
			}
		}
	}
}

int main(int argc, char** argv) {
	test_table("table.toml");
	test_array_table("array_table.toml");
}