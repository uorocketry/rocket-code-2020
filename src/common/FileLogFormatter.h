#pragma once
#include "pch.h"
#include "spdlog/pattern_formatter.h"
#include "utils.h"

/**
 * Custom formatter for spdlog. Same as default but using the getTimeStamp() function
 */
class FileLogFormatter : public spdlog::formatter
{
  private:
    spdlog::pattern_formatter f; // Separate formatter for rest of the log messages
  public:
    FileLogFormatter()
    {
        auto format = "[%n] [%^%l%$] [%s:%#] %v";
        f.set_pattern(format);
    }
    void format(const spdlog::details::log_msg &msg, spdlog::memory_buf_t &dest) override
    {
        auto timeStamp = utils::getMonotonicTimeStamp();
        dest.append("[" + std::to_string(timeStamp) + "] "); // The only thing we need to change is the time stamp
        f.format(msg, dest);
    }

    std::unique_ptr<formatter> clone() const override
    {
        return std::make_unique<FileLogFormatter>();
    }
};