#include "tcp_server_endpoint_impl.hpp"



namespace fdoip_v1 {

tcp_server_endpoint_impl::tcp_server_endpoint_impl(
        boost::asio::io_service &_io,
        const boost::asio::ip::tcp::endpoint &_local):
        io_(_io),
        acceptor_(_io) {
    boost::system::error_code ec;
    acceptor_.open(_local.protocol(), ec);
    boost::asio::detail::throw_error(ec, "acceptor open");
    acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
    boost::asio::detail::throw_error(ec, "acceptor set_option");

    // std::string its_device = "eth0";
    // if (its_device != "") {
    //     if (setsockopt(acceptor_.native_handle(),
    //             SOL_SOCKET, SO_BINDTODEVICE, its_device.c_str(), (int)its_device.size()) == -1) {
    //         /* TODO: LOG */
    //         // VSOMEIP_WARNING << "TCP Server: Could not bind to device \"" << its_device << "\"";
    //     }
    // }

    acceptor_.bind(_local, ec);
    boost::asio::detail::throw_error(ec, "acceptor bind");
    acceptor_.listen(boost::asio::socket_base::max_connections, ec);
    boost::asio::detail::throw_error(ec, "acceptor listen");
}

tcp_server_endpoint_impl::~tcp_server_endpoint_impl() {
}

void tcp_server_endpoint_impl::start() {
    std::lock_guard<std::mutex> its_lock(acceptor_mutex_);
    if (acceptor_.is_open()) {
        session::ptr new_session = session::create(
            std::dynamic_pointer_cast<tcp_server_endpoint_impl>(shared_from_this()), io_);

        {
            std::unique_lock<std::mutex> its_socket_lock(new_session->get_socket_lock());
            acceptor_.async_accept(new_session->get_socket(),
                    std::bind(&tcp_server_endpoint_impl::accept_cbk,
                            std::dynamic_pointer_cast<tcp_server_endpoint_impl>(
                                    shared_from_this()), new_session,
                            std::placeholders::_1));
        }
    }
}

void tcp_server_endpoint_impl::stop() {}

void tcp_server_endpoint_impl::accept_cbk(const session::ptr& _session,
        boost::system::error_code const &_error) {

}

boost::asio::ip::tcp::socket& tcp_server_endpoint_impl::session::get_socket() {
    return socket_;
}

std::mutex& tcp_server_endpoint_impl::session::get_socket_lock() {
    return socket_mutex_;
}


} // namespace fdoip_v1