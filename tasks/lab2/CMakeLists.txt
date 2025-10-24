cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(array_lib
    src/array.cpp
    src/twelve.cpp
)
target_include_directories(array_lib PUBLIC include)

add_executable(lab2_exe main.cpp)
target_link_libraries(lab2_exe PRIVATE array_lib)

enable_testing()
add_executable(tests tests/test_twelve.cpp)
target_link_libraries(tests array_lib gtest_main)
add_test(NAME TwelveTests COMMAND tests)