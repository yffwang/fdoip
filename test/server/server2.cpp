#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

class Connection : public std::enable_shared_from_this<Connection> {
public:
  explicit Connection(boost::asio::io_context& ioContext)
    : socket_(ioContext), strand_(ioContext) {}

  void Start() {
    boost::asio::post(strand_, [self = shared_from_this()]() {
      self->Read();
    });
  }

private:
  void Read() {
    boost::asio::async_read(socket_, boost::asio::buffer(buffer_),
      boost::asio::transfer_at_least(1),
      strand_.wrap([self = shared_from_this()](const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (!error) {
          // Process received data
          std::cout << "Received: " << std::string(self->buffer_.data(), bytes_transferred) << std::endl;

          // Continue reading
          self->Read();
        }
      }));
  }

  
  boost::asio::io_context::strand strand_;
  std::array<char, 1024> buffer_;
public:
    boost::asio::ip::tcp::socket socket_;
};

int main() {
  boost::asio::io_context ioContext;
  boost::asio::io_context::work work(ioContext);

  // Start worker threads
  boost::thread_group threadPool;
  for (std::size_t i = 0; i < 4; ++i) {
    threadPool.create_thread([&ioContext]() {
      ioContext.run();
    });
  }

  // Create a listening socket
  boost::asio::ip::tcp::acceptor acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));
  std::cout << "Server started. Listening on port 12345." << std::endl;

  // Accept incoming connections
  while (true) {
    auto connection = std::make_shared<Connection>(ioContext);
    acceptor.accept(connection->socket_);
    connection->Start();
  }

  // Stop the worker threads
  ioContext.stop();
  threadPool.join_all();

  return 0;
}