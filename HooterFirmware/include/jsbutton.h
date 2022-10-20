/* 3-Way Button:  Click, Double-Click, Press+Hold
 *
 * By Jeff Saltzman
 *
 * Modified by: Bryan Ribas
 * 
 * July 4, 2022
 *
 * To keep a physical interface as simple as possible, this sketch demonstrates generating four output events from a single push-button.
 * 
 * 1) Click:  rapid press and release
 * 2) Double-Click:  two clicks in quick succession
 * 3) Press and Hold:  holding the button down
 * 
 * http://forum.arduino.cc/index.php?topic=14479.0
 *
 */


//=================================================
//  MULTI-CLICK:  One Button, Multiple Events

// Button timing variables
int debounce = 20;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250;            // max ms between clicks for a double click event
int holdTime = 1000;        // ms hold period: how long to wait for press+hold event


// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean button2Val = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean button2Last = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already

void setupButton(){
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH );
}

uint8_t checkButtons() {    
   uint8_t event = 0;
   buttonVal = digitalRead(BUTTON_PIN);
   button2Val = digitalRead(BUTTON2_PIN);

   // Button 1 pressed down
   if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;

       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button 1 released
   else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
   {        
       if (not ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               event = 2;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
   {
       event = 1;
       DCwaiting = false;
   }
   // Test for hold
   if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast)
       {
           event = 3;
           waitForUp = true;
           ignoreUp = true;
           DConUp = false;
           DCwaiting = false;
           //downTime = millis();
           holdEventPast = true;
       }
   }
    

    // Button 2 pressed down
   if (button2Val == LOW && button2Last == HIGH && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;

       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button 2 released
   else if (button2Val == HIGH && button2Last == LOW && (millis() - downTime) > debounce)
   {        
       if (not ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               event = 5;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( button2Val == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
   {
       event = 4;
       DCwaiting = false;
   }
   // Test for hold
   if (button2Val == LOW && (millis() - downTime) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast)
       {
           event = 6;
           waitForUp = true;
           ignoreUp = true;
           DConUp = false;
           DCwaiting = false;
           //downTime = millis();
           holdEventPast = true;
       }
   }
   
   buttonLast = buttonVal;
   button2Last = button2Val;
   
   return event;
} // checkButton()
