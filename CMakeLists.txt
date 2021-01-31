cmake_minimum_required(VERSION 3.10)

project(basic_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_INCLUDE_DIR "C:/local/boost_1_75_0")
include_directories(${Boost_INCLUDE_DIR})

include_directories("${CMAKE_SOURCE_DIR}/include")

# STL

add_executable(stl_algorithms_test src/stl/stl_algorithms_test.cpp)

add_executable(cpp17_test src/stl/cpp17_test.cpp)

# BOOST

add_executable(boost_intrusive_test src/boost/boost_intrusive_test.cpp)

# OTHERS

add_executable(ranges_test src/others/ranges_test.cpp)
target_include_directories(ranges_test PRIVATE "${CMAKE_SOURCE_DIR}/modules/range-v3/include")
target_link_directories(ranges_test INTERFACE range-v3)

add_executable(toml_test src/others/toml_test.cpp)
target_include_directories(toml_test PRIVATE "${CMAKE_SOURCE_DIR}/modules/tinytoml/include")

add_subdirectory(modules)