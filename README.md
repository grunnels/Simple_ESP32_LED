

# Simple_ESP32_LED

Library for LED control on ESP32.


## Description

### Initial setup

"LED_BUILD_TYPE" MUST be defined in the platformio.ini build-flags with a value of 4 for ESP-IDF 4.x, or a value of 5 for ESP-IDF 5.x
    ie. build_flags = -D LED_BUILD_TYPE=5

These routines use the underlying ledc commands.


## Interface

```cpp
#include "Simple_ESP32LED.h"
```

### Constructor

- **init(uint8_t gpio, uint16_t blinkRate = LED_MEDIUM)** Constructor,
mandatory GPIO pin and optional blink rate.  Available blink rates are LED_SLOW, LED_MEDIUM, and LED_FAST

### LED Control

- **void turnLEDOn(int ledStatus)** ledStatus = LED_OFF, LED_ON, or LED_Blick.
- **void turnLEDOn()** Turns the LED on.
- **void turnLEDOff()** Turns the LED off.
- **void blink()** Blinks the LED.


## Future

#### Must

- update documentation

#### Should

- add automated flag to check for ESP-IDF versions.
- add a given duration to turn on and off
- add ability to invert off/on logic

#### Wont (for now).

- support platforms other than ESP32


## Support

If you have questions or suggestions, please reach out to me.

Thank you
