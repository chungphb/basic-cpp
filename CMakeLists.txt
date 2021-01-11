cmake_minimum_required(VERSION 3.10)

project(basic_cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cpp17_test src/cpp17_test.cpp)

add_executable(toml_test src/toml_test.cpp)
target_include_directories(toml_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/modules/tinytoml/include")

add_subdirectory(modules)