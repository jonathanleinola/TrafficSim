# Get project name from folder name and set it
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

#Version of cmake
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14) #c++11

file(GLOB SOURCES src/*.cpp)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (${APPLE})
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/cmake")
    find_package(SFML 2.5 REQUIRED network audio graphics window system)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
    endif()
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
if(LINUX)
    set(SFML_INCLUDE_DIR "deps/SFML/include")
    set(SFML_LIBRARY_DIR "deps/SFML/lib")
    set(SFML_DIR "deps/SFML/lib/cmake/SFML")

    link_directories(SFML_LIBRARY_DIR)
    include_directories(SFML_INCLUDE_DIR)

    # .cpp files
    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

    if(SFML_FOUND)
        message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
        message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
        message(STATUS "SFML_VERSION: ${SFML_VERSION}")
    endif()
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
endif ()





# Enable additional warnings and debug mode
set (CMAKE_CXX_FLAGS "-g -W -pedantic")

#folder with your header (.h) files
include_directories(src)


# Set "a" as output's name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")