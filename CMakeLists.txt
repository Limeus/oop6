cmake_minimum_required(VERSION 3.20)

project(Lab6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Google Test with FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# Prevent Google Test from overriding project compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Define source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# --- Build main executable ---
add_executable(lab6
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${SRC_DIR}/dragon.cpp
    ${SRC_DIR}/knight.cpp
    ${SRC_DIR}/method.cpp
    ${SRC_DIR}/npc.cpp
    ${SRC_DIR}/princess.cpp
)
target_include_directories(lab6 PRIVATE ${INCLUDE_DIR})

# --- Build test executable ---
enable_testing()

add_executable(runTests
    ${TEST_DIR}/tests.cpp
    ${SRC_DIR}/dragon.cpp
    ${SRC_DIR}/knight.cpp
    ${SRC_DIR}/method.cpp
    ${SRC_DIR}/npc.cpp
    ${SRC_DIR}/princess.cpp
)

# Link Google Test libraries
target_link_libraries(runTests PRIVATE gtest_main)
target_include_directories(runTests PRIVATE ${INCLUDE_DIR} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/googletest/include)

# Add tests to CTest
add_test(NAME Lab6Tests COMMAND runTests)
