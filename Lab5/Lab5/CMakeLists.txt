cmake_minimum_required(VERSION 3.12)

project(Lab5 LANGUAGES CXX)

# Используем C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Общая папка с исходниками (текущая)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Списки исходников
set(SERVER_SOURCES
    ${SRC_DIR}/Server.cpp
    ${SRC_DIR}/file_utils.cpp
    ${SRC_DIR}/lock_utils.cpp
    ${SRC_DIR}/pipe_utils.cpp
    ${SRC_DIR}/proc_utils.cpp
)

set(CLIENT_SOURCES
    ${SRC_DIR}/Client.cpp
    ${SRC_DIR}/file_utils.cpp
    ${SRC_DIR}/lock_utils.cpp
    ${SRC_DIR}/pipe_utils.cpp
    ${SRC_DIR}/proc_utils.cpp
)

# Создаём два исполняемых файла: Server и Client
add_executable(Server ${SERVER_SOURCES})
add_executable(Client ${CLIENT_SOURCES})

# Указываем директорию с заголовками (если заголовки в корне проекта)
target_include_directories(Server PRIVATE ${SRC_DIR})
target_include_directories(Client PRIVATE ${SRC_DIR})

# Опции компилятора для разных компиляторов
if (MSVC)
  target_compile_options(Server PRIVATE /W4 /EHsc)
  target_compile_options(Client PRIVATE /W4 /EHsc)
else()
  target_compile_options(Server PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(Client PRIVATE -Wall -Wextra -Wpedantic)
  # Если используете pthreads на POSIX-системах, раскомментируйте:
  # find_package(Threads REQUIRED)
  # target_link_libraries(Server PRIVATE Threads::Threads)
  # target_link_libraries(Client PRIVATE Threads::Threads)
endif()
