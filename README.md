# ci-clyde
A custom extension module for [Clyde](https://www.kickstarter.com/projects/metamanda/clyde-an-expressive-lamp-for-creative-homes), to check a CI server for build status and set the eye color accordingly.

## design
Clyde prominantly features a large "eye" backlit by a few RGB LEDs, we can use this to display at-a-glance information about the current state of important CI builds for our team.

To start, this will focus on communicating with a Bamboo CI server, though in the future may be extended to any CI tool with a REST interface.

Checking the status of one plan, we can tell if it is actively building at the moment, or not. Similarly, we can tell if the most recently completed build was successful or not. The success/failure status will be conveyed by changing the hue of the light, with green denoting success, and red denoting failure. When a build is underway, we will pulse the light to indicate activity, keeping the color of the previous build until it finishes, then updaiting as necessary.

## development
Clyde runs on the Atmel MEGA32U4, which is fully Arduino compatible. This makes it relatively easy to load custom code onto the chip and achieve whatever behavior we'd like from the lights.
Since Clyde does not have any wireless communication included, additional hardware is needed to accomplish the goal of communicating with a CI web server. The original intention of the kickstarter was to include extension modules that would add functionality, and so this project aims to create a custom module to fit that pattern (roughly).

### environment
Since Clyde is rather old, the official repository of code does not work smoothly with the latest version of the Arduino IDE and avrdude. Rather than try to update it, older versions of the Arduino IDE are available [from the Arduino website](https://www.arduino.cc/en/main/OldSoftwareReleases), and using 1.0.5-r2 seems to work without issue.

That being said, programming the ESP8266 is much easier with the latest libraries, especially considering that I2C support was not added to the library until ~2018, so programming for the wifi add-on module should be done in whatever most recent version is available, with the latest ESP8266 boards and libraries.
