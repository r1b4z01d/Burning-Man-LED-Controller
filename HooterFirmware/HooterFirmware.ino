#include <FastLED.h>
FASTLED_USING_NAMESPACE

// Change this to correspond to the correct device type
// Current options include  tent, wing, side, front, bike
#include "device_types/tent.h" // Set device type 

#include "include/jsbutton.h"  // Button routine by Jeff Saltzman
#include "include/patterns.h"  // Led patterns

uint8_t gCurrentPatternNumber = 0; // Current mode/effect/pattern index
// List of patterns to cycle through. Each is defined as a function in patterns.h
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { matrix, rainbowWithGlitter, dot_beat, blur, fill_grad, blendwave, beatwave, fadein, rainbow, confetti, sinelon, juggle, bpm2 };

// Setup runs on bootup
void setup() {

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // Setup button if there is one 
  if ( BUTTON_PIN <=1 ){ setupButton(); }
  
  // Setup the screen if configured
  if ( SCREEN == 1 ){ setupScreen(); }
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}

void loop()
{
  // Call the current patt\ern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  readbutton();
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  
  // insert a delay to keep the framerate modest
  if (FRAMES_PER_SECOND >= 1){
    FastLED.delay(1000/FRAMES_PER_SECOND); 
  }

  //enable mode rotation 
  if(ROTATE_MODE_SECONDS >= 1){
    EVERY_N_SECONDS(ROTATE_MODE_SECONDS) {
      nextPattern();
      }
  }
  
 // 
  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { 
    gHue++;
  } // slowly cycle the "base color" through the rainbow
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void readbutton() {                                           // Read the button and increase the mode

  uint8_t b = checkButton();

  if (b == 1) {                                               // Just a click event to advance to next pattern
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    // updateDisplay(gCurrentPatternNumber);
  }

  if (b == 2) {                                               // A double-click event to reset to 0 pattern
    gCurrentPatternNumber = 0;
    //updateDisplay(gCurrentPatternNumber);
  }

} // readbutton()

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}
