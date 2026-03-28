find_package( GTest REQUIRED )

set( SOURCES_TESTS 
        testmain.cpp
        ${CMAKE_SOURCE_DIR}/src/ipWorker.cpp 
        ${CMAKE_SOURCE_DIR}/src/parser.cpp 
)


add_executable( unit_tests ${SOURCES_TESTS} ${LIB_SOURCES} )

target_include_directories( unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include )

target_link_libraries( unit_tests GTest::gtest GTest::gtest )

add_test( NAME AllIpWorkerTests COMMAND unit_tests )