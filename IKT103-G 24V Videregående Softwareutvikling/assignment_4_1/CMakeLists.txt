cmake_minimum_required(VERSION 3.27)
project(assignment_4_1)

set(CMAKE_CXX_STANDARD 17)

find_package(cpprestsdk REQUIRED)

add_executable(assignment_4_1 main.cpp)

TARGET_LINK_LIBRARIES(assignment_4_1 PRIVATE cpprestsdk::cpprest)


if (LINUX)
    TARGET_LINK_LIBRARIES(assignment_4_1 PRIVATE crypto)
endif (LINUX)
if (UNIX)
    TARGET_LINK_LIBRARIES(assignment_4_1 PRIVATE crypto)
endif (UNIX)