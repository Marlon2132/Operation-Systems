# CMakeList.txt: проект CMake для Lab3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lab3 "Lab3.cpp" "Lab3.h" "MarkerControl.cpp" "MarkerControl.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab3 PROPERTY CXX_STANDARD 11)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

set(BOOST_ROOT "C:/local/boost_1_89_0") # Необходимо установить самому, т.к. Git не позволяет закидывать большие файлы
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib64-msvc-14.2")

find_package(Boost 1.89 REQUIRED COMPONENTS thread chrono)

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(Lab3 PRIVATE ${Boost_LIBRARIES})


include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(catch2)

add_executable(runTests
  tests/main.cpp
  tests/tests.cpp
  MarkerControl.cpp
)

target_link_libraries(runTests
  PRIVATE Catch2::Catch2WithMain
  Boost::thread
  Boost::chrono
)

enable_testing()
add_test(NAME all_tests COMMAND runTests)