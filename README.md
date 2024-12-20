# boost_asio_socket_wrappers
Simple wrapper classes around common Boost ASIO socket interfaces.

# Building
## Including in an external project
Use the inclusions below in your CMakeLists.txt to have CMake fetch and build the library for you.

```cmake
include(FetchContent)

FetchContent_Declare(
  simple_boost_asio_sockets
  GIT_REPOSITORY https://github.com/MShields1986/boost_asio_socket_wrappers
  GIT_TAG        main
)

FetchContent_MakeAvailable(simple_boost_asio_sockets)
```

Then link against your intended compilation target.

```cmake
target_link_libraries(${TARGET_NAME}
    simple_boost_asio_sockets
)
```

## As a standalone library
```shell
cmake -S . -B build/
cmake --build build/
```
