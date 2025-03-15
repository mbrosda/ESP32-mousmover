#include <Arduino.h>

//---------------------------------------------------------------------------
// Mousemover prerequisites
//---------------------------------------------------------------------------
#include "USB.h"
#include "USBHIDMouse.h"

USBHIDMouse   Mouse;
unsigned long mousemover_nxt_move_ms = 5000;

#ifndef TEST
// regular values
int8_t        mousemover_distance    = 2;
unsigned long mousemover_interval_ms = 270000;
#else
// TEST values
int8_t        mousemover_distance    = 5;
unsigned long mousemover_interval_ms = 5000;
#endif

uint8_t       backlight_brightness_pct = 90;
unsigned long current_millis           = 0;

void          setup() {
    //-------------------------------------------------------------------
    // Initialize setup
    //-------------------------------------------------------------------
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

    //-------------------------------------------------------------------
    // Mouse Setup code
    //-------------------------------------------------------------------

    // initialize mouse control:
    Mouse.begin();
    USB.begin();

    current_millis         = millis();
    mousemover_nxt_move_ms = current_millis + mousemover_nxt_move_ms;  // give it a first move a few seconds after boot

    //-------------------------------------------------------------------
    // Finalize setup
    //-------------------------------------------------------------------
    Serial.println("End of setup");
}

void loop() {
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

    delay(10);
}