#include <IO/EventQueue.h>
#include <catch2/catch.hpp>

TEST_CASE("EventQueue push and pop", "[EventQueue]")
{
    auto eventQueue = new EventQueue();

    REQUIRE(eventQueue->pop() == -1);

    eventQueue->push(100);
    eventQueue->push(102);
    eventQueue->push(104);

    REQUIRE(eventQueue->pop() == 100);
    REQUIRE(eventQueue->pop() == 102);
    REQUIRE(eventQueue->pop() == 104);
    REQUIRE(eventQueue->pop() == -1);
}
