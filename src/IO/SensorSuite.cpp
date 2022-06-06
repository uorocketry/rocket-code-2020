#include "SensorSuite.h"

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <string>

using boost::asio::ip::address;
using boost::asio::ip::tcp;

constexpr auto SENSOR_SUITE_IP = "192.168.1.250";

SensorSuite::SensorSuite() = default;

bool SensorSuite::isInitialized()
{
    return true;
}

[[noreturn]] void SensorSuite::run()
{
    tcp::endpoint endpoint(address::from_string(SENSOR_SUITE_IP), 12345);
    tcp::socket socket(io_context);
    socket.connect(endpoint);

    while (true)
    {
        boost::asio::streambuf sb;
        boost::asio::read_until(socket, sb, "\n");

        std::istream input(&sb);
        std::string line;
        getline(input, line, '\n');

        std::vector<std::string> result;
        boost::split(result, line, boost::is_any_of(","));

        if (result.size() == 9)
        {
            latest = result;
        }
    }
}

SensorSuiteState SensorSuite::getCurrentData()
{
    int count = 0;
    // clang-format off
    return {
        boost::lexical_cast<uint32_t>(latest[count++]),
        boost::lexical_cast<float>(latest[count++]),
        boost::lexical_cast<float>(latest[count++]),
        boost::lexical_cast<uint32_t>(latest[count++]),
        boost::lexical_cast<uint32_t>(latest[count++]),
        boost::lexical_cast<float>(latest[count++]),
        boost::lexical_cast<float>(latest[count++]),
        boost::lexical_cast<float>(latest[count++]),
        boost::lexical_cast<float>(latest[count++])
    };
    // clang-format on
}