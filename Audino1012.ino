#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pgmspace.h>
#include <Timer2.h>
#include <LiquidCrystal.h>

#include "MenuEntry.h"
#include "MenuLCD.h"
#include "MenuManager.h"

#include <SPI.h>
#include <Wire.h> 
#include <MIDI.h>
#include <Potentiometer.h>

#include <AnalogButtons.h>

// Keypad
AnalogButtons analogButtons(0, 700, &handleButtons);
Button b_left = Button(2, 500,510);
Button b_up = Button(3, 140, 148);
Button b_down = Button(4, 325, 334);
Button b_right = Button(5, 0, 10);

// Default hold duration is 1 second, lets make it 5 seconds for button5
Button b_enter = Button(1, 738, 747);

// Menu

MenuLCD g_menuLCD(8, 9, 4, 5, 6, 7, 16,2); 
MenuManager g_menuManager( &g_menuLCD);//pass the g_menuLCD object to the g_menuManager with the & operator.

 boolean g_isDisplaying = true; 

 boolean g_updateLabels = false; 
 boolean g_updateValues = false; 
 
#include <I2C_eeprom.h>
I2C_eeprom ee(0x50);


// ADC
//#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
//#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
//int ADCOffset = 512;
//word ADCValue; 

// DAC 
#define SLAVESELECT 3

// interrupt
boolean div32;
boolean div16;
boolean div8;
boolean div4;

//volatile boolean f_sample;

//wavetable

volatile byte ibb;
volatile byte samplePosition = 0;
word sample[128];  // Audio Memory Array 

int sampleStart = 0;  
int sampleEnd = 128;
int sampleOffset = 0;
int sampleDelay = 0;
int sampleVelocity = 127;

int sampleShiftLeft = 0;
int sampleShiftRight = 0;

// shift DAC Data
int bitShiftLeft = 0;
int bitShiftRight = 16;

// Envelope
// shorthand for our envelope stages
const byte DONE = 0;
const byte ATTACK = 1;
const byte DECAY = 2;
const byte SUSTAIN = 3;
const byte RELEASE = 4;

boolean gateState[] = {0,0};
byte envState[] = {0,0};
byte ADSRSample[] = {0,0};


int attackRate[] = {1, 200};
int decayRate[] = {10, 100};
int sustainLevel[] = {255, 255};
int releaseRate[] = {50, 200};


void setup(){

  disableInterrupts();
  
  Serial.begin(9600);
    setupMenu();
    setupDAC();
    setupADC();
    setupMIDI();
    setupInterrupt();   

    changeWave(0,1, 128, 0);   
    enableInterrupts();

//  Serial.println("BEGIN!");
Serial.println(availableMemory());
 
}

void loop(){ 

//sampleEnd = 50;
  //triangle 
  //changeWave(0,1,128,0);
  //Square changeWave(128,1,128,0);
//envState[0] = true;  
//r  changeWave(cnt * 10, 4, cnt * 20, 10);  // start point, group, steps, randomizer  
//  cnt++;
  analogButtons.checkButtons();

 }
 
 int availableMemory(){
int size = 2048;
byte *buf;
while ((buf = (byte *) malloc(--size)) == NULL);
free(buf);
return size;
}

