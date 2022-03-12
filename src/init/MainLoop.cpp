#include "common/pch.h"
#include "iostream"
#include <spdlog/sinks/systemd_sink.h>
#include <thread>

#include "IO/InterfaceImpl.h"
#include "chrono"
#include "data/UOSMData.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/dup_filter_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "stateMachine/HotFire/HotFireStateMachine.h"
#include "stateMachine/OctoberSky/OctoberSkyStateMachine.h"

constexpr auto DEFAULT_TARGET_UPDATE_DURATION_NS = 1000000000L / 30L; // in nanoseconds = 33 miliseconds = 30Hz

// Specify the minimum logging level. The specified level and up will be logged.
// For example, if we have the level to be `info`, `warning` and `error` will be
// logged but not `debug`.
const auto CONSOLE_LOGGING_LEVEL = spdlog::level::info;
const auto FILE_LOGGING_LEVEL = spdlog::level::info;
const auto SYSTEMD_LOGGING_LEVEL = spdlog::level::debug;

void setup_logging()
{
    // Duplicate message removal
    auto dup_filter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(2));

    // Get the current Unix time so we can create a unique log file
    auto unix_timestamp = std::chrono::seconds(std::time(nullptr));
    long unix_timestamp_x_1000 = std::chrono::milliseconds(unix_timestamp).count();

    // Log to a file
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "logs/global_" + std::to_string(unix_timestamp_x_1000) + ".log");
    file_sink->set_level(FILE_LOGGING_LEVEL);
    dup_filter->add_sink(file_sink);

    if (environment::getEnvOrDefault<std::string>("INSIDE_SERVICE", "0") == "0")
    {
        // Log to the console
        auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        stdout_sink->set_level(CONSOLE_LOGGING_LEVEL);
        dup_filter->add_sink(stdout_sink);
    }
    else
    {
        // Log to systemd
        auto systemd_sink = std::make_shared<spdlog::sinks::systemd_sink_mt>();
        systemd_sink->set_level(SYSTEMD_LOGGING_LEVEL);
        dup_filter->add_sink(systemd_sink);
    }

    std::vector<spdlog::sink_ptr> sinks{dup_filter};

    // Create a new logger with name 'global'
    auto logger = std::make_shared<spdlog::logger>("global", begin(sinks), end(sinks));
    logger->set_level(spdlog::level::trace);

    // Register the logger we just created so we can access it from anywhere
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);

    spdlog::enable_backtrace(32);
}

int main(int argc, char *argv[])
{
    environment::initializeVariablesMap(argc, argv);

    setup_logging();
    SPDLOG_INFO("Using {}", BOOST_PP_STRINGIZE(STATEMACHINE));

#if TESTING != 1
    InterfaceImpl interfaceImpl;
#else
    TestingInterface interfaceImpl;
#endif

    // create a state machine instance
    STATEMACHINE uOttSM(&interfaceImpl);

    time_point start, now;
    duration_ns target_ns, elapsed_ns;
    start = std::chrono::steady_clock::now();
    UOSMData data = UOSMData();

    const auto targetUpdateDuration =
        environment::getEnvOrDefault<uint64_t>("TARGET_UPDATE_DURATION_NS", DEFAULT_TARGET_UPDATE_DURATION_NS);
    uint64_t count = 1;
    while (true)
    {
        // Keep in mind, this is NOT the time since unix epoch (1970), and not the
        // system time
        now = std::chrono::steady_clock::now();

        data.now = now;

        uOttSM.updateStateMachine(data);

        elapsed_ns = duration_ns(now - start);
        target_ns = duration_ns(targetUpdateDuration * count++);

        if (target_ns > elapsed_ns)
        {
            std::this_thread::sleep_for(target_ns - elapsed_ns);
        }
        else if (targetUpdateDuration != 0)
        {
            SPDLOG_ERROR("Timing Error: Update took too long");
        }
    }

    return 0;
}
