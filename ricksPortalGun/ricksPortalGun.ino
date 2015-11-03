// Arduino // Teensy sketch for ligts on in a Portal Gun
// Lithochasm 2015 -- www.wolfnetarchives.com
// Based on code from http://www.thingiverse.com/thing:1100601
// and https://github.com/pomeroyb/PortalGun


/*
************* Required Libraries *************
* Adafruit_GFX - https://github.com/adafruit/Adafruit-GFX-Library
* Adafruit_LEDBackpack - https://github.com/adafruit/Adafruit-LED-Backpack-Library
* TinyWire if using a trinket
*/

/*
**** Hardware ****
* Adafruit Trinket or Teensy
* LED's
* Adafruit 7 Segment LCD Backpack https://www.adafruit.com/products/878
*/


// Default if you are using an arduino trinket is to use TinyWireM.h. If you are using an
// arduino or teensy comment out the tinywire include and uncomment the Wire.h line.

//#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"


// Set up the 7 Segemnt LED display
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
alpha4.begin(0x70);  // pass in the address for the LED display
alpha4.blinkRate(0); // disables blinking of the display
alpha4.writeDisplay(); // clears display

// Set up the LED / Button pins
#define topBulbPin           1 
#define frontBulbPin         3 
#define buttonPin            4

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int ledValue = LOW;
long ledStartTime = 0;
long ledBlinkInterval = 1000;

void setup() {

  //Set up pin modes
  pinMode(topBulbPin, OUTPUT);
  pinMode(frontBulbPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  digitalWrite(buttonPin, LOW); // enable low pulldown on this pin
  digitalWrite(frontBulbPin, LOW);
  digitalWrite(topBulbPin, HIGH);
  
}



void loop() { 
    
    buttonValue = digitalRead(buttonPin); // Checks if the button is pressed

    alpha4.writeDigitAscii(0, 'C');
    alpha4.writeDigitAscii(1, '1');
    alpha4.writeDigitRaw(3, 0x4F); // If i try to write an ascii 3 here is displays some other charecter, thus using the raw version here
    alpha4.writeDigitAscii(4, '7');
    alpha4.writeDisplay();


   if (buttonValue == HIGH) {  // If button is pressed turn on frontLed and blink display
   digitalWrite(frontBulbPin, HIGH);
   alpha4.blinkRate(1);
   }
  
  else { // Else turn off front led's and stop blinking display
  digitalWrite(frontBulbPin, LOW);
  alpha4.blinkRate(0);
  }

  analogWrite(topBulbPin, brightness); // Fades / Breathes the top LEDs in the power canister
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);

}  



