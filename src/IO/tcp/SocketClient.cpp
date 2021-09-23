#include "SocketClient.h"

#include <mutex>
#include <spdlog/spdlog.h>
#include <thread>

using namespace boost::asio;

SocketClient::SocketClient(std::shared_ptr<ip::tcp::socket> socket, std::function<void(const char[])> receiveCallback,
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
        boost::system::error_code err;
        if (write(*socket, buffer(data), err) == -1 || err)
        {
            if (err)
            {
                SPDLOG_LOGGER_ERROR(logger, err.message());
            }
            else
            {
                SPDLOG_LOGGER_ERROR(logger, "Could not successfully send the TCP message");
            }
        }
    }
}

void SocketClient::receivingLoop()
{
    while (socket->is_open())
    {
        char b[1] = {(char)-1};
        boost::system::error_code err;
        socket->read_some(buffer(b), err);

        SPDLOG_LOGGER_INFO(logger, "Recieved data: {}", (int)b[0]);

        if (err)
        {
            SPDLOG_LOGGER_ERROR(logger, err.message());

            if (err == boost::asio::error::eof)
            {
                SPDLOG_LOGGER_INFO(logger, "Connection closed by the device");
                socket->close();

                closeCallback(this);
                return;
            }
        }
        else
        {
            receiveCallback(b);
        }
    }

    closeCallback(this);
}