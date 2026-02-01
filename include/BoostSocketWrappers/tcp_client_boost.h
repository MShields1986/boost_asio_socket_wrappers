#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <memory>
#include <boost/asio.hpp>

namespace BoostSocketWrappers {

class TcpClientBoost {
public:
    using ReceiveCallback = std::function<void(std::vector<unsigned char>, boost::system::error_code)>;

    TcpClientBoost();
    ~TcpClientBoost();

    void                               setup(const std::string& ip_address, const int& port);
    void                               connect();
    std::vector<unsigned char>         receive(const size_t& size);
    void                               send(const std::string& message);

    // Async I/O
    void                               startIoThread();
    void                               stopIoThread();
    void                               stopIoThreadGracefully();
    void                               cancelPendingOperations();
    void                               drainSocket();
    void                               asyncReceive(size_t size, ReceiveCallback callback);

private:
    std::string                        ip_address_;
    int                                port_;
    boost::asio::io_context            io_context_;
    boost::asio::ip::tcp::endpoint     remote_endpoint_;

    // Async I/O members
    std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> io_work_;
    std::thread                        io_thread_;
    std::vector<unsigned char>         async_recv_buffer_;

public:
    boost::asio::ip::tcp::socket       socket_;
};

} // namespace BoostSocketWrappers
