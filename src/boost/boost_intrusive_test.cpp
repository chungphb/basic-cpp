#define BOOST_TEST_MODULE boost intrusive test
#include <boost/test/included/unit_test.hpp>

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/unordered_set.hpp>

#include <list>
#include <vector>

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