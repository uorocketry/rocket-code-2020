#include <catch2/catch.hpp>
#include "IO/GroundStationEncoder.h"

TEST_CASE("Encode and decode protobuf message", "[protobuf]") {
	std::string testString = "This is a test";

	RocketOut rocketOut1;
	rocketOut1.mutable_sensordata()->set_data(testString);

	helper::SharedArray<char> encodedData = GroundStationEncoder::encode(rocketOut1);

	RocketOut rocketIn2 = GroundStationEncoder::decode<RocketOut>(encodedData);

	std::string test =  rocketIn2.sensordata().data();

	REQUIRE(rocketIn2.sensordata().data() == testString);
}

TEST_CASE("Last byte is 0x0 when encoding protobuf message", "[protobuf]") {
	std::string testString = "This is a test";

	RocketOut rocketOut1;
	rocketOut1.mutable_sensordata()->set_data(testString);

	helper::SharedArray<char> encodedData = GroundStationEncoder::encode(rocketOut1);

	REQUIRE(encodedData.data.get()[encodedData.length-1] == 0x0);
}
