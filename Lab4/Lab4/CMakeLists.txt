cmake_minimum_required(VERSION 3.12)
project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека utils
add_library(utils STATIC
    utils/message_queue.cpp
    utils/input_parsing.cpp
)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utils)

# Два отдельных исполняемых файла
add_executable(Receiver Receiver.cpp)
target_link_libraries(Receiver PRIVATE utils)

add_executable(Sender Sender.cpp)
target_link_libraries(Sender PRIVATE utils)
