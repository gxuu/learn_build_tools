cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
project(lord LANGUAGES CXX VERSION 0.1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(
	  -std=c++2b
	  -Wall
	  -Wextra
	  -Werror
	  -fconcepts-diagnostics-depth=2
	)
endif()

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(main)

add_executable(test_concept)

target_include_directories(main PRIVATE include)

find_package(normal REQUIRED)
find_package(ZLIB REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
find_package(ffmpeg REQUIRED)

target_link_libraries(main normal::normal)
target_link_libraries(main ZLIB::ZLIB)
target_link_libraries(main nlohmann_json::nlohmann_json)
target_link_libraries(main spdlog::spdlog)
target_link_libraries(main ffmpeg::avutil)
target_link_libraries(main ffmpeg::swscale)
target_link_libraries(main ffmpeg::swresample)
target_link_libraries(main ffmpeg::postproc)
target_link_libraries(main ffmpeg::avcodec)
target_link_libraries(main ffmpeg::avformat)
target_link_libraries(main ffmpeg::avfilter)
target_link_libraries(main ffmpeg::avdevice)

add_subdirectory(src)

