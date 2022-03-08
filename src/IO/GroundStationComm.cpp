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
