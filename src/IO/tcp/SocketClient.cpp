#include "SocketClient.h"
#include <spdlog/spdlog.h>
#include <thread>

using namespace boost;

SocketClient::SocketClient(std::shared_ptr<asio::ip::tcp::socket> socket,
                           std::function<void(const char[])> receiveCallback,
                           std::function<void(SocketClient *)> closeCallback)
    : socket(std::move(socket)), receiveCallback(std::move(receiveCallback)), closeCallback(std::move(closeCallback))
{
    logger = spdlog::default_logger();

    std::thread receivingThread([this] { receivingLoop(); });
    receivingThread.detach();
}

SocketClient::~SocketClient()
{
}

void SocketClient::send(const std::string &data) const
{
    if (socket->is_open())
    {
        boost::system::error_code err; // write timeout
        asio::async_write(*socket, asio::buffer(data), [this](auto err, auto bytes_transferred) {
            if (bytes_transferred <= 0)
            {
                SPDLOG_LOGGER_ERROR(logger, "Could not successfully send the TCP message");
            }
            else if (err)
            {
                SPDLOG_LOGGER_ERROR(logger, err.message());
            }
        });
    }
}

void SocketClient::receivingLoop()
{
    while (socket->is_open())
    {
        char b[1] = {(char)-1};
        boost::system::error_code err;
        socket->read_some(asio::buffer(b), err);

        SPDLOG_LOGGER_INFO(logger, "Recieved data: {}", (int)b[0]);

        if (err)
        {
            if (err == boost::asio::error::eof)
            {
                SPDLOG_LOGGER_WARN(logger, "Connection closed by the device");
                socket->close();

                closeCallback(this);
                return;
            }
            else
            {
                SPDLOG_LOGGER_ERROR(logger, err.message());
            }
        }
        else
        {
            receiveCallback(b);
        }
    }

    closeCallback(this);
}