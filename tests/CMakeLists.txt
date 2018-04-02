

include_directories(${CMAKE_SOURCE_DIR}/tests  ${CMAKE_SOURCE_DIR}/random_forest/include) # include files from ProjectB

add_executable(treecheck main.cpp)


MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_SOURCE_DIR} )
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR :         " ${CMAKE_CURRENT_BINARY_DIR} )
