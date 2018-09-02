cmake_minimum_required(VERSION 2.8.11)

get_filename_component(program ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${program} CXX)

find_package(Boost REQUIRED COMPONENTS
  unit_test_framework  # For unittests
  filesystem  # For filesystem paths
  )

# Use c++17
set(CMAKE_CXX_FLAGS "-std=c++17")

# An alias
set(program_cpp ${program}.cpp)

# Build executable from sources and headers
add_executable(${program}_test ${program}_test.cpp ${program_cpp} ${program}.hpp)
add_executable(${program} main.cpp ${program_cpp} ${program}.hpp)

# We need boost includes
target_include_directories(${program}_test PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(${program} PRIVATE ${Boost_INCLUDE_DIRS})

# We need boost libraries
target_link_libraries(${program}_test ${Boost_LIBRARIES})
target_link_libraries(${program} ${Boost_LIBRARIES})

# Run the tests on every build
add_custom_command(TARGET ${program}_test POST_BUILD COMMAND ${program}_test)
