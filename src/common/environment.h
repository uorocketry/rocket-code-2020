#pragma once
#include <boost/program_options.hpp>               // Command line arguments
#include <boost/program_options/variables_map.hpp> // Command line arguments

namespace environment
{

static boost::program_options::variables_map varMap;

/**
 * Checks if environment or config file has a value for a variable, otherwise, return the default value.
 * You're probably better of just having a default value in the config file.
 */
template <typename T = std::string>
static T getEnvOrDefault(const std::string &key, const T &defaultValue)
{
    if (varMap.count(key))
    {
        return boost::lexical_cast<T>(varMap[key].as<T>());
    }
    else if (std::getenv(key.c_str()))
    {
        return boost::lexical_cast<T>(std::getenv(key.c_str()));
    }
    else
    {
        return defaultValue;
    }
}

/**
 * Initializes the configuration manager with the given command line arguments.
 */
static void initializeVariablesMap(int argc, char *argv[])
{

    // Declare the supported options.
    boost::program_options::options_description desc("Miscellaneous");
    desc.add_options()("help", "produce help message");

    // Logging options
    boost::program_options::options_description logging_desc("Logging");
    logging_desc.add_options() //
        ("console-log-level", boost::program_options::value<std::string>()->default_value("debug"),
         "Console log level")                                                                                      //
        ("file-log-level", boost::program_options::value<std::string>()->default_value("debug"), "File log level") //
        ("systemd-log-level", boost::program_options::value<std::string>()->default_value("debug"),
         "Systemd log level") //
        ("log-folder", boost::program_options::value<std::string>()->default_value("./data/"),
         "specify the folder to save the logs") //
        ("log-ext", boost::program_options::value<std::string>()->default_value(".uorocketlog"),
         "specify a log file"); //

    // Arduino proxy options
    boost::program_options::options_description arduino_desc("Arduino proxy options");
    arduino_desc.add_options() //
        ("arduino-serial-device", boost::program_options::value<std::string>()->default_value("/dev/ttyAMA0"),
         "device name")                                                                              //
        ("arduino-serial-baud", boost::program_options::value<int>()->default_value(115200), "baud") //
        ("arduino-serial-timeout", boost::program_options::value<int>()->default_value(5000),
         "serial timeout in ms"); //

    // SGB Sensor options
    boost::program_options::options_description sbg_desc("SBG sensor options");
    sbg_desc.add_options() //
        ("sbg-serial-device", boost::program_options::value<std::string>()->default_value("/dev/ttyUSB0"),
         "device name")                                                                                            //
        ("sbg-serial-baud", boost::program_options::value<int>()->default_value(115200), "baud")                   //
        ("sbg-serial-timeout", boost::program_options::value<int>()->default_value(5000), "serial timeout in ms"); //

    // Collect options
    boost::program_options::options_description all_options("All options");
    all_options.add(desc).add(logging_desc).add(arduino_desc).add(sbg_desc);

    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, all_options), varMap);
    try
    {
        boost::program_options::store(boost::program_options::parse_config_file("config.cfg", all_options), varMap);
    }
    catch (boost::wrapexcept<boost::program_options::reading_file> &e)
    {
        SPDLOG_INFO("Unused configuration file: {}", e.what());
    }
    boost::program_options::notify(varMap);

    if (varMap.count("help"))
    {
        std::cout << desc << "\n";
        exit(0);
    }
}
} // namespace environment