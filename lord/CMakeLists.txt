cmake_minimum_required(VERSION 3.27.2)

project(lbt CXX)

add_executable(main)

target_include_directories(main PRIVATE inc)

# https://github.com/conan-io/conan/issues/13513
find_package(normal REQUIRED)
target_link_libraries(main normal::normal)

add_subdirectory(src)
