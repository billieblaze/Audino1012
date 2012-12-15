#include <WProgram.h>
#include <Timer2.h>

#include <LiquidCrystal.h>
#include <phi_interfaces.h>
#include <phi_prompt.h>
#include <SPI.h>
#include <Wire.h> 


LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

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
int sampleDelay=0;

int sampleShiftLeft = 0;
int sampleShiftRight = 0;

// shift DAC Data
int bitShiftLeft = 0;
int bitShiftRight = 5;

// lcdkeypad
#define lcd_rows 2
#define lcd_columns 16

#define buttons_per_column 5 // Each analog pin has five buttons with resistors.
#define buttons_per_row 1 // There are two analog pins in use.

char analog_mapping[]={'U','D','L','R','B'}; // This is an analog keypad.
byte analog_pins[]={0}; // The pin numbers are analog pin numbers.
int values[]={142, 327, 504, 0, 741}; //These numbers need to increase monotonically. The 342 works better on my setup but you will need to change it back.
phi_analog_keypads analog_keypad(analog_mapping, analog_pins, values, buttons_per_row, buttons_per_column);


// This serial keypad is for debugging.
phi_serial_keypads debug_keypad(&Serial,115200);

// The following sets up function keys for phi_prompt library
char up_keys[]={"U"}; ///< All keys that act as the up key are listed here.
char down_keys[]={"D"}; ///< All keys that act as the down key are listed here.
char left_keys[]={"L"}; ///< All keys that act as the left key are listed here.
char right_keys[]={"R"}; ///< All keys that act as the right key are listed here.
char enter_keys[]={"B"}; ///< All keys that act as the enter key are listed here.
char escape_keys[]={"A"}; ///< All keys that act as the escape key are listed here.
char * function_keys[]={up_keys,down_keys,left_keys,right_keys,enter_keys,escape_keys}; ///< All function key names are gathered here fhr phi_prompt.

// The following adds all available keypads as inputs for phi_prompt library
multiple_button_input * keypads[]={&analog_keypad, &debug_keypad,0};


// menu

// Menu texts
PROGMEM prog_char top_menu_item00[]="Oscillator";
PROGMEM prog_char top_menu_item01[]="Envelope";
PROGMEM prog_char top_menu_item02[]="Effects";
PROGMEM prog_char top_menu_item03[]="_2";
PROGMEM prog_char top_menu_item04[]="_3";
PROGMEM const char *top_menu_items[] = {top_menu_item00, top_menu_item01, top_menu_item02, top_menu_item03, top_menu_item04};

PROGMEM prog_char sub_menu_1_item00[]="Waveform";
PROGMEM prog_char sub_menu_1_item01[]="WT Start";
PROGMEM prog_char sub_menu_1_item02[]="WT End";
PROGMEM prog_char sub_menu_1_item03[]="WT Offset";
PROGMEM prog_char sub_menu_1_item04[]="WT Delay";
PROGMEM prog_char sub_menu_1_item05[]="Back to main menu";
PROGMEM const char *sub_menu_1_items[] = {sub_menu_1_item00, sub_menu_1_item01, sub_menu_1_item02, sub_menu_1_item03, sub_menu_1_item04, sub_menu_1_item05};

PROGMEM prog_char waveform_00[]="Triangle"; 
PROGMEM prog_char waveform_01[]="Square"; 
PROGMEM prog_char waveform_02[]="Saw"; 
PROGMEM prog_char waveform_03[]="Ramp Up"; 
PROGMEM prog_char waveform_04[]="Ramp Down"; 
PROGMEM prog_char waveform_05[]="Sine"; 
PROGMEM const char *waveform_items[]= {waveform_00,waveform_01,waveform_02,waveform_03,waveform_04,waveform_05}; 


PROGMEM prog_char sub_menu_2_item00[]="Trigger";
PROGMEM prog_char sub_menu_2_item01[]="Attack";
PROGMEM prog_char sub_menu_2_item02[]="Decay";
PROGMEM prog_char sub_menu_2_item03[]="Sustain";
PROGMEM prog_char sub_menu_2_item04[]="Release";
PROGMEM prog_char sub_menu_2_item05[]="Back to main menu";
PROGMEM const char *sub_menu_2_items[] = {sub_menu_2_item00, sub_menu_2_item01, sub_menu_2_item02, sub_menu_2_item03, sub_menu_2_item04, sub_menu_2_item05};




PROGMEM prog_char menu_style00[]="Arrow/dot indicator on";
PROGMEM prog_char menu_style01[]="Index1 on-excludes index2";
PROGMEM prog_char menu_style02[]="Index2 on-excludes index1";
PROGMEM prog_char menu_style03[]="Autoscroll long items on";
PROGMEM prog_char menu_style04[]="Flashing cursor on";
PROGMEM prog_char menu_style05[]="Center on item on";
PROGMEM prog_char menu_style06[]="Scroll bar to the right on";
PROGMEM const char *menu_styles[] = {menu_style00, menu_style01, menu_style02, menu_style03, menu_style04, menu_style05, menu_style06};

//This program is the main menu. It handles inputs from the keys, updates the menu or executes a certain menu function accordingly.
int global_style=49; // This is the style of the menu

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
int envelopeShift = 6;
int cnt = 0;


void setup(){

  disableInterrupts();
  Serial.begin(57600);
  setupLCDKeypad();
  setupWavetable();  
  Serial.println("setup ad/da");
  setupDAC();
  setupADC();
  Serial.println("setup interrupt");
  setupInterrupt();   
  enableInterrupts();

  Serial.println("BEGIN!");
}

void loop(){ 
  gateState[0] = 1;
  delay(400);
  gateState[0] = 0;
  delay(1500);


//  bitShiftRight = 2;


  sampleDelay = 40;  
//sampleStart = 10; 
//sampleEnd = 50;
  //triangle 
  //changeWave(0,1,128,0);
  //Square changeWave(128,1,128,0);
  changeWave(cnt * 1, 3, cnt * 5, 20);  // start point, group, steps, randomizer

  cnt++;

//  top_menu(); 
  
 }
