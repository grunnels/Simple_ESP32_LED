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

#include "Simple_ESP32LED.h"

const int BLINK_VALUE = 100;
int rootChannel = 0;

void SimpleESP32_LED::init(uint8_t ledPin)
{
    init(ledPin, LED_MEDIUM);
}

void SimpleESP32_LED::init(uint8_t ledPin, uint16_t blinkRate)
{
    channel = rootChannel;
    rootChannel++;
    rootChannel++;
    ledcSetup(channel, blinkRate, RESOLUTION);
    ledcAttachPin(ledPin, channel);
}

void SimpleESP32_LED::turnLEDOn(int ledStatus)
{
    int blinkVal = 0;
    switch (ledStatus)
    {
    case LED_ON:
        blinkVal = 255;
        break;
    case LED_OFF:
        blinkVal = 0;
        break;
    case LED_BLINK:
        blinkVal = BLINK_VALUE;
        break;
    }
    ledcWrite(channel, blinkVal);
}

void SimpleESP32_LED::turnLEDOn(int ledStatus, long duration)
{
    turnLEDOn(ledStatus);
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
