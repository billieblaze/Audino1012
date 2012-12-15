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

int wavetablePosition = 0;
byte wavetable[64];  // Audio Memory Array 
boolean reinitializeWavetable = 1;

int wavetableStart = 0;  
int wavetableEnd = 63;
int wavetableOffset = 0;
int wavetableDelay=0;

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

// Envelope
volatile const uint16_t attack[] = {
  0, 1, 3, 5, 7, 9, 11, 13, 14, 16, 18, 20, 22, 23, 25, 27,
  29, 30, 32, 34, 35, 37, 39, 41, 42, 44, 45, 47, 49, 50, 52, 54,
  55, 57, 58, 60, 61, 63, 65, 66, 68, 69, 71, 72, 74, 75, 76, 78,
  79, 81, 82, 84, 85, 87, 88, 89, 91, 92, 93, 95, 96, 98, 99, 100,
  102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 114, 116, 117, 118, 119, 121,
  122, 123, 124, 125, 126, 128, 129, 130, 131, 132, 133, 135, 136, 137, 138, 139,
  140, 141, 142, 143, 144, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
  157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 170, 171,
  172, 173, 174, 175, 176, 177, 178, 179, 179, 180, 181, 182, 183, 184, 185, 185,
  186, 187, 188, 189, 190, 190, 191, 192, 193, 194, 194, 195, 196, 197, 198, 198,
  199, 200, 201, 201, 202, 203, 204, 204, 205, 206, 206, 207, 208, 209, 209, 210,
  211, 211, 212, 213, 213, 214, 215, 216, 216, 217, 218, 218, 219, 219, 220, 221,
  221, 222, 223, 223, 224, 225, 225, 226, 226, 227, 228, 228, 229, 229, 230, 231,
  231, 232, 232, 233, 233, 234, 235, 235, 236, 236, 237, 237, 238, 238, 239, 239,
  240, 240, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 248,
  248, 249, 249, 249, 250, 250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255
};

int attackRate = 100;
int decayRate = 100;
int sustainLevel = 1500;
int releaseRate = 10;

// shorthand for our envelope stages
const int DONE = 0;
const int ATTACK = 1;
const int DECAY = 2;
const int SUSTAIN = 3;
const int RELEASE = 4;

int gateState[] = {0,0};
int envState[] = {0,0};
word sample[] = {0,0};

int cnt = 0;


void setup(){ 
  disableInterrupts();
  Serial.begin(57600);
  setupLCDKeypad();
  setupWavetable();

  setupDAC();
  setupADC();
 
  setupInterrupt();   
  enableInterrupts();
}

void loop(){ 
  gateState[0] = 1;
  delay(400);
  gateState[0] = 0;
  delay(500);

  wavetableDelay = wavetableDelay + 20;  
  

switch (cnt){ 
     case 5: 
      changeWave(1);
        wavetableDelay = 0;
    break; 

     case 10: 
  
      changeWave(2);
            wavetableDelay = 0;
    break; 


     case 15: 
      changeWave(3);
      wavetableDelay = 0;
    break; 


     case 20: 
      changeWave(4);
      wavetableDelay = 0;
    break; 


     case 25: 
      changeWave(5);
      wavetableDelay = 0;
    break; 

  
}
  cnt++;
//  top_menu(); 
  
 }
