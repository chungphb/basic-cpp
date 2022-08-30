cmake_minimum_required(VERSION 3.10)

project(basic_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_INCLUDE_DIR "C:/local/boost_1_75_0")
include_directories(${Boost_INCLUDE_DIR})

include_directories("${CMAKE_SOURCE_DIR}/include")

# 1. TECHNIQUES

# 1.1. TEMPLATE METAPROGRAMMING (TMP)

# 1.1.1. MODERN C++ DESIGN: GENERIC PROGRAMMING AND DESIGN PATTERNS APPLIED
# Link: https://g.co/kgs/NaxxkE

add_executable(from_modern_cpp_design src/books/from_modern_cpp_design.cpp)

# 2. LIBS

# 2.1. STL

add_executable(stl_algorithms_test src/libs/stl/stl_algorithms_test.cpp)

add_executable(cpp17_test src/libs/stl/cpp17_test.cpp)

add_executable(cpp11_concurrency_test src/libs/stl/cpp11_concurrency_test.cpp)

# 2.2. BOOST

add_executable(boost_intrusive_test src/libs/boost/boost_intrusive_test.cpp)

# 2.3. OTHERS

# 2.3.1. RANGE-V3
add_executable(ranges_test src/libs/others/ranges_test.cpp)
target_include_directories(ranges_test PRIVATE "${CMAKE_SOURCE_DIR}/modules/range-v3/include")
target_link_directories(ranges_test INTERFACE range-v3)

# 2.3.2. TINYTOML
add_executable(toml_test src/libs/others/toml_test.cpp)
target_include_directories(toml_test PRIVATE "${CMAKE_SOURCE_DIR}/modules/tinytoml/include")

# 3. SITES

# 3.1. GEEKSFORGEEKS

# 3.1.1. DATA STRUCTURES
add_executable(array_test src/sites/geeksforgeeks/data_structures/array_test.cpp)
add_executable(singly_linked_list_test src/sites/geeksforgeeks/data_structures/singly_linked_list_test.cpp)
add_executable(doubly_linked_list_test src/sites/geeksforgeeks/data_structures/doubly_linked_list_test.cpp)
add_executable(circular_linked_list_test src/sites/geeksforgeeks/data_structures/circular_linked_list_test.cpp)
add_executable(binary_tree_test src/sites/geeksforgeeks/data_structures/binary_tree_test.cpp)

# 3.1.2. ALGORITHMS
add_executable(back_tracking_test src/sites/geeksforgeeks/algorithms/back_tracking_test.cpp)

# 3.2. LEETCODE

# 3.1.1. DATA STRUCTURES
add_executable(leetcode_linked_list_test "src/sites/leetcode/data_structures/linked_list_test.cpp")
add_executable(leetcode_hash_test "src/sites/leetcode/data_structures/hash_test.cpp")
add_executable(leetcode_heap_test "src/sites/leetcode/data_structures/heap_test.cpp")

# 3.2.2. ALGORITHMS
add_executable(leetcode_two_pointers_test "src/sites/leetcode/algorithms/two_pointers_test.cpp")
add_executable(leetcode_bfs_test "src/sites/leetcode/algorithms/bfs_test.cpp")
add_executable(leetcode_dfs_test "src/sites/leetcode/algorithms/dfs_test.cpp")
add_executable(leetcode_binary_search_test "src/sites/leetcode/algorithms/binary_search_test.cpp")

# 3.2.3. RANDOM
add_executable(leetcode_random_test "src/sites/leetcode/random_test.cpp")

add_subdirectory(modules)