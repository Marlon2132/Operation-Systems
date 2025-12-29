cmake_minimum_required(VERSION 3.16)

project(Kollok2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/mainwindow.cpp
    ${SRC_ROOT}/mainwindow.h
    ${SRC_ROOT}/mainwindow.ui

    ${SRC_ROOT}/task.h
    ${SRC_ROOT}/task.cpp

    ${SRC_ROOT}/taskstore.h
    ${SRC_ROOT}/taskstore.cpp

    ${SRC_ROOT}/todoserver.h
    ${SRC_ROOT}/todoserver.cpp

    ${SRC_ROOT}/apiclient.h
    ${SRC_ROOT}/apiclient.cpp
)

set(THIRDPARTY_DIR ${SRC_ROOT})
if(EXISTS ${THIRDPARTY_DIR}/httplib.h)
    list(APPEND PROJECT_SOURCES ${THIRDPARTY_DIR}/httplib.h)
    set(HAS_HTTPLIB TRUE)
else()
    set(HAS_HTTPLIB FALSE)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        server_main.cpp
    )
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SRC_ROOT}
)

if(HAS_HTTPLIB)
    target_include_directories(${PROJECT_NAME} PRIVATE ${THIRDPARTY_DIR})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

add_executable(Kollok2_server server_main.cpp todoserver.cpp taskstore.cpp task.cpp)
target_link_libraries(Kollok2_server PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
target_include_directories(Kollok2_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

