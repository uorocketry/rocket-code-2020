#include "common/types.h"
#include <catch2/catch.hpp>

TEST_CASE("EventQueue push and pop", "[EventQueue]")
{
    EventQueue eventQueue(3);
    eventType temp;
    REQUIRE(eventQueue.empty());

    eventQueue.push(100);
    eventQueue.push(102);
    eventQueue.push(104);

    // Pop the first element
    eventQueue.pop(temp);
    REQUIRE(temp == 100);
    eventQueue.pop(temp);
    REQUIRE(temp == 102);
    eventQueue.pop(temp);
    REQUIRE(temp == 104);
    REQUIRE(eventQueue.empty());
    REQUIRE(!eventQueue.pop(temp));
}
