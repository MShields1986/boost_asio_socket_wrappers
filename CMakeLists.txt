cmake_minimum_required(VERSION 3.0..3.24)

project(SimpleBoostAsioSockets
    VERSION 0.0.1
    DESCRIPTION "Simple wrapper classes around common Boost ASIO socket interfaces."
    LANGUAGES CXX)

add_compile_options(-std=c++17)

# Set build type to Release if not already set
#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
#endif()
#message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Set project wide settings
#add_library(cxx_setup INTERFACE)
#target_compile_options(cxx_setup INTERFACE -Wall -Wpedantic -Wextra)
#target_compile_features(cxx_setup INTERFACE cxx_std_17)
#target_include_directories(cxx_setup INTERFACE ${PROJECT_SOURCE_DIR})

find_package(Boost 1.71.0 REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

include_directories(include)

set(LIBRARY_NAME "BoostSocketWrappers")
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES src/*.cpp include/*.h)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES})
#add_library(${LIBRARY_NAME} SHARED ${SRC_FILES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDE_DIR})

target_link_libraries(${LIBRARY_NAME} PUBLIC Boost::system Threads::Threads)
#target_link_libraries(${LIBRARY_NAME} PUBLIC cxx_setup Boost::system Threads::Threads)

install(TARGETS ${LIBRARY_NAME})
install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION include/${LIBRARY_NAME} FILES_MATCHING PATTERN "*.h*")
