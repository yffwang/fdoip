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

void tcp_server_endpoint_impl::accept_cbk(const session::ptr& _session,
        boost::system::error_code const &_error) {
    if (!_error) {
        boost::system::error_code its_error;
        boost::asio::ip::tcp::endpoint remote;
        {
            std::unique_lock<std::mutex> its_socket_lock(_session->get_socket_lock());
        
            boost::asio::ip::tcp::socket &new_session_socket = _session->get_socket();
            remote = new_session_socket.remote_endpoint(its_error);
            _session->set_remote_info(remote);

            // Nagle algorithm off
            new_session_socket.set_option(boost::asio::ip::tcp::no_delay(true), its_error);
            new_session_socket.set_option(boost::asio::socket_base::keep_alive(true), its_error);
            // if (its_error) {
            //     VSOMEIP_WARNING << "tcp_server_endpoint::session: couldn't enable "
            //             << "keep_alive: " << its_error.message();
            // }
        }

        // Setup socket connection successfully!
        if (!its_error) {
            {
                std::lock_guard<std::mutex> its_lock(sessions_management_mutex_);
                sessions_management_[remote] = _session;
            }
            _session->start();
        }
    }


    if (_error != boost::asio::error::bad_descriptor
            && _error != boost::asio::error::operation_aborted
            && _error != boost::asio::error::no_descriptors) {
        start(); // Continue to listen to incoming sessions
    } 
    // else if (_error == boost::asio::error::no_descriptors) {
    //     // TODO: OS has used out of file descriptors, we can wait 1000ms and restart again 
    // }
}

void tcp_server_endpoint_impl::stop() {
    
    {
        std::lock_guard<std::mutex> its_lock(acceptor_mutex_);
        if(acceptor_.is_open()) {
            boost::system::error_code its_error;
            acceptor_.close(its_error);
        }
    }
}

boost::asio::ip::tcp::socket& tcp_server_endpoint_impl::session::get_socket() {
    return socket_;
}

std::mutex& tcp_server_endpoint_impl::session::get_socket_lock() {
    return socket_mutex_;
}

void tcp_server_endpoint_impl::session::set_remote_info(
        const boost::asio::ip::tcp::endpoint &_remote) {
    remote_ = _remote;
    remote_address_ = _remote.address();
    remote_port_ = _remote.port();
}


} // namespace fdoip_v1