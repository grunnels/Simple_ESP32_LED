/******************************************************************************
 *
 * This is a library for LED's on an ESP32
 *
 *
 * Feel free to use or change it
 *
 * Please let me know if you find any bugs
 *
 * Written by Greg Runnels
 *
 *
 ******************************************************************************/

#ifndef SIMPLE_ESP32LED_h
#define SIMPLE_ESP32LED_h

#include <Arduino.h>

#ifdef LED_ON_WHEN_HIGH
typedef enum ESP32LED_MODE
{
    LED_OFF = 0,
    LED_ON = 1,
    LED_BLINK = 2
} esp32ledMode;
#else
typedef enum ESP32LED_MODE
{
    LED_OFF = 1,
    LED_ON = 0,
    LED_BLINK = 2
} esp32ledMode;
#endif

typedef enum ESP32LED_BLINK
{
    LED_SLOW = 4,
    LED_MEDIUM = 8,
    LED_FAST = 16
} esp32ledBlink;

class SimpleESP32_LED
{
public:
    void init(uint8_t lp, uint16_t blinkRate = LED_MEDIUM);
    void turnLEDOn(int ledStatus);
    void turnLEDOn();
    void turnLEDOff();
    void blink();

private:
    uint8_t ledPin;
    uint16_t frequency;
    uint16_t channel;
};

#endif
