#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/unordered_set.hpp>
#include <boost/intrusive/parent_from_member.hpp>
#include <boost/intrusive/any_hook.hpp>
#include <boost/intrusive/circular_slist_algorithms.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/derivation_value_traits.hpp>

#include <list>
#include <vector>
#include <cstring>

#include "test_util.h"

// HOW TO USE BOOST.INSTRUSIVE

// 1. Using base hooks

BOOST_AUTO_TEST_CASE(test_base_hook) {
	TEST_MARKER();
	
	// Intrusive containers
	struct foo : public boost::intrusive::list_base_hook<> {};
	using foo_list = boost::intrusive::list<foo>;
	foo f;
	foo_list fl;
	fl.push_back(f);
	BOOST_CHECK(&f == &fl.front());

	// Non-intrusive containers
	struct foo_2 {};
	using foo_2_list = std::list<foo_2>;
	foo_2 f2;
	foo_2_list f2l;
	f2l.push_back(f2);
	BOOST_CHECK(&f2 != &f2l.front());
}

BOOST_AUTO_TEST_CASE(test_multiple_base_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct tag_1;
	struct tag_2;
	using base_hook_1 = list_base_hook<tag<tag_1>>;
	using base_hook_2 = list_base_hook<tag<tag_2>>;
	struct foo : public base_hook_1, public base_hook_2 {};
	using foo_list = list<foo, base_hook<base_hook_1>>;
	using foo_list_2 = list<foo, base_hook<base_hook_2>>;

	foo f;
	foo_list fl;
	fl.push_back(f);
	foo_list_2 fl2;
	fl2.push_back(f);

	BOOST_CHECK(&f == &fl.front());
	BOOST_CHECK(&f == &fl2.front());
}

// 2. Using member hooks

BOOST_AUTO_TEST_CASE(test_member_hook) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo {
		list_member_hook<> hook;
	};
	using member_hook_option = member_hook<foo, list_member_hook<>, &foo::hook>;
	using foo_list = list<foo, member_hook_option>;

	foo f;
	foo_list fl;
	fl.push_back(f);

	BOOST_CHECK(&f == &fl.front());
}

BOOST_AUTO_TEST_CASE(test_multiple_member_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo {
		list_member_hook<> hook_1;
		list_member_hook<> hook_2;
	};
	using member_hook_option_1 = member_hook<foo, list_member_hook<>, &foo::hook_1>;
	using foo_list_1 = list<foo, member_hook_option_1>;
	using member_hook_option_2 = member_hook<foo, list_member_hook<>, &foo::hook_2>;
	using foo_list_2 = list<foo, member_hook_option_2>;

	foo f;
	foo_list_1 fl1;
	fl1.push_back(f);
	foo_list_2 fl2;
	fl2.push_back(f);

	BOOST_CHECK(&f == &fl1.front());
	BOOST_CHECK(&f == &fl2.front());
}

// 3. Using both hooks

BOOST_AUTO_TEST_CASE(test_both_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public list_base_hook<> {
		list_member_hook<> hook;
	};
	using foo_list = list<foo>;
	using member_hook_option = member_hook<foo, list_member_hook<>, &foo::hook>;
	using foo_list_2 = list<foo, member_hook_option>;

	foo f;
	foo_list fl;
	fl.push_back(f);
	foo_list_2 fl2;
	fl2.push_back(f);

	BOOST_CHECK(&f == &fl.front());
	BOOST_CHECK(&f == &fl2.front());
}

// WHEN TO USE BOOST.INTRUSIVE

using namespace boost::intrusive;
struct base : public list_base_hook<> {
	using object_list = list<base>;
	static object_list ol;
	base() {
		ol.push_back(*this);
	}
	virtual ~base() {
		ol.erase(ol.s_iterator_to(*this));
	}
	virtual void func() {
		std::cout << "base\n";
	}
};

base::object_list base::ol;

struct derived_0 : public base {
	int val = 0;
	void func() {
		std::cout << "derived_0\n";
	}
};

struct derived_1 : public base {
	int val = 0;
	void func() {
		std::cout << "derived_1\n";
	}
};

void func_all() {
	auto e = base::ol.end();
	for (auto i = base::ol.begin(); i != e; i++) {
		i->func();
	}
}

BOOST_AUTO_TEST_CASE(test_storing_base_and_derived_objects_in_the_same_container) {
	TEST_MARKER();
	base b;
	derived_0 d0;
	derived_1 d1;
	func_all();
}

// SAFE HOOKS

BOOST_AUTO_TEST_CASE(test_safe_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public list_base_hook<link_mode<safe_link>> {};
	using foo_list = list<foo>;

	foo f;
	BOOST_CHECK(!f.is_linked());
	foo_list fl;
	fl.push_back(f);
	BOOST_CHECK(f.is_linked());
}

// AUTO-UNLINK HOOKS

BOOST_AUTO_TEST_CASE(test_auto_unlink_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public list_base_hook<link_mode<auto_unlink>> {};
	using foo_list = list<foo, constant_time_size<false>>;

	foo f;
	BOOST_CHECK(!f.is_linked());
	foo_list fl;
	fl.push_back(f);
	BOOST_CHECK(f.is_linked());
	f.unlink();
	BOOST_CHECK(!f.is_linked());
	BOOST_CHECK(fl.empty());
}

// SLIST

BOOST_AUTO_TEST_CASE(test_slist) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public slist_base_hook<> {
		int val;
		slist_member_hook<> hook;
		foo(int v) : val{v} {}
	};
	using base_slist = slist<foo>;
	using member_hook_option = member_hook<foo, slist_member_hook<>, &foo::hook>;
	using member_slist = slist<foo, member_hook_option>;
	using vec_it = std::vector<foo>::iterator;
	using vec_rit = std::vector<foo>::reverse_iterator;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{i});
	}
	base_slist bsl;
	member_slist msl;;
	/// Reverse the order in the base hook list
	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		bsl.push_front(*it);
	}
	/// Keep the order (by reversing twice) in the member hook list
	for (base_slist::iterator bit{bsl.begin()}, bitend{bsl.end()}; bit != bitend; bit++) {
		msl.push_front(*bit);
	}

	auto bit = bsl.begin();
	auto mit = msl.begin();
	for (vec_rit rit{v.rbegin()}, ritend{v.rend()}; rit != ritend; rit++, bit++) {
		BOOST_CHECK(&*rit == &*bit);
	}
	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++, mit++) {
		BOOST_CHECK(&*it == &*mit);
	}
}

// LIST

// SET, MULTISET, RBTREE

namespace test_set_vs_multiset_vs_btree_ns {

struct foo : public set_base_hook<> {
	int val;
	set_member_hook<> hook;
	foo(int v) : val{v} {}
	friend bool operator<(const foo& lhs, const foo& rhs) {
		return lhs.val < rhs.val;
	}
	friend bool operator>(const foo& lhs, const foo& rhs) {
		return lhs.val > rhs.val;
	}
	friend bool operator==(const foo& lhs, const foo& rhs) {
		return lhs.val == rhs.val;
	}
};

}

BOOST_AUTO_TEST_CASE(test_set_vs_multiset_vs_btree) {
	TEST_MARKER();

	using namespace test_set_vs_multiset_vs_btree_ns;
	using namespace boost::intrusive;
	using base_set = set<foo, compare<std::greater<foo>>>;
	using member_hook_option = member_hook<foo, set_member_hook<>, &foo::hook>;
	using member_set = set<foo, member_hook_option>;
	using vec_it = std::vector<foo>::iterator;
	using vec_rit = std::vector<foo>::reverse_iterator;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{i});
	}
	base_set bs;
	member_set ms;
	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		bs.insert(*it);
		ms.insert(*it);
	}

	auto bit = bs.begin();
	auto mit = ms.begin();
	for (vec_rit rit{v.rbegin()}, ritend{v.rend()}; rit != ritend; rit++, bit++) {
		BOOST_CHECK(&*rit == &*bit);
	}
	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++, mit++) {
		BOOST_CHECK(&*it == &*mit);
	}
}

// UNORDERED_SET, UNORDERED_MULTISET

namespace test_unordered_set_vs_unordered_multiset_ns {

struct foo : public unordered_set_base_hook<> {
	int val;
	unordered_set_member_hook<> hook;
	foo(int v) : val{v} {}
	friend bool operator==(const foo& lhs, const foo& rhs) {
		return lhs.val == rhs.val;
	}
	friend std::size_t hash_value(const foo& f) {
		return std::size_t(f.val);
	}
};

}

BOOST_AUTO_TEST_CASE(test_unordered_set_vs_unordered_multiset) {
	TEST_MARKER();

	using namespace test_unordered_set_vs_unordered_multiset_ns;
	using namespace boost::intrusive;
	using base_unordered_set = unordered_set<foo>;
	using member_hook_option = member_hook<foo, unordered_set_member_hook<>, &foo::hook>;
	using member_unordered_multiset = unordered_multiset<foo, member_hook_option>;
	using vec_it = std::vector<foo>::iterator;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{i});
	}
	std::vector<foo> v_2{v};
	base_unordered_set::bucket_type base_buckets[100];
	member_unordered_multiset::bucket_type member_buckets[200];
	base_unordered_set bus{base_unordered_set::bucket_traits{base_buckets, 100}};
	member_unordered_multiset mus{member_unordered_multiset::bucket_traits{member_buckets, 200}};
	for (vec_it it{v.begin()}, itend{v.end()}, it_2{v_2.begin()}; it != itend; it++, it_2++) {
		bus.insert(*it);
		mus.insert(*it);
		mus.insert(*it_2);
	}

	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		BOOST_CHECK(bus.count(*it) == 1);
		BOOST_CHECK(mus.count(*it) == 2);
	}
}

namespace test_unordered_set_vs_unordered_multiset_ns {

using base_hook_option = base_hook<unordered_set_base_hook<>>;
using bucket_type = unordered_bucket<base_hook_option>::type;
using bucket_ptr = unordered_bucket_ptr<base_hook_option>::type;

struct custom_bucket_traits {
	static const int n_buckets = 100;
	custom_bucket_traits(bucket_ptr p) : ptr{p} {}
	bucket_ptr bucket_begin() const {
		return ptr;
	}
	std::size_t bucket_count() const {
		return n_buckets;
	}
private:
	bucket_ptr ptr;
};

}

BOOST_AUTO_TEST_CASE(test_custom_bucket_traits) {
	TEST_MARKER();

	using namespace test_unordered_set_vs_unordered_multiset_ns;
	using namespace boost::intrusive;
	using foo_unordered_set = unordered_set<foo, bucket_traits<custom_bucket_traits>>;
	using vec_it = std::vector<foo>::iterator;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{i});
	}
	bucket_type buckets[custom_bucket_traits::n_buckets];
	custom_bucket_traits btraits{buckets};
	foo_unordered_set fus{btraits};
	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		fus.insert(*it);
	}

	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		BOOST_CHECK(fus.count(*it) == 1);
	}
}


// MAP, MULTIMAP-LIKE INTERFACE

BOOST_AUTO_TEST_CASE(test_map_vs_multimap_interface) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public set_base_hook<>, unordered_set_base_hook<> {
		int key;
		int val;
		explicit foo(int k, int v) : key{k}, val{v} {}
	};
	struct foo_key_f {
		using type = int;
		const type& operator()(const foo& f) const {
			return f.key;
		}
	};
	using foo_map = set<foo, key_of_value<foo_key_f>>;
	using foo_unordered_map = unordered_set<foo, key_of_value<foo_key_f>>;
	BOOST_STATIC_ASSERT(boost::is_same<foo_map::key_type, int>::value);
	BOOST_STATIC_ASSERT(boost::is_same<foo_unordered_map::key_type, int>::value);
	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{i, i});
	}
	foo_map fm{v.begin(), v.end()};
	foo_unordered_map::bucket_type buckets[100];
	foo_unordered_map fum{v.begin(), v.end(), foo_unordered_map::bucket_traits{buckets, 100}};

	for (int key = 0; key < 100; key++) {
		BOOST_CHECK(fm.find(key) != fm.end());
		BOOST_CHECK(fum.find(key) != fum.end());
		BOOST_CHECK(fm.lower_bound(key) != fm.end());
		BOOST_CHECK(++fm.lower_bound(key) == fm.upper_bound(key));
		BOOST_CHECK(fm.equal_range(key).first != fm.equal_range(key).second);
		BOOST_CHECK(fum.equal_range(key).first != fum.equal_range(key).second);
	}
	for (int key = 0; key < 100; key++) {
		BOOST_CHECK(fm.count(key) == 1);
		BOOST_CHECK(fum.count(key) == 1);
		BOOST_CHECK(fm.erase(key) == 1);
		BOOST_CHECK(fum.erase(key) == 1);
	}
	BOOST_CHECK(fm.empty());
	BOOST_CHECK(fum.empty());
}

// AVL_SET, AVL_MULTISET, AVLTREE: https://www.boost.org/doc/libs/1_64_0/doc/html/intrusive/avl_set_multiset.html

// SPLAY_SET, SPLAY_MULTISET, SPLAY_TREE: https://www.boost.org/doc/libs/1_64_0/doc/html/intrusive/splay_set_multiset.html

// SG_SET, SG_MULTISET, SGTREE: https://www.boost.org/doc/libs/1_64_0/doc/html/intrusive/sg_set_multiset.html

// TREAP_SET, TREAP_MULTISET, TREAP: https://www.boost.org/doc/libs/1_64_0/doc/html/intrusive/treap_set_multiset.html

// ADVANCED LOOKUP AND INSERTION FUNCTIONS

namespace test_advanced_lookup_and_insertion_functions_ns {

struct str_hasher {
	std::size_t operator()(const char* str) {
		std::size_t seed = 0;
		for (; *str; str++) {
			boost::hash_combine(seed, *str);
		}
		return seed;
	}
};

struct foo : public set_base_hook<>, unordered_set_base_hook<> {
	foo(const char* k, int v) : key{k}, val{v} {}
	const std::string& get_key() const {
		return key;
	}
	int get_value() const {
		return val;
	}
	friend bool operator<(const foo& lhs, const foo& rhs) {
		return lhs.key < rhs.key;
	}
	friend bool operator==(const foo& lhs, const foo& rhs) {
		return lhs.key == rhs.key;
	}
	friend std::size_t hash_value(const foo& f) {
		return str_hasher()(f.key.c_str());
	}
private:
	std::string key;
	int val;
};

using foo_set = set<foo>;
using foo_uset = unordered_set<foo>;
 
/// Search functions

foo* get_from_set(const char* key, foo_set& fs) {
	/// Can't build foo without passing its value
	/// auto it = fs.find(foo{key});
	/// return it != fs.end() ? &*it : nullptr;
	return nullptr;
}

foo* get_from_uset(const char* key, foo_uset& fus) {
	/// Can't build foo without passing its value
	/// auto it = fus.find(foo{key});
	/// return it != fus.end() ? &*it : nullptr;
	return nullptr;
}

/// Optimized search functions

struct str_foo_cmp {
	bool operator()(const char* key, const foo& f) const {
		return std::strcmp(key, f.get_key().c_str()) < 0;
	}
	bool operator()(const foo& f, const char* key) const {
		return std::strcmp(f.get_key().c_str(), key) < 0;
	}
};

struct str_foo_eql {
	bool operator()(const char* key, const foo& f) const {
		return std::strcmp(key, f.get_key().c_str()) == 0;
	}
	bool operator()(const foo& f, const char* key) const {
		return std::strcmp(f.get_key().c_str(), key) == 0;
	}
};

foo* get_from_set_optimized(const char* key, foo_set& fs) {
	auto it = fs.find(key, str_foo_cmp());
	return it != fs.end() ? &*it : nullptr;
}

foo* get_from_uset_optimized(const char* key, foo_uset& fus) {
	auto it = fus.find(key, str_hasher(), str_foo_eql());
	return it != fus.end() ? &*it : nullptr;
}

}

BOOST_AUTO_TEST_CASE(test_advanced_lookup) {
	TEST_MARKER();

	using namespace test_advanced_lookup_and_insertion_functions_ns;
	using namespace boost::intrusive;
	using vec_it = std::vector<foo>::iterator;

	std::vector<std::string> keys;
	for (int i = 0; i < 100; i++) {
		keys.emplace_back("str" + std::to_string(i));
	}
	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{keys[i].c_str(), i});
	}
	foo_set fs;
	foo_uset::bucket_type buckets[100];
	foo_uset fus{foo_uset::bucket_traits{buckets, 100}};
	for (vec_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		fs.insert(*it);
		fus.insert(*it);
	}

	for (int i = 0; i < 100; i++) {
		auto* f = get_from_set_optimized(keys[i].c_str(), fs);
		BOOST_CHECK(f && f->get_value() == i);
		f = get_from_uset_optimized(keys[i].c_str(), fus);
		BOOST_CHECK(f && f->get_value() == i);
	}
}

namespace test_advanced_lookup_and_insertion_functions_ns {

/// Insertion functions

bool insert_to_set(const char* key, int val, foo_set& fs) {
	foo* f = new foo{key, val};
	auto success = fs.insert(*f).second;
	if (!success) {
		delete f;
	}
	return success;
}

bool insert_to_uset(const char* key, int val, foo_uset& fus) {
	foo* f = new foo{key, val};
	auto success = fus.insert(*f).second;
	if (!success) {
		delete f;
	}
	return success;
}

/// Optimized insertion functions

bool insert_to_set_optimized(const char* key, int val, foo_set& fs) {
	foo_set::insert_commit_data insert_data;
	bool success = fs.insert_check(key, str_foo_cmp(), insert_data).second;
	if (success) {
		fs.insert_commit(*new foo{key, val}, insert_data);
	}
	return success;
}

bool insert_to_uset_optimized(const char* key, int val, foo_uset& fus) {
	foo_uset::insert_commit_data insert_data;
	bool success = fus.insert_check(key, str_hasher(), str_foo_eql(), insert_data).second;
	if (success) {
		fus.insert_commit(*new foo{key, val}, insert_data);
	}
	return success;
}

}

BOOST_AUTO_TEST_CASE(test_advanced_insertion) {
	TEST_MARKER();

	using namespace test_advanced_lookup_and_insertion_functions_ns;
	using namespace boost::intrusive;
	using vec_it = std::vector<foo>::iterator;

	std::vector<std::string> keys;
	for (int i = 0; i < 100; i++) {
		keys.emplace_back("str" + std::to_string(i));
	}
	foo_set fs;
	foo_uset::bucket_type buckets[100];
	foo_uset fus{foo_uset::bucket_traits{buckets, 100}};

	for (int i = 0; i < 100; i++) {
		BOOST_CHECK(insert_to_set_optimized(keys[i].c_str(), i, fs));
		BOOST_CHECK(insert_to_uset_optimized(keys[i].c_str(), i, fus));
	}
	for (int i = 0; i < 100; i++) {
		auto* f = get_from_set_optimized(keys[i].c_str(), fs);
		BOOST_CHECK(f && f->get_value() == i);
		f = get_from_uset_optimized(keys[i].c_str(), fus);
		BOOST_CHECK(f && f->get_value() == i);
	}

	struct disposer {
		void operator()(foo* f) {
			delete f;
		}
	};
	fs.clear_and_dispose(disposer());
	fus.clear_and_dispose(disposer());
}

namespace test_positional_insertion_functions_ns {
	
struct foo : public set_base_hook<> {
public:
	foo(int k) : key{k} {}
	friend bool operator<(const foo& lhs, const foo& rhs) {
		return lhs.key < rhs.key;
	}
	friend bool operator>(const foo& lhs, const foo& rhs) {
		return lhs.key > rhs.key;
	}
private:
	int key;
};

}

BOOST_AUTO_TEST_CASE(test_positional_insertion) {
	TEST_MARKER();

	using namespace test_positional_insertion_functions_ns;
	using namespace boost::intrusive;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(foo{i});
	}
	/// Uses push_back instead of insert because v is already sorted
	{
		using foo_set = set<foo>;
		foo_set fs;
		for (int i = 0; i < 100; i++) {
			fs.push_back(v[i]);
		}
		foo_set::const_iterator nxt_it{fs.begin()}, cur_it{nxt_it++};
		for (int i = 0; i < 99; i++, cur_it++, nxt_it++) {
			BOOST_CHECK(*cur_it < *nxt_it);
		}
	}
	/// Uses push_front instead of insert because v is already sorted
	{
		using foo_set = set<foo, compare<std::greater<foo>>>;
		foo_set fs;
		for (int i = 0; i < 100; i++) {
			fs.push_front(v[i]);
		}
		foo_set::const_iterator nxt_it{fs.begin()}, cur_it{nxt_it++};
		for (int i = 0; i < 99; i++, cur_it++, nxt_it++) {
			BOOST_CHECK(*cur_it > *nxt_it);
		}
	}
	/// Uses insert_before instead of insert because v is already sorted
	{
		using foo_set = set<foo>;
		foo_set fs;
		fs.insert_before(fs.begin(), v[0]);
		foo_set::const_iterator cur_pos = fs.insert_before(fs.end(), v[99]);
		for (int i = 1; i < 99; i++) {
			fs.insert_before(cur_pos, v[i]);
		}
		foo_set::const_iterator nxt_it{fs.begin()}, cur_it{nxt_it++};
		for (int i = 0; i < 99; i++, cur_it++, nxt_it++) {
			BOOST_CHECK(*cur_it < *nxt_it);
		}
	}
}

// ERASING AND DISPOSING VALUES FROM CONTAINERS

BOOST_AUTO_TEST_CASE(test_erasing_and_disposing_values_from_containers) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public list_base_hook<> {
		int val;
		foo(int v) : val{v} {}
	};
	using foo_list = list<foo>;
	struct is_even {
		bool operator()(const foo& f) {
			return f.val % 2 == 0;
		}
	};
	struct disposer {
		void operator()(foo* f) {
			delete f;
		}
	};

	foo_list fl;
	try {
		for (int i = 0; i < 100; i++) {
			fl.push_back(*new foo{i});
		}
		fl.remove_and_dispose_if(is_even(), disposer());
	}
	catch (...) {
		fl.clear_and_dispose(disposer());
	}
	fl.erase_and_dispose(fl.begin(), fl.end(), disposer());
}

// CLONING CONTAINERS

namespace test_cloning_containers_ns {

struct foo : public list_base_hook<> {
	int val;
	foo(int v) : val{v} {}
	friend bool operator==(const foo& lhs, const foo& rhs) {
		return lhs.val == rhs.val;
	}
};

}
BOOST_AUTO_TEST_CASE(test_cloning_containers) {
	TEST_MARKER();

	using namespace test_cloning_containers_ns;
	using namespace boost::intrusive;
	using foo_list = list<foo>;
	struct cloner {
		foo* operator()(const foo& f) {
			return new foo{f};
		}
	};
	struct disposer {
		void operator()(foo* f) {
			return delete f;
		}
	};

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.emplace_back(i);
	}
	foo_list fl;
	fl.insert(fl.end(), v.begin(), v.end());
	foo_list cloned_fl;
	cloned_fl.clone_from(fl, cloner(), disposer());

	BOOST_CHECK(cloned_fl == fl);

	cloned_fl.clear_and_dispose(disposer());
}

// FUNCTION HOOKS

namespace test_function_hooks_ns {

struct foo {
	int val;
	struct inner_foo {
		int val;
		list_member_hook<> hook;
	} inner;
};

struct functor {
	using hook_type = list_member_hook<>;
	using hook_ptr = hook_type*;
	using const_hook_ptr = const hook_type*;
	using value_type = foo;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	static hook_ptr to_hook_ptr(value_type& value) {
		return &value.inner.hook;
	}
	static const_hook_ptr to_hook_ptr(const value_type& value) {
		return &value.inner.hook;
	}
	static pointer to_value_ptr(hook_ptr n) {
		return get_parent_from_member<foo>(
			get_parent_from_member<foo::inner_foo>(n, &foo::inner_foo::hook),
			&foo::inner
		);
	}
	static const_pointer to_value_ptr(const_hook_ptr n) {
		return get_parent_from_member<foo>(
			get_parent_from_member<foo::inner_foo>(n, &foo::inner_foo::hook),
			&foo::inner
		);
	}
};

}

BOOST_AUTO_TEST_CASE(test_function_hooks) {
	TEST_MARKER();

	using namespace test_function_hooks_ns;
	using namespace boost::intrusive;
	using foo_list = list<foo, function_hook<functor>>;
	
	foo f;
	foo_list fl;
	fl.push_back(f);

	BOOST_CHECK(&f == &fl.front());
}

// RECURSIVE CONTAINERS

BOOST_AUTO_TEST_CASE(test_recursive_containers_with_base_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public list_base_hook<> {
		/// Must specify the hook type to avoid early instantiation
		list<foo, base_hook<list_base_hook<>>> foo_children;
		foo() : list_base_hook<>(), foo_children() {}
	};
	/// Must specify the hook type to avoid early instantiation
	using foo_list = list<foo, base_hook<list_base_hook<>>>;

	foo f, f_2;
	foo_list fl;
	fl.insert(fl.begin(), f);
	fl.begin()->foo_children.insert(fl.begin()->foo_children.begin(), f_2);

	BOOST_CHECK(&f == &fl.front());
	BOOST_CHECK(&f_2 == &fl.front().foo_children.front());

	fl.front().foo_children.clear();
	fl.clear();
}

namespace test_recursive_containers_ns {

struct foo;

struct functor {
	using hook_type = list_member_hook<>;
	using hook_ptr = hook_type*;
	using const_hook_ptr = const hook_type*;
	using value_type = foo;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	static hook_ptr to_hook_ptr(value_type&);
	static const_hook_ptr to_hook_ptr(const value_type&);
	static pointer to_value_ptr(hook_ptr);
	static const_pointer to_value_ptr(const_hook_ptr);
};

struct foo {
	list_member_hook<> hook;
	/// Must use function_hook instead of member_hook to avoid early instantiation
	list<foo, function_hook<functor>> foo_children;
	foo() : hook(), foo_children() {}
};

inline functor::hook_ptr functor::to_hook_ptr(value_type& value) {
	return &value.hook;
}

inline functor::const_hook_ptr functor::to_hook_ptr(const value_type& value) {
	return &value.hook;
}

inline functor::pointer functor::to_value_ptr(hook_ptr n) {
	return get_parent_from_member<foo>(n, &foo::hook);
}

inline functor::const_pointer functor::to_value_ptr(const_hook_ptr n) {
	return get_parent_from_member<foo>(n, &foo::hook);
}

}

BOOST_AUTO_TEST_CASE(test_recursive_containers_with_member_hooks) {
	TEST_MARKER();

	using namespace test_recursive_containers_ns;
	using namespace boost::intrusive;
	/// Must use function_hook instead of member_hook to avoid early instantiation
	using foo_list = list<foo, function_hook<functor>>;

	foo f, f_2;
	foo_list fl;
	fl.insert(fl.begin(), f);
	fl.begin()->foo_children.insert(fl.begin()->foo_children.begin(), f_2);

	BOOST_CHECK(&f == &fl.front());
	BOOST_CHECK(&f_2 == &fl.front().foo_children.front());

	fl.front().foo_children.clear();
	fl.clear();
}

// USING SMART POINTERS WITH CONTAINERS

// OBTAINING ITERATORS FROM VALUES

namespace test_obtaining_iterators_from_values_ns {

struct foo {
	int val;
	list_member_hook<> l_hook;
	unordered_set_member_hook<> us_hook;
	foo(int v) : val{v} {}
	friend bool operator==(const foo& lhs, const foo& rhs) {
		return lhs.val == rhs.val;
	}
	friend bool operator!=(const foo& lhs, const foo& rhs) {
		return lhs.val != rhs.val;
	}
	friend std::size_t hash_value(const foo& f) {
		return boost::hash<int>()(f.val);
	}
};

}

BOOST_AUTO_TEST_CASE(test_obtaining_iterators_from_values) {
	TEST_MARKER();

	using namespace test_obtaining_iterators_from_values_ns;
	using namespace boost::intrusive;
	using l_member_hook_options = member_hook<foo, list_member_hook<>, &foo::l_hook>;
	using foo_list = list<foo, l_member_hook_options>;
	using us_member_hook_options = member_hook<foo, unordered_set_member_hook<>, &foo::us_hook>;
	using foo_unordered_set = unordered_set<foo, us_member_hook_options>;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.emplace_back(i);
	}
	foo_list fl;
	fl.insert(fl.end(), v.begin(), v.end());
	foo_unordered_set::bucket_type buckets[100];
	foo_unordered_set fus{foo_unordered_set::bucket_traits{buckets, 100}};
	fus.insert(v.begin(), v.end());

	foo_list::iterator lit{fl.begin()};
	for (int i = 0; i < 100; i++, lit++) {
		BOOST_CHECK(fl.iterator_to(v[i]) == lit && fl.s_iterator_to(v[i]) == lit);
	}
	for (int i = 0; i < 100; i++) {
		foo_unordered_set::iterator usit = fus.find(v[i]);
		BOOST_CHECK(fus.iterator_to(v[i]) == usit);
		BOOST_CHECK(*fus.local_iterator_to(v[i]) == *usit && *fus.s_local_iterator_to(v[i]) == *usit);
	}
}

// ANY HOOKS

BOOST_AUTO_TEST_CASE(test_any_hooks) {
	TEST_MARKER();

	using namespace boost::intrusive;
	struct foo : public any_base_hook<> {
		int val;
		any_member_hook<> hook;
		foo(int v) : val{v} {}
	};
	using base_slist_option = any_to_slist_hook<base_hook<any_base_hook<>>>;
	using foo_slist = slist<foo, base_slist_option>;
	using member_list_option = any_to_list_hook<member_hook<foo, any_member_hook<>, &foo::hook>>;
	using foo_list = list<foo, member_list_option>;
	using vector_it = std::vector<foo>::iterator;
	using vector_rit = std::vector<foo>::reverse_iterator;

	std::vector<foo> v;
	for (int i = 0; i < 100; i++) {
		v.emplace_back(i);
	}
	foo_slist fsl;
	foo_list fl;
	for (vector_it it{v.begin()}, itend{v.end()}; it != itend; it++) {
		fsl.push_front(*it);
		fl.push_back(*it);
	}

	foo_slist::iterator slit{fsl.begin()};
	foo_list::reverse_iterator lit{fl.rbegin()};
	vector_rit vit{v.rbegin()}, vitend{v.rend()};
	for (; vit != vitend; vit++, slit++, lit++) {
		BOOST_CHECK(&*vit == &*slit);
		BOOST_CHECK(&*vit == &*lit);
	}
}

// NODETRAITS

// 1. Intrusive singly linked list algorithms

namespace test_circular_slist_algorithms_ns {

struct my_node {
	my_node* next;
};

struct my_slist_node_traits {
	using node = my_node;
	using node_ptr = my_node*;
	using const_node_ptr = const my_node*;
	static node_ptr get_next(const_node_ptr n) {
		return n->next;
	}
	static void set_next(node_ptr n, node_ptr next) {
		n->next = next;
	}
};

}

BOOST_AUTO_TEST_CASE(test_circular_slist_algorithms) {
	TEST_MARKER();

	using namespace test_circular_slist_algorithms_ns;
	using algo = boost::intrusive::circular_slist_algorithms<my_slist_node_traits>;

	my_node node_1, node_2, node_3;
	algo::init_header(&node_1);
	BOOST_CHECK(algo::count(&node_1) == 1);
	algo::link_after(&node_1, &node_2);
	BOOST_CHECK(algo::count(&node_1) == 2);
	BOOST_CHECK(&*algo::get_previous_node(&node_1) == &node_2);
	BOOST_CHECK(&*algo::get_previous_node(&node_2) == &node_1);
	algo::link_after(&node_1, &node_3);
	BOOST_CHECK(algo::count(&node_1) == 3);
	BOOST_CHECK(&*algo::get_previous_node(&node_1) == &node_2);
	BOOST_CHECK(&*algo::get_previous_node(&node_2) == &node_3);
	BOOST_CHECK(&*algo::get_previous_node(&node_3) == &node_1);
	algo::unlink_after(&node_1);
	BOOST_CHECK(algo::count(&node_1) == 2);
	algo::unlink(&node_2);
	BOOST_CHECK(algo::count(&node_1) == 1);
}

// 2. Intrusive doubly linked list algorithms

namespace test_circular_list_algorithms_ns {

struct my_node {
	my_node* next;
	my_node* prev;
};

struct my_list_node_traits {
	using node = my_node;
	using node_ptr = my_node*;
	using const_node_ptr = const my_node*;
	static node_ptr get_next(const_node_ptr n) {
		return n->next;
	}
	static void set_next(node_ptr n, node_ptr next) {
		n->next = next;
	}
	static node_ptr get_previous(const_node_ptr n) {
		return n->prev;
	}
	static void set_previous(node_ptr n, node_ptr prev) {
		n->prev = prev;
	}
};

}

BOOST_AUTO_TEST_CASE(test_circular_list_algorithms) {
	TEST_MARKER();

	using namespace test_circular_list_algorithms_ns;
	using algo = boost::intrusive::circular_list_algorithms<my_list_node_traits>;

	my_node node_1, node_2, node_3;
	algo::init_header(&node_1);
	BOOST_CHECK(algo::count(&node_1) == 1);
	algo::link_before(&node_1, &node_2);
	BOOST_CHECK(algo::count(&node_1) == 2);
	algo::link_after(&node_2, &node_3);
	BOOST_CHECK(algo::count(&node_1) == 3);
	algo::unlink(&node_3);
	BOOST_CHECK(algo::count(&node_1) == 2);
	algo::unlink(&node_2);
	BOOST_CHECK(algo::count(&node_1) == 1);
	algo::unlink(&node_1);
	BOOST_CHECK(algo::count(&node_1) == 1);
}

// 3. Intrusive red-black tree algorithms

namespace test_red_black_tree_algorithms_ns {

struct my_node {
	my_node* parent;
	my_node* left;
	my_node* right;
	int color;
	int val;
	my_node(int v) : val{v} {}
};

struct my_rbtree_node_traits {
	using node = my_node;
	using node_ptr = my_node*;
	using const_node_ptr = const my_node*;
	using color = int;
	static node_ptr get_parent(const_node_ptr n) {
		return n->parent;
	}
	static void set_parent(node_ptr n, node_ptr parent) {
		n->parent = parent;
	}
	static node_ptr get_left(const_node_ptr n) {
		return n->left;
	}
	static void set_left(node_ptr n, node_ptr left) {
		n->left = left;
	}
	static node_ptr get_right(const_node_ptr n) {
		return n->right;
	}
	static void set_right(node_ptr n, node_ptr right) {
		n->right = right;
	}
	static color get_color(const_node_ptr n) {
		return n->color;
	}
	static void set_color(node_ptr n, color c) {
		n->color = c;
	}
	static color black() {
		return color{0};
	}
	static color red() {
		return color{1};
	}
};

struct node_ptr_compare {
	bool operator()(const my_node* lhs, const my_node* rhs) {
		return lhs->val < rhs->val;
	}
};

}

BOOST_AUTO_TEST_CASE(test_red_black_tree_algorithms) {
	TEST_MARKER();

	using namespace test_red_black_tree_algorithms_ns;
	using algo = boost::intrusive::rbtree_algorithms<my_rbtree_node_traits>;

	my_node node_1{1}, node_2{2}, node_3{3};
	algo::init_header(&node_1);
	algo::insert_equal_upper_bound(&node_1, &node_2, node_ptr_compare());
	algo::insert_equal_lower_bound(&node_1, &node_3, node_ptr_compare());
	
	BOOST_CHECK(node_1.left == &node_2);
	BOOST_CHECK(algo::next_node(node_1.left) == &node_3);

	algo::unlink(&node_2);
	algo::erase(&node_1, &node_3);
}

// 4. Intrusive splay tree algorithms

// 5. Intrusive avl tree algorithms

// 6. Intrusive treap algorithms

// VALUETRAITS

namespace test_value_traits_ns {

namespace bi = boost::intrusive;

struct legacy_value {
	int id;
	legacy_value* next;
	legacy_value* prev;
};

struct legacy_node_traits {
	using node = legacy_value;
	using node_ptr = legacy_value*;
	using const_node_ptr = const legacy_value*;
	static node_ptr get_next(const_node_ptr n) {
		return n->next;
	}
	static void set_next(node_ptr n, node_ptr next) {
		n->next = next;
	}
	static node_ptr get_previous(const_node_ptr n) {
		return n->prev;
	}
	static void set_previous(node_ptr n, node_ptr prev) {
		n->prev = prev;
	}
};

struct legacy_value_traits {
	using node_traits = legacy_node_traits;
	using node_ptr = legacy_node_traits::node_ptr;
	using const_node_ptr = legacy_node_traits::const_node_ptr;
	using value_type = legacy_value;
	using pointer = legacy_value*;
	using const_pointer = const legacy_value*;
	static const bi::link_mode_type link_mode = bi::normal_link;
	static node_ptr to_node_ptr(value_type& value) {
		return node_ptr{&value};
	}
	static const_node_ptr to_node_ptr(const value_type& value) {
		return const_node_ptr{&value};
	}
	static pointer to_value_ptr(node_ptr n) {
		return pointer{n};
	}
	static const_pointer to_value_ptr(const_node_ptr n) {
		return const_pointer{n};
	}
};

using trivial_legacy_value_traits = bi::trivial_value_traits<legacy_node_traits, bi::normal_link>;

using value_traits_option = bi::value_traits<legacy_value_traits>;
using trivial_value_traits_option = bi::value_traits<trivial_legacy_value_traits>;

using legacy_list = bi::list<legacy_value, value_traits_option>;
using legacy_slist = bi::slist<legacy_value, value_traits_option>;
using trivial_legacy_list = bi::list<legacy_value, trivial_value_traits_option>;
using trivial_legacy_slist = bi::slist<legacy_value, trivial_value_traits_option>;

template <typename list>
void test_list() {
	using vect = std::vector<legacy_value>;
	vect lv_vec;
	for (int i = 0; i < 100; i++) {
		legacy_value lv;
		lv.id = i;
		lv_vec.push_back(lv);
	}
	list lv_list{lv_vec.begin(), lv_vec.end()};
	typename vect::const_iterator vit{lv_vec.begin()}, vitend{lv_vec.end()};
	typename list::const_iterator lit{lv_list.begin()};
	for (; vit != vitend; vit++, lit++) {
		BOOST_CHECK(&*vit == &*lit);
	}
}

}

BOOST_AUTO_TEST_CASE(test_trivial_value_traits) {
	TEST_MARKER();
	
	using namespace test_value_traits_ns;

	test_list<legacy_list>();
	test_list<legacy_slist>();
	test_list<trivial_legacy_list>();
	test_list<trivial_legacy_slist>();
}

namespace test_value_traits_ns {
	
struct simple_node {
	simple_node* next;
	simple_node* prev;
};

struct base_1 {};

struct base_2 {};

struct value_1 : public base_1, simple_node {
	int id;
};

struct value_2 : public base_1, base_2, simple_node {
	float id;
};

struct simple_node_traits {
	using node = simple_node;
	using node_ptr = simple_node*;
	using const_node_ptr = const simple_node*;
	static node_ptr get_next(const_node_ptr n) {
		return n->next;
	}
	static void set_next(node_ptr n, node_ptr next) {
		n->next = next;
	}
	static node_ptr get_previous(const_node_ptr n) {
		return n->prev;
	}
	static void set_previous(node_ptr n, node_ptr prev) {
		n->prev = prev;
	}
};

template <typename value_t>
struct simple_value_traits {
	using node_traits = simple_node_traits;
	using node_ptr = simple_node_traits::node_ptr;
	using const_node_ptr = simple_node_traits::const_node_ptr;
	using value_type = value_t;
	using pointer = value_t*;
	using const_pointer = const value_t*;
	static const bi::link_mode_type link_mode = bi::normal_link;
	static node_ptr to_node_ptr(value_type& value) {
		return node_ptr{&value};
	}
	static const_node_ptr to_node_ptr(const value_type& value) {
		return const_node_ptr{&value};
	}
	static pointer to_value_ptr(node_ptr n) {
		return static_cast<pointer>(n);
	}
	static const_pointer to_value_ptr(const_node_ptr n) {
		return static_cast<const_pointer>(n);
	}
};

struct derivation_value_1 : public base_1, simple_node {
	int id;
	simple_node n;
};

struct derivation_value_2 : public base_1, base_2, simple_node {
	float id;
	simple_node n;
};

using derivation_simple_value_traits_1 = bi::derivation_value_traits<derivation_value_1, simple_node_traits, bi::normal_link>;
using derivation_simple_value_traits_2 = bi::derivation_value_traits<derivation_value_2, simple_node_traits, bi::normal_link>;

using simple_value_traits_option_1 = bi::value_traits<simple_value_traits<value_1>>;
using simple_value_traits_option_2 = bi::value_traits<simple_value_traits<value_2>>;
using derivation_simple_value_traits_option_1 = bi::value_traits<derivation_simple_value_traits_1>;
using derivation_simple_value_traits_option_2 = bi::value_traits<derivation_simple_value_traits_2>;

using simple_list_1 = bi::list<value_1, simple_value_traits_option_1>;
using simple_list_2 = bi::list<value_2, simple_value_traits_option_2>;
using derivation_simple_list_1 = bi::list<derivation_value_1, derivation_simple_value_traits_option_1>;
using derivation_simple_list_2 = bi::list<derivation_value_2, derivation_simple_value_traits_option_2>;

}

BOOST_AUTO_TEST_CASE(test_derivation_value_traits) {
	TEST_MARKER();

	using namespace test_value_traits_ns;

	value_1 v_1;
	simple_list_1 sl_1;
	sl_1.push_back(v_1);
	BOOST_CHECK(&v_1 == &sl_1.front());

	derivation_value_1 dv_1;
	derivation_simple_list_1 dsl_1;
	dsl_1.push_back(dv_1);
	BOOST_CHECK(&dv_1 == &dsl_1.front());

	value_2 v_2;
	simple_list_2 sl_2;
	sl_2.push_back(v_2);
	BOOST_CHECK(&v_2 == &sl_2.front());

	derivation_value_2 dv_2;
	derivation_simple_list_2 dsl_2;
	dsl_2.push_back(dv_2);
	BOOST_CHECK(&dv_2 == &dsl_2.front());
}

namespace test_value_traits_ns {

using id_t = int;

struct stateful_value_traits {
	using node_traits = bi::list_node_traits<void*>;
	using node = node_traits::node;
	using node_ptr = node*;
	using const_node_ptr = const node*;
	using value_type = id_t;
	using pointer = id_t*;
	using const_pointer = const id_t*;
	static const bi::link_mode_type link_mode = bi::normal_link;
	stateful_value_traits(pointer i, node_ptr n) : ids{i}, nodes{n} {}
	node_ptr to_node_ptr(value_type& value) const {
		return this->nodes + (&value - this->ids);
	}
	const_node_ptr to_node_ptr(const value_type& value) const {
		return this->nodes + (&value - this->ids);
	}
	pointer to_value_ptr(node_ptr n) const {
		return this->ids + (n - this->nodes);
	}
	const_pointer to_value_ptr(const_node_ptr n) const {
		return this->ids + (n - this->nodes);
	}
private:
	pointer ids;
	node_ptr nodes;
};

}

BOOST_AUTO_TEST_CASE(test_stateful_value_traits) {
	TEST_MARKER();

	using namespace test_value_traits_ns;
	using namespace boost::intrusive;
	using list = list<id_t, value_traits<stateful_value_traits>>;

	id_t ids[100];
	list_node_traits<void*>::node nodes[100];
	for (int i = 0; i < 100; i++) {
		ids[i] = i;
	}
	list l{stateful_value_traits{ids, nodes}};
	for (auto& id : ids) {
		l.push_back(id);
	}

	list::const_iterator it{l.cbegin()}, itend{l.cend()};
	id_t* id{&ids[0]};
	for (; it != itend; it++, id++) {
		BOOST_CHECK(&*it == &*id);
	}
}