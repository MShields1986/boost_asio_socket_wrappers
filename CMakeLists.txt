cmake_minimum_required(VERSION 3.16..3.24)

project(simple_boost_asio_sockets
    VERSION 0.0.1
    DESCRIPTION "Simple wrapper classes around common Boost ASIO socket interfaces."
    LANGUAGES CXX)

add_compile_options(-std=c++17)

# Set build type to Release if not already set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Set project wide settings
add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup INTERFACE -Wall -Wpedantic -Wextra)
target_compile_features(cxx_setup INTERFACE cxx_std_17)
target_include_directories(cxx_setup INTERFACE ${PROJECT_SOURCE_DIR})

find_package(Boost 1.71.0 REQUIRED COMPONENTS system)

include_directories(include)

#set(SRC_FILES
#    src/tcp_server_boost.cpp
#    src/tcp_client_boost.cpp
#    src/udp_client_boost.cpp
#)

#add_library(simple_boost_asio_sockets src/tcp_server_boost.cpp)

add_library(simple_tcp_server_boost src/tcp_server_boost.cpp)
add_library(simple_tcp_client_boost src/tcp_client_boost.cpp)
add_library(simple_udp_client_boost src/udp_client_boost.cpp)

target_link_libraries(simple_tcp_server_boost PUBLIC cxx_setup Boost::system)
target_link_libraries(simple_tcp_client_boost PUBLIC cxx_setup Boost::system)
target_link_libraries(simple_udp_client_boost PUBLIC cxx_setup Boost::system)
