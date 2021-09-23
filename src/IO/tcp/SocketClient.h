#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <spdlog/logger.h>

class SocketClient
{
  public:
    SocketClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                 std::function<void(const char[])> receiveCallback, std::function<void(SocketClient *)> closeCallback);
    ~SocketClient();

    void send(const std::string &data) const;

  private:
    void receivingLoop();

    const std::shared_ptr<boost::asio::ip::tcp::socket> socket;

    std::shared_ptr<spdlog::logger> logger;
    std::function<void(const char b[])> receiveCallback;
    std::function<void(SocketClient *)> closeCallback;
};