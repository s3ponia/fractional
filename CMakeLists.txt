cmake_minimum_required(VERSION 3.15)
project(FractionNumber)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(FractionNumber include/Fraction.cpp)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(test1 tests/test_file.cpp)

target_include_directories(test1 PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_definitions(test1 PRIVATE "BOOST_TEST_DYN_LINK=1")

target_link_libraries(test1 ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(TEST1 test1 COMMAND test_executable)

set(FRACTIONAL_SOURCES include/fractional.hpp)