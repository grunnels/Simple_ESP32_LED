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

#define LED_BUILD_TYPE_4 4 // idf_ver prior to 5.x
#define LED_BUILD_TYPE_5 5 // idf_ver post 5.x

#ifndef LED_BUILD_TYPE
#error "Must define LED_BUILD_TYPE..."
#endif

#include "Simple_ESP32LED.h"

#if LED_BUILD_TYPE == LED_BUILD_TYPE_4
const int BLINK_VALUE = 100;
const int RESOLUTION = 8;
const int LED_OFF_VALUE = 255;
#endif
#if LED_BUILD_TYPE == LED_BUILD_TYPE_5
const int BLINK_VALUE = 8000;
const int RESOLUTION = 14;
const int LED_OFF_VALUE = 16383;
#endif

int rootChannel = 0;

void SimpleESP32_LED::init(uint8_t lp, uint16_t blinkRate)
{
    channel = rootChannel;
    ledPin = lp;
    rootChannel++;
    rootChannel++;
    // IF (IDF_VER MATCHES "v4.") can I use this in the future??

#if LED_BUILD_TYPE == LED_BUILD_TYPE_5
    ledcAttachChannel(ledPin, blinkRate, RESOLUTION, channel);
#endif
#if LED_BUILD_TYPE == LED_BUILD_TYPE_4
    ledcSetup(channel, blinkRate, RESOLUTION);
    ledcAttachPin(ledPin, channel);
#endif
}

void SimpleESP32_LED::turnLEDOn(int ledStatus)
{
    int blinkVal = 0;
    switch (ledStatus)
    {
    case LED_ON:
        blinkVal = 0;
        break;
    case LED_OFF:
        blinkVal = LED_OFF_VALUE;
        break;
    case LED_BLINK:
        blinkVal = BLINK_VALUE;
        break;
    }
#if LED_BUILD_TYPE == LED_BUILD_TYPE_5
    ledcWrite(ledPin, blinkVal);
#endif
#if LED_BUILD_TYPE == LED_BUILD_TYPE_4
    ledcWrite(channel, blinkVal);
#endif
}

void SimpleESP32_LED::turnLEDOn()
{
    turnLEDOn(LED_ON);
}

void SimpleESP32_LED::turnLEDOff()
{
    turnLEDOn(LED_OFF);
}

void SimpleESP32_LED::blink()
{
    turnLEDOn(LED_BLINK);
}
