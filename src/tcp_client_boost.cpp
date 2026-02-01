#include "BoostSocketWrappers/tcp_client_boost.h"



namespace BoostSocketWrappers {

TcpClientBoost::TcpClientBoost()
     : io_context_(),
       socket_(io_context_)
{
}


TcpClientBoost::~TcpClientBoost() {
    stopIoThread();
    socket_.close();
}


void TcpClientBoost::setup(const std::string& ip_address, const int& port) {
    using namespace boost::asio::ip;

    ip_address_ = ip_address;
    port_ = port;
    remote_endpoint_ = tcp::endpoint(address::from_string(ip_address_), port_);
}


void TcpClientBoost::connect() {
    socket_.connect(remote_endpoint_);
    {
        using namespace boost::asio::ip;
        socket_.set_option(tcp::no_delay(true));
    }
}


std::vector<unsigned char> TcpClientBoost::receive(const size_t& size) {
    std::vector<unsigned char> data(size);
    boost::system::error_code error;

    boost::asio::read(socket_, boost::asio::buffer(data), error);

    if(error) {
        std::cout << "TCPClientBoost : Read error: " << error << std::endl;
    }

    return data;
}


void TcpClientBoost::send(const std::string& message) {
  const std::string msg = message;
  boost::asio::write(socket_, boost::asio::buffer(msg));
}


void TcpClientBoost::startIoThread() {
    if (io_thread_.joinable()) {
        return; // Already running
    }
    io_context_.restart();
    io_work_ = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(
        io_context_.get_executor());
    io_thread_ = std::thread([this]() { io_context_.run(); });
}


void TcpClientBoost::stopIoThread() {
    io_work_.reset();
    io_context_.stop();
    if (io_thread_.joinable()) {
        io_thread_.join();
    }
}


void TcpClientBoost::stopIoThreadGracefully() {
    // Cancel pending async operations so their handlers fire with
    // operation_aborted.  Then release the work guard and let the
    // io_context drain naturally (all pending handlers complete).
    cancelPendingOperations();
    io_work_.reset();
    if (io_thread_.joinable()) {
        io_thread_.join();
    }
}


void TcpClientBoost::cancelPendingOperations() {
    boost::system::error_code ec;
    socket_.cancel(ec);
}


void TcpClientBoost::drainSocket() {
    // Discard any bytes left in the kernel receive buffer after a
    // cancelled async read.  Uses non-blocking reads so this never
    // waits for new data.
    socket_.non_blocking(true);

    boost::system::error_code ec;
    char discard[4096];
    while (true) {
        socket_.read_some(boost::asio::buffer(discard), ec);
        if (ec) {
            break;  // EWOULDBLOCK / EOF / any error — done
        }
    }

    socket_.non_blocking(false);
}


void TcpClientBoost::asyncReceive(size_t size, ReceiveCallback callback) {
    async_recv_buffer_.resize(size);
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(async_recv_buffer_),
        [this, callback](boost::system::error_code ec, std::size_t /*bytes_transferred*/) {
            // Move the buffer contents out to the callback
            std::vector<unsigned char> data;
            if (!ec) {
                data = std::move(async_recv_buffer_);
            }
            callback(std::move(data), ec);
        });
}

} // namespace BoostSocketWrappers
