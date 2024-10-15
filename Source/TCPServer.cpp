#include <iostream>

#include <boost/asio.hpp>

#include "TCPServer.hpp"

using ErrorCode = boost::system::error_code;

void TCPClient::Start()
{
    DoRead();
}

void TCPClient::DoRead()
{
    auto self = shared_from_this(); // Capture shared_ptr of this to keep it alive

    auto handler = [this, self](const ErrorCode& error, std::size_t length)
    {
        if (error)
        {
            if (error != boost::asio::error::eof)
            {
                std::cerr << "Error on received: " << error.message() << std::endl;
            }
        }
        else
        {
            m_DataReceivedCallback(m_Data, length);
        }

        DoRead();
    };

    m_Socket.async_read_some(boost::asio::buffer(m_Data, kMaxData), handler);
}

void TCPServer::StartAccept()
{
    auto handler = [this](const ErrorCode& error, boost::asio::ip::tcp::socket socket)
    {
        if (error)
        {
            std::cerr << "Error on accepting a client: " << error.message() << std::endl;
        }
        else
        {
            std::make_shared<TCPClient>(std::move(socket), m_DataReceivedCallback)->Start();
        }

        StartAccept();
    };

    m_Acceptor.async_accept(handler);
}
