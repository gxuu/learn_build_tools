
cmake_minimum_required(VERSION 3.27.2)
# set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(normal CXX)

add_library(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(include)
target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME})
