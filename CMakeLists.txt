#Version of cmake
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11) #c++11?

# .cpp files
set(SOURCES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Enable additional warnings and debug mode
set (CMAKE_CXX_FLAGS "-g -W -pedantic")

#folder with your header (.h) files
include_directories(src)

# Set "a" as output's name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")