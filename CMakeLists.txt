cmake_minimum_required(VERSION 3.10)
project(ecc-cpp)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to Debug build if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Find GMP package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMP REQUIRED IMPORTED_TARGET gmp)

# List of source files
set(SOURCES
    src/bigint.cpp
    src/ecc.cpp
    src/ecdh.cpp
    src/blake2b.cpp
    src/ecdsa.cpp
    src/test.cpp
)

# Create executable from sources
add_executable(ecc-cpp ${SOURCES})

# Include directories for header files
target_include_directories(ecc-cpp PRIVATE include)

# Link against GMP library
target_link_libraries(ecc-cpp PkgConfig::GMP)

# Set ecc-cpp as the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ecc-cpp)

# Additional flags for Debug configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
