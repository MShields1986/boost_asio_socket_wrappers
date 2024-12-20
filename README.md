# boost_asio_socket_wrappers
Simple wrapper classes around common Boost ASIO socket interfaces.

# Including in an external project
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
target_link_libraries(${EXECUTABLE_NAME} BoostSocketWrappers)

```

# Usage
## TCP Server
```cpp
#include <BoostSocketWrappers/tcp_server_boost.h>

BoostSocketWrappers::TcpServerBoost tcp_server;

size_t buffer_size(256);

tcp_server("192.1.1.10", 1111);
tcp_server.send("command string");
std::vector<unsigned char> response = tcp_server.receive(buffer_size);
```

## TCP Client
```cpp
#include <BoostSocketWrappers/tcp_client_boost.h>

BoostSocketWrappers::TcpClientBoost tcp_client;

size_t buffer_size(256);

tcp_client("192.1.1.10", 1111);
tcp_client.connect();
tcp_client.send("command string");
std::vector<unsigned char> response = tcp_client.receive(buffer_size);
```

## UDP Client
```cpp
#include <BoostSocketWrappers/udp_client_boost.h>

BoostSocketWrappers::UdpClientBoost udp_client;

size_t buffer_size(256);

udp_client("192.1.1.10", 1111);
std::vector<unsigned char> response = udp_client.receive(buffer_size);
```
