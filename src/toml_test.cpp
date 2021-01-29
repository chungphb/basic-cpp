#define BOOST_TEST_MODULE toml test
#include <boost/test/included/unit_test.hpp>

#include <toml/toml.h>
#include <iostream>

#include "test_util.h"

BOOST_AUTO_TEST_CASE(test_table) {
	TEST_MARKER();
	std::string file = "table.toml";
	std::ifstream ifs(file);
	toml::ParseResult pr = toml::parse(ifs);
	BOOST_REQUIRE_MESSAGE(pr.valid(), pr.errorReason);
	const toml::Value& val = pr.value;
	const toml::Value* name = val.find("album.name");
	if (name && name->is<std::string>()) {
		BOOST_TEST_MESSAGE(name->as<std::string>());
	}
	const toml::Value* artist = val.find("album.artist");
	if (artist && artist->is<std::string>()) {
		BOOST_TEST_MESSAGE(artist->as<std::string>());
	}
	const toml::Value* year = val.find("album.year");
	if (year && year->is<int>()) {
		BOOST_TEST_MESSAGE(year->as<int>());
	}
}

BOOST_AUTO_TEST_CASE(test_array_table) {
	TEST_MARKER();
	std::string file = "array_table.toml";
	std::ifstream ifs(file);
	toml::ParseResult pr = toml::parse(ifs);
	BOOST_REQUIRE_MESSAGE(pr.valid(), pr.errorReason);
	const toml::Value& val = pr.value;
	const toml::Value* res = val.find("album");
	if (!res || !(res->is<toml::Array>())) {
		return;
	}
	const toml::Array& albums = res->as<toml::Array>();
	for (const toml::Value& album : albums) {
		const toml::Value* name = album.find("name");
		if (name && name->is<std::string>()) {
			BOOST_TEST_MESSAGE(name->as<std::string>());
		}
		const toml::Value* res = album.find("singles");
		if (!res || !(res->is<toml::Array>())) {
			continue;
		}
		const toml::Array& singles = res->as<toml::Array>();
		for (const toml::Value& single : singles) {
			if (single.is<std::string>()) {
				BOOST_TEST_MESSAGE("\t" << single.as<std::string>());
			}
		}
	}
}

BOOST_AUTO_TEST_CASE(test_nested_table) {
	TEST_MARKER();
	std::string file = "nested_table.toml";
	std::ifstream ifs(file);
	toml::ParseResult pr = toml::parse(ifs);
	BOOST_REQUIRE_MESSAGE(pr.valid(), pr.errorReason);
	const toml::Value& val = pr.value;
	const toml::Value* name = val.find("album.name");
	if (name && name->is<std::string>()) {
		BOOST_TEST_MESSAGE(name->as<std::string>());
	}
	const toml::Value* artist = val.find("album.artist");
	if (artist && artist->is<std::string>()) {
		BOOST_TEST_MESSAGE(artist->as<std::string>());
	}
	const toml::Value* year = val.find("album.year");
	if (year && year->is<int>()) {
		BOOST_TEST_MESSAGE(year->as<int>());
	}
	const toml::Value* detail = val.find("album.detail");
	if (detail) {
		const toml::Value* genre = detail->find("genre");
		if (genre && genre->is<std::string>()) {
			BOOST_TEST_MESSAGE(genre->as<std::string>());
		}
		const toml::Value* label = detail->find("label");
		if (label && label->is<std::string>()) {
			BOOST_TEST_MESSAGE(label->as<std::string>());
		}
		const toml::Value* res = detail->find("producers");
		if (!res || !(res->is<toml::Array>())) {
			return;
		}
		const toml::Array& producers = res->as<toml::Array>();
		for (const toml::Value& producer : producers) {
			BOOST_TEST_MESSAGE(producer.as<std::string>());
		}
	}
}