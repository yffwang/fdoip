#ifndef FDOIP_V1_TCP_SERVER_ENDPOINT_IMPL_HPP_
#define FDOIP_V1_TCP_SERVER_ENDPOINT_IMPL_HPP_

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace fdoip_v1 {

class tcp_server_endpoint_impl {

public:
    tcp_server_endpoint_impl(
            boost::asio::io_service &_io,
            const boost::asio::ip::tcp::endpoint &_local);
    virtual ~tcp_server_endpoint_impl();

    void start();
    void stop();

private:
    std::mutex acceptor_mutex_;
    boost::asio::ip::tcp::acceptor acceptor_;

    // Reference to service context
    boost::asio::io_service &service_;

private:
    class session: public std::enable_shared_from_this<session> {
    
    public:
        static std::shared_ptr<session> create(
                const std::weak_ptr<tcp_server_endpoint_impl>& _server,
                boost::asio::io_service & _io_service);
        
        void start();
        void stop();
        void receive();

        boost::asio::ip::tcp::socket & get_socket();
        std::unique_lock<std::mutex> get_socket_lock();

    private:
        session(const std::weak_ptr<tcp_server_endpoint_impl>& _server,
                boost::asio::io_service & _io_service);

    };
};


} // namespace fdoip_v1

#endif // FDOIP_V1_TCP_SERVER_ENDPOINT_IMPL_HPP_
