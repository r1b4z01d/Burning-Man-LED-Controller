#include "../include/screen.h"
#define SCREEN              0       // Does the device have a screen
#define DATA_PIN            3       // Main LED strip pin
#define PARALLEL_STRIPS     1       // Running parallel strips
#define PARALLEL_STRIP_PINS {5,6}   // Running parallel strips
#define BUTTON_PIN          10      // Set to 0 to disable
#define LED_TYPE            SK6812  // LED type (WS2812, WS2811, SK6812, etc.)
#define COLOR_ORDER         GRB     // Use red() green() blue() to validate color order
#define NUM_LEDS            2610    // Number of LEDs
#define BRIGHTNESS          255     // 0 to 255
#define FRAMES_PER_SECOND   0       // Set to 0 to disable throttle
#define BRIGHTNESS_ADJUST   0       // On: 1 | off: 0
#define ROTATE_MODE_SECONDS 0       // Set to 0 to disable