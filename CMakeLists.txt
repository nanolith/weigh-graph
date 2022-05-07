cmake_policy(SET CMP0048 NEW)
PROJECT(weightgraph VERSION 0.1.0)

string(REPLACE "." ";" WEIGHTGRAPH_VERSION_LIST "${CMAKE_PROJECT_VERSION}")
list(GET WEIGHTGRAPH_VERSION_LIST 0 WEIGHTGRAPH_VERSION_MAJOR)
list(GET WEIGHTGRAPH_VERSION_LIST 1 WEIGHTGRAPH_VERSION_MINOR)
list(GET WEIGHTGRAPH_VERSION_LIST 2 WEIGHTGRAPH_VERSION_REL)

cmake_minimum_required(VERSION 3.10)

INCLUDE(CheckSymbolExists)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

#expat support
find_package(EXPAT 2.4.8 MODULE REQUIRED)
#rcpr package
find_package(rcpr 0.2.1 REQUIRED)

#Build config.h
configure_file(config.h.cmake include/weightgraph/config.h)

#includes
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

#source files
AUX_SOURCE_DIRECTORY(src/main WEIGHTGRAPH_MAIN_SOURCES)
SET(WEIGHTGRAPH_SOURCES ${WEIGHTGRAPH_MAIN_SOURCES})

ADD_EXECUTABLE(weightgraph ${WEIGHTGRAPH_SOURCES})

TARGET_COMPILE_OPTIONS(
    weightgraph PRIVATE -O2 -Wall -Werror -Wextra -Wpedantic ${RCPR_CFLAGS}
                     -Wno-unused-command-line-argument)
TARGET_LINK_LIBRARIES(
    weightgraph PUBLIC EXPAT::EXPAT ${RCPR_LDFLAGS})

#Install binary
INSTALL(TARGETS weightgraph
        RUNTIME DESTINATION bin)
