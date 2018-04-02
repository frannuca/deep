cmake_minimum_required(VERSION 3.10)
project(deep)


set(CMAKE_CXX_STANDARD 11)

configure_file(config.h.in config.h @ONLY)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(src include)

set(SRCS
        src/main.cpp
        src/decisiontrees/Node.cpp)
set(HDRS include/decisiontrees/Node.h
         include/decisiontrees/NodeAlgorithms.h)


find_package(dlib REQUIRED)

ADD_EXECUTABLE(deep  ${SRCS} ${HDRS})

target_link_libraries(deep dlib::dlib)