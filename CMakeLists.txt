cmake_minimum_required(VERSION 3.7)

project(HomomorphicFilter)

find_package(OpenCV 4 REQUIRED)
if (OpenCV_FOUND)
  message(STATUS "OpenCV 4 found")
else()
  message(FATAL_ERROR "OpenCV not found!")
endif()

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-pedantic)
add_compile_options(-std=c++17)

# Interactive demo app
set(Demo_SOURCES
    HomomorphicFilter.cpp
    bin/demo/main.cpp)

add_executable(HomomorphicFilterDemo ${Demo_SOURCES})    
target_link_libraries(HomomorphicFilterDemo ${OpenCV_LIBS})
target_include_directories(HomomorphicFilterDemo
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS HomomorphicFilterDemo DESTINATION bin)

# Command line interface
set(CLI_SOURCES
    HomomorphicFilter.cpp
    bin/cli/main.cpp)

add_executable(HomomorphicFilterCLI ${CLI_SOURCES})    
target_link_libraries(HomomorphicFilterCLI ${OpenCV_LIBS})
target_include_directories(HomomorphicFilterCLI
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS HomomorphicFilterCLI DESTINATION bin)
