# Get project name from folder name and set it
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})


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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/cmake")
find_package(SFML 2.5 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Set "a" as output's name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")