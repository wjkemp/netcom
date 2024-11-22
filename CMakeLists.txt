cmake_minimum_required(VERSION 3.25)

project(netcom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Network SerialPort REQUIRED)

set(SOURCES
    source/main.cpp
    source/server.cpp
    source/serial.cpp
    source/connection.cpp
)

add_executable(
    netcom
    ${SOURCES}
)

target_include_directories(netcom PRIVATE
    ./source/
)

target_link_libraries(netcom Qt5::Network Qt5::SerialPort)
