#include <Arduino.h>

// clang-format off
#ifdef OTA
    #include <WiFi.h>
    #include <ArduinoOTA.h>
    #include <ESPmDNS.h>

    #include <myWiFi_secrets.h>
    #include <myWifi_init.h>
#endif
// clang-format on

//---------------------------------------------------------------------------
// Mousemover prerequisites
//---------------------------------------------------------------------------
#ifndef USB_DISABLED
    #include "USB.h"
    #include "USBHIDMouse.h"

USBHIDMouse   Mouse;
unsigned long mousemover_nxt_move_ms = 5000;

    #ifndef TEST
// regular values
bool          TESTMODE               = false;
int8_t        mousemover_distance    = 2;
unsigned long mousemover_interval_ms = 270000;
    #else
// TEST values
bool          TESTMODE               = true;
int8_t        mousemover_distance    = 5;
unsigned long mousemover_interval_ms = 5000;
    #endif
#endif  // USB_DISABLED

uint8_t       backlight_brightness_pct = 90;
unsigned long current_millis           = 0;
bool          OTAinProgress            = false;  // used to stop anything else after OTA update has been started

// ################################################################################################################################
// setup
// ################################################################################################################################
void setup() {
    //-------------------------------------------------------------------
    // Initialize setup
    //-------------------------------------------------------------------

    if (TESTMODE) {
        delay(5000);  // give time to connect serial monitor
    }

    Serial.begin(115200);
    Serial.println("Start of setup");

    //-------------------------------------------------------------------
    // turn off builtin LED
    //-------------------------------------------------------------------

#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
#endif
#ifdef RGB_BUILTIN
    neopixelWrite(RGB_BUILTIN, 0, 0, 0);  // Off / black
#endif

    current_millis = millis();

//-------------------------------------------------------------------
// WiFi and OTA setup
//-------------------------------------------------------------------
#if defined(OTA)
    setup_wifi();
    #include <myOTA_setup.h>
#endif

//-------------------------------------------------------------------
// Mouse Setup code
//-------------------------------------------------------------------
#ifndef USB_DISABLED
    //---------------------------
    // initialize USB device name
    //---------------------------
    #ifdef USB_PRODUCT
    USB.productName(USB_PRODUCT);
        #ifdef USB_MANUFACTURER
    USB.manufacturerName(USB_MANUFACTURER);
    USB.productName(((String)USB_MANUFACTURER + ' ' + USB_PRODUCT).c_str());
        #endif
    #endif

    //-------------------------
    // initialize mouse control
    //-------------------------
    Mouse.begin();
    USB.begin();
    mousemover_nxt_move_ms = current_millis + mousemover_nxt_move_ms;  // give it a first move a few seconds after boot

#endif  // USB_DISABLED

    //-------------------------------------------------------------------
    // Finalize setup
    //-------------------------------------------------------------------
    Serial.println("End of setup");
}

// ################################################################################################################################
// loop
// ################################################################################################################################

void loop() {
//-------------------------------------------------------------------
// WiFi / OTA handler
//-------------------------------------------------------------------
#ifdef OTA
    #include <myWifi_handler.h>
    ArduinoOTA.handle();
#endif

    if (OTAinProgress == false) {
#ifndef USB_DISABLED
        //-----------------------------------
        // handler to periodically move mouse
        //-----------------------------------
        current_millis = millis();
        if (current_millis > mousemover_nxt_move_ms) {
            mousemover_nxt_move_ms = current_millis + mousemover_interval_ms;
            Mouse.move(mousemover_distance, 0, 0);

            // Serial.printf("moved %d pixel\n", mousemover_distance);

            mousemover_distance = -mousemover_distance;  // revert direction for next move

            //-----------------------------------
            // flash LED
            //-----------------------------------

    #ifdef LED_BUILTIN
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
    #endif

    #ifdef RGB_BUILTIN
            neopixelWrite(RGB_BUILTIN, 0, 0, 255);  // Blue
            delay(100);
            neopixelWrite(RGB_BUILTIN, 0, 0, 0);  // Off / black
    #endif
        }
#endif  // USB_DISABLED

        delay(10);
        if (TESTMODE) {
            Serial.printf(".");
        }
    }
}
