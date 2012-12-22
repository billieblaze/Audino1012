#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgmspace.h>
#include <Timer2.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Wire.h> 
#include <MIDI.h>
#include <Potentiometer.h>
#include <AnalogButtons.h>

#include <I2C_eeprom.h>

#include "MenuEntry.h"
#include "MenuLCD.h"
#include "MenuManager.h"


void setup(){

  disableInterrupts();
  
//  Serial.begin(9600);
    setupMenu();
    setupDAC();
    setupADC();
    setupMIDI();
    setupInterrupt();   

    changeWave(0,1, 128, 0);   
    enableInterrupts();

  //Serial.println(availableMemory());
 //Serial.println(freeRam());
}

void loop(){ 

//sampleEnd = 50;
  //triangle 
  //changeWave(0,1,128,0);
  //Square changeWave(128,1,128,0);
//envState[0] = true;  
//r  changeWave(cnt * 10, 4, cnt * 20, 10);  // start point, group, steps, randomizer  
//  cnt++;
    checkKeys();
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
