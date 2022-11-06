#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

  /////Screen definitions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String PatternsText[] = {"Off", "Music", "Matrix", "Purple & Green" ,"White &  Black" ,"Glitter", "Dot Beat", "Blur", "Fill", "Blendwave", "Beatwave", "Fade In", "Confetti",  "Juggle", "BPM" };

//map float function 
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
   return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// update the display
void updateDisplay(int mode) {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(PatternsText[mode]);
  display.display(); // actually display all of the above
}


// setup screen
void setupScreen(void) {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  // Clear the buffer
  display.clearDisplay();
  updateDisplay(0);
}