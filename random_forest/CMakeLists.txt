include_directories(${CMAKE_SOURCE_DIR}/random_forest)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )

set(SRCS
        src/decisiontrees/Node.cpp)
set(HDRS include/decisiontrees/Node.h
         include/decisiontrees/NodeAlgorithms.h)



#add_library(random_forest  SHARED ${SRCS} ${HDRS})
add_library(random_forest  STATIC ${SRCS} ${HDRS})
