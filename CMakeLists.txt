cmake_minimum_required(VERSION 3.10)

project(basic_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_INCLUDE_DIR "C:/local/boost_1_75_0")
include_directories(${Boost_INCLUDE_DIR})

include_directories("${CMAKE_SOURCE_DIR}/include")

# ================================================================================
# 1. TECHNIQUES
# ================================================================================

# ========================================
# 1.1. TEMPLATE METAPROGRAMMING (TMP)
# ========================================

# 1.1.1. MODERN C++ DESIGN: GENERIC PROGRAMMING AND DESIGN PATTERNS APPLIED
# Link: https://g.co/kgs/NaxxkE
add_executable(from_modern_cpp_design src/books/from_modern_cpp_design.cpp)

# ========================================
# 1.2. MULTI-THREADING
# ========================================

# 1.2.1. CONCURRENCY WITH MODERN C++
add_executable(concurrency_atomic_flag "src/books/concurrency_with_modern_cpp/memory_model/atomic_flag.cpp")
add_executable(concurrency_atomic "src/books/concurrency_with_modern_cpp/memory_model/atomic.cpp")
add_executable(concurrency_memory_order_sequential_consistency "src/books/concurrency_with_modern_cpp/memory_model/memory_order_sequential_consistency.cpp")
add_executable(concurrency_memory_order_acquire_release "src/books/concurrency_with_modern_cpp/memory_model/memory_order_acquire_release.cpp")
add_executable(concurrency_memory_order_consume_release "src/books/concurrency_with_modern_cpp/memory_model/memory_order_consume_release.cpp")
add_executable(concurrency_memory_order_relaxed "src/books/concurrency_with_modern_cpp/memory_model/memory_order_relaxed.cpp")

add_executable(concurrency_thread "src/books/concurrency_with_modern_cpp/multithreading/thread.cpp")
add_executable(concurrency_mutex "src/books/concurrency_with_modern_cpp/multithreading/mutex.cpp")
add_executable(concurrency_lock "src/books/concurrency_with_modern_cpp/multithreading/lock.cpp")
add_executable(concurrency_thread_safe_initialisation "src/books/concurrency_with_modern_cpp/multithreading/thread_safe_initialisation.cpp")
add_executable(concurrency_thread_local "src/books/concurrency_with_modern_cpp/multithreading/thread_local.cpp")
add_executable(concurrency_condition_variable "src/books/concurrency_with_modern_cpp/multithreading/condition_variable.cpp")
add_executable(concurrency_task "src/books/concurrency_with_modern_cpp/multithreading/task.cpp")

add_executable(concurrency_parallel_stl "src/books/concurrency_with_modern_cpp/parallel_stl/parallel_stl.cpp")

add_executable(concurrency_scoped_lock "src/books/concurrency_with_modern_cpp/synchronisation_patterns/scoped_lock.cpp")
add_executable(concurrency_strategized_lock "src/books/concurrency_with_modern_cpp/synchronisation_patterns/strategized_lock.cpp")
add_executable(concurrency_thread_safe_interface "src/books/concurrency_with_modern_cpp/synchronisation_patterns/thread_safe_interface.cpp")

add_executable(concurrency_active_object "src/books/concurrency_with_modern_cpp/concurrent_architecture/active_object.cpp")
add_executable(concurrency_monitor_object "src/books/concurrency_with_modern_cpp/concurrent_architecture/monitor_object.cpp")

add_executable(concurrency_sum_of_vector "src/books/concurrency_with_modern_cpp/sum_of_vector.cpp")

# ================================================================================
# 2. LIBS
# ================================================================================

# ========================================
# 2.1. STL
# ========================================

add_executable(stl_algorithms_test src/libs/stl/stl_algorithms_test.cpp)
add_executable(cpp17_test src/libs/stl/cpp17_test.cpp)
add_executable(cpp11_concurrency_test src/libs/stl/cpp11_concurrency_test.cpp)

# ========================================
# 2.2. BOOST
# ========================================

add_executable(boost_intrusive_test src/libs/boost/boost_intrusive_test.cpp)

# ========================================
# 2.3. OTHERS
# ========================================

# 2.3.1. RANGE-V3
add_executable(ranges_test src/libs/others/ranges_test.cpp)
target_include_directories(ranges_test PRIVATE "${CMAKE_SOURCE_DIR}/modules/range-v3/include")
target_link_directories(ranges_test INTERFACE range-v3)

# 2.3.2. TINYTOML
add_executable(toml_test src/libs/others/toml_test.cpp)
target_include_directories(toml_test PRIVATE "${CMAKE_SOURCE_DIR}/modules/tinytoml/include")

# ================================================================================
# 3. SITES
# ================================================================================

# ========================================
# 3.1. GEEKSFORGEEKS
# ========================================

# 3.1.1. DATA STRUCTURES
add_executable(array_test src/sites/geeksforgeeks/data_structures/array_test.cpp)
add_executable(singly_linked_list_test src/sites/geeksforgeeks/data_structures/singly_linked_list_test.cpp)
add_executable(doubly_linked_list_test src/sites/geeksforgeeks/data_structures/doubly_linked_list_test.cpp)
add_executable(circular_linked_list_test src/sites/geeksforgeeks/data_structures/circular_linked_list_test.cpp)
add_executable(binary_tree_test src/sites/geeksforgeeks/data_structures/binary_tree_test.cpp)

# 3.1.2. ALGORITHMS
add_executable(back_tracking_test src/sites/geeksforgeeks/algorithms/back_tracking_test.cpp)

# ========================================
# 3.2. LEETCODE
# ========================================

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

# ========================================
# 3.3. REFACTORING.GURU
# ========================================

add_executable(refactoring_guru_abstract_factory "src/sites/refactoring_guru/creational/abstract_factory.cpp")
add_executable(refactoring_guru_builder "src/sites/refactoring_guru/creational/builder.cpp")
add_executable(refactoring_guru_factory_method "src/sites/refactoring_guru/creational/factory_method.cpp")
add_executable(refactoring_guru_prototype "src/sites/refactoring_guru/creational/prototype.cpp")
add_executable(refactoring_guru_singleton "src/sites/refactoring_guru/creational/singleton.cpp")

add_executable(refactoring_guru_adapter "src/sites/refactoring_guru/structural/adapter.cpp")
add_executable(refactoring_guru_bridge "src/sites/refactoring_guru/structural/bridge.cpp")
add_executable(refactoring_guru_composite "src/sites/refactoring_guru/structural/composite.cpp")
add_executable(refactoring_guru_decorator "src/sites/refactoring_guru/structural/decorator.cpp")
add_executable(refactoring_guru_facade "src/sites/refactoring_guru/structural/facade.cpp")
add_executable(refactoring_guru_flyweight "src/sites/refactoring_guru/structural/flyweight.cpp")
add_executable(refactoring_guru_proxy "src/sites/refactoring_guru/structural/proxy.cpp")

add_executable(refactoring_guru_chain_of_responsibility "src/sites/refactoring_guru/behavioral/chain_of_responsibility.cpp")
add_executable(refactoring_guru_command "src/sites/refactoring_guru/behavioral/command.cpp")
add_executable(refactoring_guru_iterator "src/sites/refactoring_guru/behavioral/iterator.cpp")
add_executable(refactoring_guru_mediator "src/sites/refactoring_guru/behavioral/mediator.cpp")
add_executable(refactoring_guru_memento "src/sites/refactoring_guru/behavioral/memento.cpp")
add_executable(refactoring_guru_observer "src/sites/refactoring_guru/behavioral/observer.cpp")
add_executable(refactoring_guru_state "src/sites/refactoring_guru/behavioral/state.cpp")
add_executable(refactoring_guru_strategy "src/sites/refactoring_guru/behavioral/strategy.cpp")
add_executable(refactoring_guru_template_method "src/sites/refactoring_guru/behavioral/template_method.cpp")
add_executable(refactoring_guru_visitor "src/sites/refactoring_guru/behavioral/visitor.cpp")

add_subdirectory(modules)