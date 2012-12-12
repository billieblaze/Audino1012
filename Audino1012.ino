#include <LiquidCrystal.h>
#include <DFR_Key.h>
#include <SPI.h>
#include <Wire.h> 
#include <MenuBackend.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

#include <I2C_eeprom.h>

I2C_eeprom ee(0x50);

#include "adc.h"
#include "dac.h"
#include "interrupt.h"
#include "wavetable.h"
#include "effects.h"
#include "menu.h"
#include "lcdkeypad.h"

int offset = 510;

void setup() 
{ 
  Serial.begin(57600);

  setupInterrupt();

  
  setupLCDKeypad();
  setupDAC();
  setupADC();

  setupWavetable();
  menuSetup();
  lcd.print("READY");	
  delay(500);
}

void loop() 
{ 

  
  //while (!f_sample) {         // wait for Sample Value from ADC 
  //}                           // Cycle 15625 KHz = 64uSec 
  //f_sample=false;

  //wavetablePosition=wavetablePosition + potVal/2;         // Variable frequency with potentiometer
  //  wavetablePosition *= i2; 
  
  DACValue = playWavetable(wavetablePosition) << 4;  
  SPISend(DACValue);

  // increment pointers
  wavetablePosition++;                 // increment index
  if (wavetablePosition == 64){ 
    wavetablePosition = 0;
  }

 //  variable delay controlled by potentiometer    
  // when distortion then delay / processing time is too long     
//  int badc2=1 ;
//  for (int cnta=0; cnta <= badc2; cnta++) { 
//    ibb = ibb * 5;              
//  }

    handleKeypad(); 
}


void dumpEEPROM(unsigned int addr, unsigned int length)
{
  // block to 10
  addr = addr / 10 * 10;
  length = (length + 9)/10 * 10;

  byte b = ee.readByte(addr);
  for (int i = 0; i < length; i++)
  {
    if (addr % 10 == 0)
    {
      Serial.println();
      Serial.print(addr);
      Serial.print(":\t");
    }
    Serial.print(b);
    b = ee.readByte(++addr);
    Serial.print("  ");
  }
  Serial.println();
}


void changeWave(int index){ 
  for ( int i = 1; i < 128; i++){
    wavetable[i] = ee.readByte(index * 128 + i);   
  }
}
