cmake_minimum_required(VERSION 3.14)
project(Kollok1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(Kollok1Lib STATIC
  FactorialClass.cpp
  VecClass.cpp
  LinkedList.cpp
)
target_compile_definitions(Kollok1Lib PRIVATE BUILDING_FOR_TESTS)
target_include_directories(Kollok1Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Kollok1
  Kollok1.cpp
  Kollok1.h
)
target_link_libraries(Kollok1
  PRIVATE
    Kollok1Lib
)

add_executable(Kollok1Tests
  tests/test.cpp
)

target_link_libraries(Kollok1Tests
  PRIVATE
    Kollok1Lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Kollok1Tests)
