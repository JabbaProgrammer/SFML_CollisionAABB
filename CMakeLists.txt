cmake_minimum_required(VERSION 3.23)
project(SFML_CollisionDetection)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(SFML_CollisionDetection main.cpp)

include(FindPkgConfig)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)