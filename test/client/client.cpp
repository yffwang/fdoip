#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::placeholders;
boost::asio::streambuf receive_buffer;

void handle_write(const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
  if (!error) {
    std::cout << "Message sent to server." << std::endl;
  } else {
    std::cerr << "Write error: " << error.message() << std::endl;
  }
}

void handle_read(const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
  if (!error) {
    std::cout << "Response from server: " << boost::asio::buffer_cast<const char*>(receive_buffer.data()) << std::endl;
  } else {
    std::cerr << "Read error: " << error.message() << std::endl;
  }
}

int main() {
  try {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::ip::tcp::resolver resolver(io_context);

    boost::asio::async_connect(socket, resolver.resolve("localhost", "12345"),
        [&](const boost::system::error_code& error, const boost::asio::ip::tcp::endpoint& /*endpoint*/) {
        if (!error) {
          std::string message = "Hello, server!\n";
          boost::asio::async_write(socket, boost::asio::buffer(message),
            boost::bind(handle_write, boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));

          boost::asio::async_read_until(socket, receive_buffer, '\n',
            boost::bind(handle_read, boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
        } else {
          std::cerr << "Connect error: " << error.message() << std::endl;
        }
      });

    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
            