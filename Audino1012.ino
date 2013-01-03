#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgmspace.h>
#include <avr/eeprom.h>


#include <Timer2.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Wire.h> 
#include <MIDI.h>
#include <Potentiometer.h>
#include <AnalogButtons.h>
#include <digitalWriteFast.h>

#include <I2C_eeprom.h>

#include "MenuEntry.h"
#include "MenuLCD.h"
#include "MenuManager.h"

// these vars are here because the menu requires them, but they've not been included by wavetable.ino yet
int sampleStart = 0;  
int sampleEnd = 128;
int sampleOffset = 0;
int sampleDelay = 0;

// shift DAC Data
int bitShiftLeft = 0;
int bitShiftRight = 4;

void setup(){

  disableInterrupts();
  
   // Serial.begin(9600);
    setupMenu();
    setupDAC();
    setupADC();
    setupMIDI();
    setupInterrupt();   
    enableInterrupts();

  //Serial.println(availableMemory());
  // Serial.println(freeRam());
}

void loop(){ 
  
  // envOn(0);
  // delay(2000);
  // envOff(0);
  // delay(10000);
  
  //  cnt++;
    checkKeys();
    
  /*Serial.println("AvailableMemory");
  Serial.print(availableMemory());
  Serial.print("--");
  Serial.println(freeRam());*/
 }
 
int availableMemory(){
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL);
    free(buf);
    return size;
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
