project(cdeedle)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package( Boost REQUIRED COMPONENTS program_options regex )

include_directories( ${Boost_INCLUDE_DIRS}  ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCS
        src/Node.cpp
        src/Frame.cpp
        )

set(HDRS include/Node.h
         include/NodeAlgorithms.h
        include/Frame.h
        )



#add_library(cdeedle  SHARED ${SRCS} ${HDRS})
add_library(cdeedle  STATIC  ${SRCS} ${HDRS})
