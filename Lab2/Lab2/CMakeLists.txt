cmake_minimum_required(VERSION 3.14)
project(Lab2Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================================
# 1) Подтягиваем GoogleTest «внутрь» проекта
# ========================================
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
# на Windows принудительно используем тот же CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ========================================
# 2) Собираем библиотеку из Lab2.cpp (без main)
# ========================================
add_library(Lab2Lib STATIC
  Lab2.cpp
)
# этот макрос «вырубит» main() внутри Lab2.cpp,
# оставив только MinMaxProc/AverageProc в библиотеке
target_compile_definitions(Lab2Lib PRIVATE BUILDING_FOR_TESTS)
target_include_directories(Lab2Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ========================================
# 3) Собираем приложение Lab2 с реальным main()
# ========================================
add_executable(Lab2
  Lab2.cpp    # здесь main() будет, потому что BUILDING_FOR_TESTS не задан
  Lab2.h
)
# WinAPI (CreateThread, Sleep) в MSVC линкуются автоматически

# ========================================
# 4) Собираем тесты — только test.cpp, без вашего main()
# ========================================
add_executable(Lab2Tests
  tests/test.cpp
)
target_link_libraries(Lab2Tests
  PRIVATE
    Lab2Lib          # логика потоков + структуры
    GTest::gtest_main
)
# чтобы CTest видел и запускал наши тесты
include(GoogleTest)
gtest_discover_tests(Lab2Tests)
