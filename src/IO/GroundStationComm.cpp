#include "GroundStationComm.h"
#include <spdlog/spdlog.h>

void GroundStationComm::sendSensorData(const sensorsData &data)
{
    auto dataStr = data.convertToReducedString();
    dataStr += "\n";

    RocketryProto::GroundStationIn gsData;
    gsData.set_sensorsdata(dataStr);

    sendMessage(gsData);
}

void GroundStationComm::handleMessage(const RocketryProto::GroundStationOut &gsData)
{
    auto data = gsData.data();
    SPDLOG_INFO("Received message from ground station: {}", data);
    eventQueue.push(data);
}

void GroundStationComm::sink_it_(const spdlog::details::log_msg &msg)
{
    RocketryProto::GroundStationIn pbMsg;
    auto pbLogMsg = pbMsg.mutable_loggingmessage();
    switch (msg.level)
    {
    case spdlog::level::trace:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_TRACE);
        break;
    case spdlog::level::debug:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_DEBUG);
        break;
    case spdlog::level::info:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_INFO);
        break;
    case spdlog::level::warn:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_WARN);
        break;
    case spdlog::level::err:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_ERROR);
        break;
    case spdlog::level::critical:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_CRITICAL);
        break;
    default:
        pbLogMsg->set_level(RocketryProto::LoggingMessage_LogLevel_INFO);
    }

    pbLogMsg->set_log(msg.payload.data());
    pbLogMsg->set_source(msg.source.filename + msg.source.line);

    sendMessage(pbMsg);
}
