# Arduino Proxy

This is the repo for the Arduino proxy, a somewhat simple project that allows the rocket code to use an Arduino for
generic input and outputs. See
the [documentation for more information](https://github.com/uorocketry/rocket-code-2020/wiki/RPi-to-Arduino-Communication)
.

# Build Instructions (Linux)

1. Install PlatformIO Core: https://docs.platformio.org/en/latest/core/installation.html#installer-script
    - While it is possible to get it working with IDEs such as VSCode and CLion, from the team's experience there are
      often problems encountered while doing this. For general development it is recommended to get the PlatformIO
      integration with IDEs, but it is not needed to build the project.

2. Install protobuf dependencies. This may be different on other non Ubuntu-based distros:
   `sudo apt update && sudo apt install protobuf-compiler nanopb`

3. Build the project: `pio run`

4. Upload to a connected Arduino: `pio run --target upload`
