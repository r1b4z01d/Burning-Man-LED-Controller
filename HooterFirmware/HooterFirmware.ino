#include <FastLED.h>
#define BUTTON_PIN 10  // button pin

//#include "front.h" 
//#include "wing.h" 
//#include "side.h" 
//#include "bike.h" 
#include "tent.h" 

#include "jsbutton.h" // button routine by Jeff Saltzman
#include "patterns.h" // led patterns

FASTLED_USING_NAMESPACE

uint8_t gCurrentPatternNumber = 0; // Current mode/effect/pattern index

// Mode auto rotation settings
#define ROTATE_MODES 0             // off:0 on:1
#define ROTATE_MODE_SECONDS 60     // 


void setup() {                                                                
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,3,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH );

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
 // if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
  //}

  // Clear the buffer
  //display.clearDisplay();
  //display.display();
  
  //display hootie logo
  //drawLogo();

  gCurrentPatternNumber = 0;
  //updateDisplay(gCurrentPatternNumber);

}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { matrix, rainbowWithGlitter, fill_grad, blendwave, beatwave,fadein,rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm2 };
String PatternsText[] = { "  Matrix", "  Glitter", "   Fill", " Blendwave", " Beatwave", "  Fade In", " Rainbow", " Confetti", "  Sinelon", "  Juggle", "   BPM" };

void loop()
{
  // Call the current patt\ern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  readbutton();
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

 EVERY_N_MILLISECONDS(100) {                                                 // FastLED based non-blocking FIXED delay.
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);    // AWESOME palette blending capability.
  }

  //enable buttonless mode
  if(ROTATE_MODES == 1){
    EVERY_N_SECONDS(ROTATE_MODE_SECONDS) {
      nextPattern();
      }
  }

  EVERY_N_SECONDS(5) {                                                        // Change the target palette to a random one every 5 seconds.
    uint8_t baseC = random8(255);                                             // Use the built-in random number generator as we are re-initializing the FastLED one.
    targetPalette = CRGBPalette16(CHSV(baseC+random8(0,32), 255, random8(128, 255)), CHSV(baseC+random8(0,32), 255, random8(128, 255)), CHSV(baseC+random8(0,32), 192, random8(128, 255)), CHSV(baseC+random8(0,32), 255, random8(128, 255)));
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
