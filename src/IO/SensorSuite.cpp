#include "SensorSuite.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <string>

using boost::asio::ip::address;
using boost::asio::ip::tcp;

constexpr auto SENSOR_SUITE_IP = "192.168.1.250";
constexpr auto SENSOR_SUITE_PORT = 8080;
constexpr auto DATA_LENGTH = 15;

SensorSuite::SensorSuite() = default;

void SensorSuite::initialize()
{
    IO::initialize();
}

bool SensorSuite::isInitialized()
{
    return true;
}

void SensorSuite::run()
{
    try
    {
        tcp::endpoint endpoint(address::from_string(SENSOR_SUITE_IP), SENSOR_SUITE_PORT);
        tcp::socket socket(io_context);

        connect(socket, endpoint);

        boost::asio::streambuf sb;

        while (true)
        {
            try
            {
                boost::asio::read_until(socket, sb, "\n");

                std::istream input(&sb);
                std::string line;
                getline(input, line, '\n');

                std::vector<std::string> result;
                boost::split(result, line, boost::is_any_of(","));

                if (result.size() == DATA_LENGTH)
                {
                    latest = result;
                }
            }
            catch (std::exception &e)
            {
                SPDLOG_LOGGER_ERROR(logger, "Exception: {}", e.what());

                if (socket.is_open())
                {
                    socket.close();
                }

                connect(socket, endpoint);
            }
        }
    }
    catch (std::exception &e)
    {
        SPDLOG_LOGGER_ERROR(logger, "Exception: {}", e.what());
    }
}

void SensorSuite::connect(tcp::socket &socket, tcp::endpoint &endpoint)
{
    boost::system::error_code err;

    do
    {
        SPDLOG_LOGGER_INFO(logger, "Trying to connect to SensorSuite...");
        socket.connect(endpoint, err);

        if (err)
        {
            SPDLOG_LOGGER_ERROR(logger, "Failed to connect to SensorSuite, Retrying...: {}", err.message());
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        else
        {
            SPDLOG_LOGGER_INFO(logger, "Connected to SensorSuite...");
        }
    } while (err);
}

SensorSuiteState SensorSuite::getCurrentData()
{
    if (latest.size() == DATA_LENGTH)
    {
        boost::trim_right(latest[DATA_LENGTH - 1]);

        int count = 0;
        // clang-format off
        try {
            return {
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<uint32_t>(latest[count++]),
                boost::lexical_cast<uint32_t>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<float>(latest[count++]),
                boost::lexical_cast<uint32_t>(latest[count++]),
            };
        } catch (std::exception& e) {
            SPDLOG_LOGGER_ERROR(logger, "Exception: {}", e.what());
        }
        // clang-format on
    }

    return {};
}