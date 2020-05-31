cmake_minimum_required(VERSION 3.13)

project(Chess)

find_package(Curses REQUIRED)
#heders
include_directories(${CURSES_INCLUDE_DIR})

#sources
file(GLOB SOURCES "src/*.cc")


add_executable(Chess ${SOURCES})
target_link_libraries(Chess ${CURSES_LIBRARIES})