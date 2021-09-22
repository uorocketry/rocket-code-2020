# Arduino Proxy

This is the repo for the Arduino proxy, a somewhat simple project that allows the rocket code to use an Arduino for
generic input and outputs. See
the [documentation for more information](https://github.com/uorocketry/rocket-code-2020/wiki/RPi-to-Arduino-Communication)
.

## Windows

If you plan on flashing the Arduino, you can't use WSL and just follow the Linux instructions like with the rocket code.

## Installing dependencies

1. Install PlatformIO Core: https://docs.platformio.org/en/latest/core/installation.html#installer-script
    - While it is possible to get it working with IDEs such as VSCode and CLion, from the team's experience there are
      often problems encountered while doing this. For general development it is recommended to get the PlatformIO
      integration with IDEs, but it is not needed to build the project.

### If on Linux

2. Install protobuf dependencies. This may be different on other non Ubuntu-based distros:
   `sudo apt update && sudo apt install protobuf-compiler nanopb`

### If on Windows

2. Install nanopb to your path
  - Download a build from https://jpa.kapsi.fi/nanopb/download/
  - Extract `generator-bin` to some folder
  - [Add the folder to your PATH](https://stackoverflow.com/questions/44272416/how-to-add-a-folder-to-path-environment-variable-in-windows-10-with-screensho)

Note: If the platform-io installer script doesn't work, try installing with `pip install -U platformio`

## Building

3. Build the project: `pio run`

4. Upload to a connected Arduino: `pio run --target upload`

## Development

Make sure to open the Arduino project in another VSCode window and make sure it is not running in WSL if on Windows.