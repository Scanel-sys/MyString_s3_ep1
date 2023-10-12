cmake_minimum_required(VERSION 3.26.3)

project(MyString)

# for 1st var
#-------------------------------------------------

# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

#-------------------------------------------------

set(CMAKE_CXX_STANDARD 17)

set(MyStringLibFiles
    src/MyString.h
    src/MyString.cpp
)
add_library(MyStringLib ${MyStringLibFiles})


# Main target
add_executable(
    MyStringExe
    src/main.cpp
    src/MyString.h
    src/MyString.cpp
)

# Test target
add_executable(
    MyStringTests
    tests/MyStringTests.cpp
)

target_include_directories(
    MyStringTests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
    MyStringTests PRIVATE
    gtest gtest_main MyStringLib gmock
)

# for 3rd var
#-------------------------------------------------
# # Lookup for prebuilt gtest
# find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add googletet to the include dirs for the test target
target_include_directories(MyStringTests PRIVATE ${GTEST_INCLUDE_DIRS})

# Link test target against gtest libraries
target_link_libraries(MyStringTests PRIVATE ${GTEST_BOTH_LIBRARIES} MyStringLib gmock)

#-------------------------------------------------


if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # VS Dynamic vs Static Runtimes
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    target_compile_options(
        MyStringExe PRIVATE
        /W4
    )

    target_compile_options(
        MyStringTests PRIVATE
        /W4
    )
else ()
    # flags of high Error alert
    target_compile_options(
        MyStringExe PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # flags of high Error alert
    target_compile_options(
        MyStringTests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
