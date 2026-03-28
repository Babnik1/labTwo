cmake_minimum_required( VERSION 3.12 )
option( ENABLE_TESTS "Enable tests" ON )

project( PacketsSorter VERSION 1.0 LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( SOURCES 
        src/parser.cpp
        src/ipWorker.cpp
        src/main.cpp 
)

add_executable( ipFilter ${SOURCES} )

target_include_directories( ipFilter PRIVATE include )

set_target_properties( ipFilter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )

if( ENABLE_TESTS )
    enable_testing()
    add_subdirectory( tests )
endif()
