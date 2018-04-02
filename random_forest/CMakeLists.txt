include_directories(${CMAKE_SOURCE_DIR}/random_forest)

set(SRCS
        src/decisiontrees/Node.cpp)
set(HDRS include/decisiontrees/Node.h
         include/decisiontrees/NodeAlgorithms.h)



#add_library(random_forest  SHARED ${SRCS} ${HDRS})
add_library(random_forest  STATIC ${SRCS} ${HDRS})
