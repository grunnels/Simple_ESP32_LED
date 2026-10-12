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
 
 
 typedef enum ESP32LED_MODE
 {
     LED_OFF = 0,
     LED_ON = 1,
     LED_BLINK = 2
 } esp32ledMode;
 
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
     void blink(int duration = 0);
     // 2026-10-11: a slow, visible blink timed in software - onMs lit, offMs dark,
     // repeating until turnLEDOn/turnLEDOff/blink is called. blink() above is the
     // fast PWM blink (several times a second); this one can be as slow as you like,
     // e.g. blinkRate(100, 2900) = a short flash every 3 s.
     void blinkRate(uint16_t onMs, uint16_t offMs);
 
 private:
     uint8_t ledPin;
     uint16_t frequency;
     uint16_t channel;
     TimerHandle_t blickOffTimer = NULL;
     TimerHandle_t rateTimer = NULL;
     volatile bool rateLit = false;
     volatile uint16_t rateOnMs = 0, rateOffMs = 0;
     void write(int ledStatus);   // set the LED without stopping blinkRate
     void stopRate();
     static void rateCallback(TimerHandle_t t);
 
 };
 
 #endif
 