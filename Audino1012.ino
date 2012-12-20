#include <WProgram.h>
#include <Timer2.h>

#include <LiquidCrystal.h>
#include <phi_interfaces.h>
#include <phi_prompt.h>
#include <SPI.h>
#include <Wire.h> 
#include <MIDI.h>
#include <Potentiometer.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
boolean showMenu = 1;

#include <I2C_eeprom.h>
I2C_eeprom ee(0x50);


// ADC
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
int ADCOffset = 512;
word ADCValue; 

// DAC 
#define SLAVESELECT 3

// interrupt
unsigned int tcnt2; 
boolean div32;
boolean div16;
boolean div8;
boolean div4;
boolean div2;

volatile boolean f_sample;

//wavetable

volatile byte ibb;

int samplePosition = 0;
int sampleSize = 128;
word sample[128];  // Audio Memory Array 
boolean reinitializeWavetable = 0;

int sampleStart = 0;  
int sampleEnd = 63;
int sampleOffset = 0;
int sampleDelay = 0;
int sampleVelocity = 127;

int sampleShiftLeft = 0;
int sampleShiftRight = 0;

// shift DAC Data
int bitShiftLeft = 0;
int bitShiftRight = 16;

// Envelope

int attackRate = 1;
int decayRate = 10;
int sustainLevel = 2000;
int releaseRate = 50;

// shorthand for our envelope stages
const int DONE = 0;
const int ATTACK = 1;
const int DECAY = 2;
const int SUSTAIN = 3;
const int RELEASE = 4;

int gateState[] = {0,0};
int envState[] = {0,0};
word ADSRSample[] = {0,0};
word envelopeValue[] = {0,0,0,0};
int envelopeShift = 6;


void setup(){

  disableInterrupts();
  Serial.begin(57600);
  setupLCDKeypad();
  setupWavetable();  
//  Serial.println("setup ad/da");
  setupDAC();
  setupADC();
//  Serial.println("setup interrupt");
  setupMIDI();
// Serial.println("setup MIDI");
  
  setupInterrupt();   
//changeWave(0,1, 128, 0);   
  
  
  enableInterrupts();

  Serial.println("BEGIN!");
    
    
 
}

int cnt = 0;
void loop(){ 

//sampleEnd = 50;
  //triangle 
  //changeWave(0,1,128,0);
//  envState[0] = 1;
  //Square changeWave(128,1,128,0);
  
//r  changeWave(cnt * 10, 4, cnt * 20, 10);  // start point, group, steps, randomizer  
//  cnt++;
  // if (showMenu == 1){ 
     top_menu(); 
  // }
 
 }
