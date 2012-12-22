
volatile unsigned int DACValue = 0;

void playSample( ){

if (envState[0]){
  
  samplePosition=samplePosition + sampleOffset;         // modulate the wavetable startpoint
  samplePosition = samplePosition << sampleShiftLeft;
  samplePosition = samplePosition >> sampleShiftRight;
  
  DACValue = sample[samplePosition];
  //ee.readBlock(samplePosition, (uint8_t*) &DACValue, 2);  
  
  // process the envelope
  DACValue =  (DACValue * (ADSRSample[0]  >> 1) );   // todo: add sample velocity
   
  DACValue = DACValue << bitShiftLeft; 
  DACValue = DACValue >> bitShiftRight; 
  
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
    ibb = ibb * 5;              
  }
  
 }
}


 

// select n groups of steps at evern n increment in wavetable

void changeWave(int index, int group, int steps, int randomize){ 

  int pointer = 0;
  int stepCount = 0;
  word ar;

//  Serial.print("change wave ");

 
  for ( int groupCount = 1; groupCount <= group; groupCount++){ 
    stepCount = 0;
     
    for ( int i = 0; i <  (groupCount*steps); i++){
  
      int address = index  +    (groupCount*i) + random(0, randomize);;
   
  //    Serial.println(address);
    
      ee.readBlock(address, (uint8_t*) &ar, 2);  
     
     // sample[pointer] = ar;
      pointer++;
      stepCount ++;
  }
  
}
}

