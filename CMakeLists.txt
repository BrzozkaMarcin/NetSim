cmake_minimum_required(VERSION 3.19)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_ID NetSim)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic -errors -Wconversion)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/helpers.cpp
        src/factory.cpp
        )

set(SOURCES_FILES_TESTS
        test/test_package.cpp
        test/test_storage_types.cpp
        test/test_nodes.cpp
        test/test_Factory.cpp
        )

add_executable(NetSim ${SOURCE_FILES} main.cpp)
#add_executable(NetSim main.cpp)
include(SetCommonConfig.cmake)
