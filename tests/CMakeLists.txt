enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/cdeedle/include)
include_directories(${CMAKE_SOURCE_DIR}/GP/include)

#I like to keep test files in a separate src directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR:         " ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR :         " ${CMAKE_CURRENT_BINARY_DIR} )

#Run through each src
foreach(testSrc ${TEST_SRCS})
    MESSAGE( STATUS "Adding file -------------------------" ${testSrc} )
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc})

    link_directories(/usr/local/lib)
    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES} cdeedle GP boost_serialization armadillo nlopt)

    #I like to move testing binaries into a testBin directory
    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)


    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)
