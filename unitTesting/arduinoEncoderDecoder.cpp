#include "ArduinoComm.pb.h"
#include "IO/ArduinoEncoder.h"
#include <catch2/catch.hpp>

using RocketryProto::ArduinoIn;

TEST_CASE("Encode and decode protobuf message", "[protobuf]")
{
    std::string testString = "This is a test";

    ArduinoIn arduinoIn;
    arduinoIn.mutable_servoinit()->set_pin(1823);
    arduinoIn.mutable_servoinit()->set_safeposition(1231);

    helper::SharedArray<char> encodedData = ArduinoEncoder::encode(arduinoIn);

    auto arduinoIn2 = ArduinoEncoder::decode<ArduinoIn>(encodedData.data.get(), encodedData.length);

    REQUIRE(arduinoIn2.data_case() == ArduinoIn::kServoInit);
    REQUIRE(arduinoIn2.servoinit().pin() == 1823);
    REQUIRE(arduinoIn2.servoinit().safeposition() == 1231);
}

TEST_CASE("Last byte is 0x0 when encoding protobuf message", "[protobuf]")
{
    std::string testString = "This is a test";

    ArduinoIn arduinoIn;
    arduinoIn.mutable_servoinit()->set_pin(1823);
    arduinoIn.mutable_servoinit()->set_safeposition(1231);

    helper::SharedArray<char> encodedData = ArduinoEncoder::encode(arduinoIn);

    REQUIRE(encodedData.data.get()[encodedData.length - 1] == 0x0);
}
