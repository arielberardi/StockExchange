#pragma once

#include <string_view>

#include <boost/asio.hpp>

#include "MarketFeedMessage.hpp"

class UDPMulticast
{
  public:
    UDPMulticast(boost::asio::io_context& context,
                 std::string_view ip,
                 boost::asio::ip::port_type port)
        : m_Socket{context}, m_Endpoint{boost::asio::ip::make_address(ip), port}
    {
        m_Socket.open(boost::asio::ip::udp::v4());
        m_Socket.set_option(boost::asio::ip::multicast::outbound_interface(
            boost::asio::ip::make_address("172.19.15.78").to_v4()));
        m_Socket.set_option(boost::asio::ip::multicast::hops(1));
    };

    ~UDPMulticast()
    {
        m_Socket.close();
    }

    void Send(const std::vector<uint8_t>& buffer)
    {
        m_Socket.send_to(boost::asio::buffer(buffer, buffer.size()), m_Endpoint);
    };

  private:
    boost::asio::ip::udp::endpoint m_Endpoint;
    boost::asio::ip::udp::socket m_Socket;
};
