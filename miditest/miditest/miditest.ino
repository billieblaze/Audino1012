#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

#include <MIDI.h>
/*
  MIDI Input tutorial
  by Franky
  28/07/2009
  
  NOTE: for easier MIDI input reading, 
  take a look a the Callbacks example.
  
*/

#define LED 13   		// LED pin on Arduino board

void BlinkLed(byte num) { 	// Basic blink function
  for (byte i=0;i<num;i++) {
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(LED,LOW);
    delay(50);
  }
}


void setup() {
  lcd.begin(16,2);
  lcd.print("MIDI Test");
  pinMode(LED, OUTPUT);
  MIDI.begin();            	// Launch MIDI with default options
				// (input channel is default set to 1)
}

void loop() {
 lcd.setCursor(0,1);
 
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
   lcd.print("IN "); 
    switch(MIDI.getType()) {		// Get the type of the message we caught
      case NoteOn:               // If it is a Program Change
	lcd.print("note on");	// Blink the LED a number of times 
					// correponding to the program number 
					// (0 to 127, it can last a while..)
        break;
      // See the online reference for other message types
      default:
      	lcd.print("other");
      BlinkLed(1);
        break;
    }
  }
}
