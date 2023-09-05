cmake_minimum_required(VERSION 3.27.2)

project(normal CXX)

add_library(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(inc)
target_include_directories(${PROJECT_NAME} PUBLIC inc)

install(TARGETS ${PROJECT_NAME})
