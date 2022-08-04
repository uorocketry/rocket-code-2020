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
constexpr auto SENSOR_SUITE_IP2 = "192.168.1.200";
constexpr auto SENSOR_SUITE_PORT = 8080;
constexpr auto SENSOR_SUITE_PORT2 = 8080;
constexpr auto TWO_DATAQ_DATA_LENGTH = 21;
constexpr auto ONE_DATAQ_DATA_LENGTH = 15;

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
    #if DOUBLE_SENSOR_SUITE == 1
    secondConnectionThread = std::thread(&SensorSuite::runSecondListener, this);
    secondConnectionThread.detach();
    #endif

    startListening(SENSOR_SUITE_IP2, SENSOR_SUITE_PORT2, 1);
}

void SensorSuite::runSecondListener()
{
    SensorSuite::startListening(SENSOR_SUITE_IP, SENSOR_SUITE_PORT, 0);
}

void SensorSuite::startListening(std::string host, int port, int index)
{
    try
    {
        tcp::endpoint endpoint(address::from_string(host), port);
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

                #if DOUBLE_SENSOR_SUITE == 1
                    if (result.size() == ONE_DATAQ_DATA_LENGTH)
                    {
                        if (index == 0) 
                        {
                            latestOne = result;
                        } else if (index == 1) 
                        {
                            latestTwo = result;
                        }
                    } else {
                        SPDLOG_LOGGER_ERROR(logger, "Sensor suite sent {} lines, the wrong amount: {}", result.size(), line);
                    }
                #else
                    if (result.size() == TWO_DATAQ_DATA_LENGTH)
                    {
                        latestOne = result;
                    }
                #endif
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
    #if DOUBLE_SENSOR_SUITE == 1
    if (latestOne.size() == ONE_DATAQ_DATA_LENGTH && latestTwo.size() == ONE_DATAQ_DATA_LENGTH)
    {
        boost::trim_right(latestOne[ONE_DATAQ_DATA_LENGTH - 1]);
        boost::trim_right(latestTwo[ONE_DATAQ_DATA_LENGTH - 1]);

        int count1 = 0;
        int count2 = 0;
        // clang-format off
        try {
            return {
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<uint32_t>(latestOne[count1++]),
                boost::lexical_cast<uint32_t>(latestOne[count1++]),
                boost::lexical_cast<float>(latestTwo[count2++]),
                boost::lexical_cast<float>(latestTwo[count2++]),
                boost::lexical_cast<float>(latestTwo[count2++]),
                boost::lexical_cast<float>(latestTwo[count2++]),
                boost::lexical_cast<uint32_t>(latestTwo[count2++]),
                boost::lexical_cast<uint32_t>(latestTwo[count2++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<float>(latestOne[count1++]),
                boost::lexical_cast<uint32_t>(latestOne[count1++]),
            };
        } catch (std::exception& e) {
            SPDLOG_LOGGER_ERROR(logger, "Exception: {}", e.what());
        }
        // clang-format on
    } else {
        SPDLOG_LOGGER_ERROR(logger, "Latest data is the wrong size: {}, {}", latestOne.size(), latestTwo.size());
    }
    #else
    if (latestOne.size() == TWO_DATAQ_DATA_LENGTH)
    {
        boost::trim_right(latestOne[TWO_DATAQ_DATA_LENGTH - 1]);

        int count = 0;
        // clang-format off
        try {
            return {
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<uint32_t>(latestOne[count++]),
                boost::lexical_cast<uint32_t>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<uint32_t>(latestOne[count++]),
                boost::lexical_cast<uint32_t>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<float>(latestOne[count++]),
                boost::lexical_cast<uint32_t>(latestOne[count++]),
            };
        } catch (std::exception& e) {
            SPDLOG_LOGGER_ERROR(logger, "Exception: {}", e.what());
        }
        // clang-format on
    }
    #endif
    

    return {};
}