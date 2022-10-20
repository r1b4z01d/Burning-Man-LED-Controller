#include "../include/screen.h"

#define SCREEN              1       // Does the device have a screen
#define DATA_PIN            3       // Main LED strip pin
#define BUTTON_PIN          11       // Set to 0 to disable
#define BUTTON2_PIN         10       // Set to 0 to disable
#define BRIGHTNESS_PIN      0       // Set to 0 to disable
#define LED_TYPE            WS2811  // LED type (WS2812, WS2811, SK6812, etc.)
#define COLOR_ORDER         GRB     // Use red() green() blue() to validate color order
#define NUM_LEDS            64      // Number of LEDs
#define BRIGHTNESS          255     // 0 to 255
#define FRAMES_PER_SECOND   30      // Set to 0 to disable throttle
#define ROTATE_MODE_SECONDS 0       // Set to 0 to disable

CRGB leds[NUM_LEDS];

// setup led strips 
void setupLEDStrips(){
    FastLED.addLeds<LED_TYPE,6,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,5,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,4,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,3,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,2,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}