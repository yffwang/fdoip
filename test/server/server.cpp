#include <iostream>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)) {
  }

  void start() {
    doRead();
  }

private:
  void doRead() {
    auto self(shared_from_this());
    boost::asio::async_read_until(socket_, receiveBuffer_, '\n',
      [this, self](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
        if (!error) {
          std::istream is(&receiveBuffer_);
          std::string message;
          std::getline(is, message);

          std::cout << "Received message: " << message << std::endl;

          doWrite(message + "\n");
        } else {
          std::cerr << "Read error: " << error.message() << std::endl;
        }
      });
  }

  void doWrite(const std::string& message) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(message),
      [this, self](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
        if (!error) {
          doRead();
        } else {
          std::cerr << "Write error: " << error.message() << std::endl;
        }
      });
  }

  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf receiveBuffer_;
};

class Server {
public:
  Server(boost::asio::io_context& ioContext, std::uint16_t port)
    : acceptor_(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    doAccept();
  }

private:
  void doAccept() {
    acceptor_.async_accept(
      [this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
        if (!error) {
          std::make_shared<Session>(std::move(socket))->start();
        } else {
          std::cerr << "Accept error: " << error.message() << std::endl;
        }

        doAccept();
      });
  }

  boost::asio::ip::tcp::acceptor acceptor_;
};

int main() {
  try {
    boost::asio::io_context ioContext;
    Server server(ioContext, 12345);
    ioContext.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}