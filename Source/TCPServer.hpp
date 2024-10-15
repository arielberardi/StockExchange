#include <memory>

#include <boost/asio.hpp>

class TCPClient : public std::enable_shared_from_this<TCPClient>
{
  public:
    using Callback = std::function<void(const char* data, const std::size_t length)>;

    static constexpr std::size_t kMaxData = 1024;
    typedef std::shared_ptr<TCPClient> Pointer;

    TCPClient(boost::asio::ip::tcp::socket socket, Callback dataReceivedCallback)
        : m_Socket(std::move(socket)), m_DataReceivedCallback{dataReceivedCallback}
    {
    }

    void Start();

  private:
    boost::asio::ip::tcp::socket m_Socket;
    char m_Data[kMaxData];
    Callback m_DataReceivedCallback;

    void DoRead();
};

class TCPServer
{
  public:
    TCPServer(boost::asio::io_context& context,
              boost::asio::ip::port_type port,
              TCPClient::Callback dataReceivedCallback)
        : m_Acceptor{context, boost::asio::ip::tcp::endpoint{boost::asio::ip::tcp::v4(), port}},
          m_DataReceivedCallback{dataReceivedCallback}
    {
        StartAccept();
    }

  private:
    boost::asio::ip::tcp::acceptor m_Acceptor;
    TCPClient::Callback m_DataReceivedCallback;

    void StartAccept();
};
