#include "common/pch.h"
#include <catch2/catch.hpp>

TEST_CASE("Helper String Split", "[helper]")
{
    std::vector<std::string> result;
    boost::split(result, "item1,item2,item3", boost::is_any_of(","));
    REQUIRE(result == std::vector<std::string>{"item1", "item2", "item3"});
}