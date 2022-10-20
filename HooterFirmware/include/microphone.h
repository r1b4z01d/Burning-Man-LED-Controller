#define MIC_PIN           A3    // Analog port for microphone
#define MIC2_PIN          A2    // Analog port for microphone

#define DC_OFFSET  0                                          // DC offset in mic signal - if unusure, leave 0
                                                              // I calculated this value by serialprintln lots of mic values
uint8_t NOISE   =  30;     //todo                             // Noise/hum/interference in mic signal and increased value until it went quiet
#define SAMPLES   30                                          // Length of buffer for dynamic level adjustment
#define TOP       57                                          // Allow dot to go slightly off scale
uint8_t PEAK_FALL = 10;  //todo                               // Rate of peak falling dot

byte
  peak      = 0,                                              // Used for falling dot
  dotCount  = 0,                                              // Frame counter for delaying dot-falling speed
  volCount  = 0;                                              // Frame counter for storing past volume data
int
  vol[SAMPLES],                                               // Collection of prior volume samples
  lvl       = 10,                                             // Current "dampened" audio level
  minLvlAvg = 0,                                              // For dynamic adjustment of graph low & high
  maxLvlAvg = 512;

  void music(){
    // Debug print out
    Serial.println("music");


  uint8_t  i;
  uint16_t minLvl, maxLvl;
  int      n, height;
  int userBrightness=255;
  NOISE = 30;
  PEAK_FALL = 10;
  n = analogRead(MIC_PIN);                                    // Raw reading from mic
  n = abs(n - 512 - DC_OFFSET);                               // Center on zero

  Serial.println(n);
  
  n = (n <= NOISE) ? 0 : (n - NOISE);                         // Remove noise/hum
  lvl = ((lvl * 7) + n) >> 3;                                 // "Dampened" reading (else looks twitchy)
 
  // Calculate bar height based on dynamic min/max levels (fixed point):
  height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);
 
  if (height < 0L)       height = 0;                          // Clip output
  else if (height > TOP) height = TOP;
  if (height > peak)     peak   = height;                     // Keep 'peak' dot at top
 

 
  // Color pixels based on rainbow gradient
  for (i=0; i<57; i++) {
    if (i >= height) {
          if(i<=55){ 
      leds[i].setRGB( 0, 0,0);
          }
    }
    else {
          if(i<=55){ 
      leds[i] = CHSV(map(i,0,30-1,0,255), 255, userBrightness);
          }
    }
      }

  // Draw peak dot  
  if (peak > 0 && peak <= NUM_LEDS-1){
    leds[peak] = CHSV(map(peak,0,57-1,0,255), 255, 255);
  }

// Every few frames, make the peak pixel drop by 1:
 
    if (++dotCount >= PEAK_FALL) {                            // fall rate 
      if(peak > 0) peak--;
      dotCount = 0;
    }
  
  vol[volCount] = n;                                          // Save sample for dynamic leveling
  if (++volCount >= SAMPLES) volCount = 0;                    // Advance/rollover sample counter
 
  // Get volume range of prior frames
  minLvl = maxLvl = vol[0];
  for (i=1; i<SAMPLES; i++) {
    if (vol[i] < minLvl)      minLvl = vol[i];
    else if (vol[i] > maxLvl) maxLvl = vol[i];
  }
  // minLvl and maxLvl indicate the volume range over prior frames, used
  // for vertically scaling the output graph (so it looks interesting
  // regardless of volume level).  If they're too close together though
  // (e.g. at very low volume levels) the graph becomes super coarse
  // and 'jumpy'...so keep some minimum distance between them (this
  // also lets the graph go to zero when no sound is playing):
  if((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
  minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6;                 // Dampen min/max levels
  maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6;                 // (fake rolling average)
  
  FastLED.show();                         // Power managed FastLED display       
}
