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
 #error Must define LED_BUILD_TYPE...  Check IDF_VER
 #endif
 
 #include "Simple_ESP32LED.h"
 
 #if LED_BUILD_TYPE == LED_BUILD_TYPE_4
 const int BLINK_VALUE = 100;
 const int RESOLUTION = 8;
 #ifdef LED_ON_WHEN_HIGH
 const int LED_ON_VALUE = 255;
 const int LED_OFF_VALUE = 0;
 #else
 const int LED_ON_VALUE = 0;
 const int LED_OFF_VALUE = 255;
 #endif
 #endif
 #if LED_BUILD_TYPE == LED_BUILD_TYPE_5
 const int BLINK_VALUE = 8000;
 const int RESOLUTION = 14;
 #ifdef LED_ON_WHEN_HIGH
 const int LED_ON_VALUE = 0xFFFF;
 const int LED_OFF_VALUE = 0;
 #else
 const int LED_ON_VALUE = 0;
 const int LED_OFF_VALUE = 0xFFFF;
 #endif
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
     stopRate();
     write(ledStatus);
 }

 void SimpleESP32_LED::write(int ledStatus)
 {
     int blinkVal = 0;
     switch (ledStatus)
     {
     case LED_ON:
         blinkVal = LED_ON_VALUE;
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
 
 // Turn off LED when timer expires
 void autoBlinkCallback(TimerHandle_t xTimer)
 {
     SimpleESP32_LED *led = static_cast<SimpleESP32_LED *>(pvTimerGetTimerID(xTimer)); // Retrieve the pointer to class
     assert(led);                                                                      // Sanity check
     led->turnLEDOff();                                                                // Forward to the real callback
 }
 
 void SimpleESP32_LED::blink(int duration)
 {
     turnLEDOn(LED_BLINK);   // (stops blinkRate)
 
     if (duration != 0)
     {
         blickOffTimer = xTimerCreate(
             "ledOff",                      // Name of timer
             duration / portTICK_PERIOD_MS, // Period of timer (in ticks)
             pdFALSE,                       // Auto-reload
             static_cast<void *>(this),     // Send a pointer to this object
             autoBlinkCallback);            // Callback function
 
         xTimerStart(blickOffTimer, portMAX_DELAY);
     }
 }

 // ---- blinkRate: a software-timed blink (2026-10-11) ---------------------------
 void SimpleESP32_LED::stopRate()
 {
     if (rateTimer != NULL)
         xTimerStop(rateTimer, 0);
     rateOnMs = rateOffMs = 0;
 }

 void SimpleESP32_LED::rateCallback(TimerHandle_t t)
 {
     SimpleESP32_LED *led = static_cast<SimpleESP32_LED *>(pvTimerGetTimerID(t));
     if (led == nullptr || led->rateOnMs == 0)
         return;   // stopped meanwhile
     led->rateLit = !led->rateLit;
     led->write(led->rateLit ? LED_ON : LED_OFF);
     uint16_t next = led->rateLit ? led->rateOnMs : led->rateOffMs;
     xTimerChangePeriod(t, pdMS_TO_TICKS(next > 0 ? next : 1), 0);   // also restarts it
 }

 void SimpleESP32_LED::blinkRate(uint16_t onMs, uint16_t offMs)
 {
     if (onMs == 0)
     {
         turnLEDOff();
         return;
     }
     if (offMs == 0)
     {
         turnLEDOn();
         return;
     }
     if (rateTimer == NULL)
     {
         rateTimer = xTimerCreate("ledRate", pdMS_TO_TICKS(onMs), pdFALSE, static_cast<void *>(this), rateCallback);
         if (rateTimer == NULL)
         {
             blink();   // no timer to be had - the plain blink will do
             return;
         }
     }
     xTimerStop(rateTimer, 0);
     rateOnMs = onMs;
     rateOffMs = offMs;
     rateLit = true;
     write(LED_ON);
     xTimerChangePeriod(rateTimer, pdMS_TO_TICKS(onMs), 0);   // starts it
 }
