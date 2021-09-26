#include <catch2/catch.hpp>
#include <helpers/Helper.h>

TEST_CASE("Helper String Split", "[helper]")
{
    REQUIRE(helper::stringSplit("item1,item2,item3", ',') == std::vector<std::string>{"item1", "item2", "item3"});
}