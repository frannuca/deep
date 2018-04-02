cmake_minimum_required(VERSION 3.10)
project(deep)
set(CMAKE_CXX_STANDARD 11)


add_subdirectory(random_forest)
add_subdirectory(tests)

enable_testing()
ADD_TEST(TREECHECK tests/treecheck)