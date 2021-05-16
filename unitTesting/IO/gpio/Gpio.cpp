#include <catch2/catch.hpp>

#define USE_GPIO 1
#include <IO/gpio/Gpio.h>

#define DIGITAL_1 "Digital 1"
#define DIGITAL_2 "Digital 2"
#define PWM_1 "PWM 1"
#define PWM_2 "PWM 2"

class TestableGpio : public Gpio
{
    public:
        TestableGpio() {};
        ~TestableGpio() {};
};

void createOutputs(Gpio* gpio) {
    gpio->createNewGpioOutput(DIGITAL_1, 1);
    gpio->createNewGpioOutput(DIGITAL_2, 2);

    gpio->createNewGpioPwmOutput(PWM_1, 3);
    gpio->createNewGpioPwmOutput(PWM_2, 4);
}

TEST_CASE("EventQueue setOutputs", "[EventQueue]") {
    Gpio* gpio = new TestableGpio();
    createOutputs(gpio);

    GpioData input;
    input.digitalOutputMap.insert({DIGITAL_1, 500});
    input.pwmOutputMap.insert({PWM_2, 600});
    
    auto result = gpio->setOutputs(input);

    REQUIRE(result.digitalOutputMap.at(DIGITAL_1) == 500);
    REQUIRE(result.digitalOutputMap.at(DIGITAL_2) == 0);

    REQUIRE(result.pwmOutputMap.at(PWM_1) == 0);
    REQUIRE(result.pwmOutputMap.at(PWM_2) == 600);

    // Data should carry over unless replaced

    GpioData input2;
    input2.digitalOutputMap.insert({DIGITAL_1, 400});
    input2.pwmOutputMap.insert({PWM_1, 300});

    auto result2 = gpio->setOutputs(input2);

    REQUIRE(result2.digitalOutputMap.at(DIGITAL_1) == 400);
    REQUIRE(result2.digitalOutputMap.at(DIGITAL_2) == 0);

    REQUIRE(result2.pwmOutputMap.at(PWM_1) == 300);
    REQUIRE(result2.pwmOutputMap.at(PWM_2) == 600);

    delete gpio;
}