project(GP)
set(CMAKE_CXX_STANDARD 11)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package( Boost REQUIRED COMPONENTS regex )

include_directories( ${Boost_INCLUDE_DIRS}  ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCS
        src/SquaredExponentialKernel.cpp
        src/GaussianProcess.cpp
        src/IKernel.cpp
        )

set(HDRS include/IKernel.h
         include/SquaredExponentialKernel.h
         include/GaussianProcess.h
        )

add_library(GP  SHARED ${SRCS} ${HDRS})
#add_library(GP  STATIC  ${SRCS} ${HDRS})

#LINK_DIRECTORIES(/usr/local/lib/)
TARGET_LINK_LIBRARIES(GP nlopt)