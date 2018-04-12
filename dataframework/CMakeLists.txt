project(dataframework)

include_directories(${CMAKE_SOURCE_DIR}/random_forest)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package( Boost REQUIRED COMPONENTS program_options regex )

include_directories( ${Boost_INCLUDE_DIRS} )

set(SRCS
        src/hierarchy/Node.cpp
        src/data/NumericDefaults.cpp)

set(HDRS include/hierarchy/Node.h
        include/hierarchy/NodeAlgorithms.h
         include/data/Frame.h
         include/data/Series.h
        include/data/NumericDefaults.h)



#add_library(dataframework  SHARED ${SRCS} ${HDRS})
add_library(datafamework  STATIC ${SRCS} ${HDRS})
