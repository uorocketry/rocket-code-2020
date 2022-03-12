#include <catch2/catch.hpp>

#define USE_GPIO 1
#include <IO/gpio/Gpio.h>

#define DIGITAL_1 "Digital 1"
#define DIGITAL_2 "Digital 2"
#define PWM_1 "PWM 1"
#define PWM_2 "PWM 2"

class FakeGpio : public Gpio
{
  public:
    FakeGpio(){};
    ~FakeGpio(){};
};

void createOutputs(Gpio *gpio)
{
    gpio->createNewGpioOutput(DIGITAL_1, 1);
    gpio->createNewGpioOutput(DIGITAL_2, 2);

    gpio->createNewGpioPwmOutput(PWM_1, 3, 250, false);
    gpio->createNewGpioPwmOutput(PWM_2, 4, 0, false);
}

TEST_CASE("EventQueue setOutputs", "[EventQueue]")
{
    Gpio *gpio = new FakeGpio();
    createOutputs(gpio);

    GpioData input;
    input.digitalMap.insert({DIGITAL_1, 500});
    input.pwmMap.insert({PWM_2, 600});

    auto result = gpio->setOutputs(input);

    REQUIRE(result.digitalMap.at(DIGITAL_1) == 500);
    REQUIRE(result.digitalMap.at(DIGITAL_2) == -1);

    REQUIRE(result.pwmMap.at(PWM_1) == -1);
    REQUIRE(result.pwmMap.at(PWM_2) == 600);

    // Data should carry over unless replaced

    GpioData input2;
    input2.digitalMap.insert({DIGITAL_1, 400});
    input2.pwmMap.insert({PWM_1, 300});

    auto result2 = gpio->setOutputs(input2);

    REQUIRE(result2.digitalMap.at(DIGITAL_1) == 400);
    REQUIRE(result2.digitalMap.at(DIGITAL_2) == -1);

    REQUIRE(result2.pwmMap.at(PWM_1) == 300);
    REQUIRE(result2.pwmMap.at(PWM_2) == 600);

    delete gpio;
}