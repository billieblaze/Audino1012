I2C_eeprom ee(0x50);
  
//wavetable

volatile byte ibb;
volatile byte samplePosition = 0;

int sampleVelocity = 127;

volatile long DACValue = 0;

void playSample( ){

if (gateState[0] || droneMode == true){
  //Serial.println("Runnit!");
 
  samplePosition=samplePosition + sampleOffset;         // modulate the wavetable startpoint
  // implement "interpolation" and randomization 
  
//  DACValue = sample[samplePosition];

       DACValue =  eeprom_read_word((uint16_t*)samplePosition) >> 4;
 // Serial.print(DACValue);
 // Serial.print(" -- ");
 //Serial.println(ADSRSample[0]);
 //Serial.println("  ");
 //Serial.print(" -- ");
 // process the envelope
    if (droneMode == false){
      DACValue =  (DACValue * ADSRSample[0] ) ;   // todo: add sample velocity
    }
  DACValue = DACValue << bitShiftLeft; 
  DACValue = DACValue >> bitShiftRight; 
 //Serial.println(DACValue);     
  SPISend(DACValue );

  // increment pointers
  samplePosition++;                 // increment index

  if (samplePosition == sampleEnd){ 
    samplePosition = sampleStart;
  }

 //  variable delay controlled by potentiometer    
  // when distortion then delay / processing time is too long     
  
  // envelope 1 -> pitch
 // sampleDelay = sampleDelay - (4000 - envelopeValue[0])/2;  
  
  for (int cnta=0; cnta <= sampleDelay; cnta++) { 
    ibb = ibb * 1;              
  }
  
 }
}

void resetSamplePosition(){
  samplePosition = 0;
}
void setPitch (int pitch) {
   sampleDelay =  1000 - (10 * pitch);
}

void setVelocity (int velocity){ 
   sampleVelocity = velocity; 
}
