
volatile word DACValue = 0;


void playWavetable( ){

  wavetablePosition=wavetablePosition + wavetableOffset;         // modulate the wavetable startpoint
  
  DACValue = wavetable[wavetablePosition]; // << 4; 

  // process the envelope
   DACValue = (DACValue * (envelopeValue >> 6)) << 2 ;  

  SPISend(DACValue);

  // increment pointers
  wavetablePosition++;                 // increment index

  if (wavetablePosition == wavetableEnd){ 
    wavetablePosition = wavetableStart;
  }

 //  variable delay controlled by potentiometer    
  // when distortion then delay / processing time is too long     

  for (int cnta=0; cnta <= wavetableDelay; cnta++) { 
    ibb = ibb * 5;              
  }
}


 void setupWavetable(){ 
  if (reinitializeWavetable ){
    Serial.println("Initializing Waveform");
      float pi = 3.141592;
      float dx ;
      float fd ;
      float fcnt;
      int iw;
      word iw1;
      word iw2;
      
      int i2;
      
      word bb;
    
     byte tmpWave[64];
  
  
     // triangle
       for (iw = 0; iw <= 32; iw++){    
        tmpWave[iw]=iw * 8  ;
        ee.writeBlock(iw, (uint8_t *) &tmpWave[iw], 1);
      }
       
       for (iw = 0; iw <= 32; iw++){    
        tmpWave[iw+32] = (255 - iw * 8);
        ee.writeBlock(iw+32, (uint8_t *) &tmpWave[iw+32], 1);

      }
      
//      dumpEEPROM(1, 64);
      

  // Square
      for (iw = 0; iw <= 32; iw++){      // with  50 periods sinewawe
       tmpWave[iw]=255;
        ee.writeBlock(iw+128, (uint8_t *) &tmpWave[iw], 1);

      }
      
      for (iw = 0; iw <= 32; iw++){      // with  50 periods sinewawe
       tmpWave[iw]=0;
        ee.writeBlock(iw+192, (uint8_t *) &tmpWave[iw], 1);
      }

            // ramp up
       
      for (iw = 0; iw <= 64; iw++){      // with  50 periods sinewawe
         tmpWave[iw]=iw * 4;
        ee.writeBlock(iw+256, (uint8_t *) &tmpWave[iw], 1);
     }
    
      
      // ramp down
      for (iw = 0; iw <= 64; iw++){      // with  50 periods sinewawe
       tmpWave[iw]= 255 - (iw * 4);
        ee.writeBlock(iw+320, (uint8_t *) &tmpWave[iw], 1);
      }
      
      // sine
      
      dx=2 * pi / 255;                    // fill the 512 byte bufferarry
      for (iw = 0; iw <= 64; iw++){      // with  50 periods sinewawe
        fd= 64*sin(fcnt);                // fundamental tone
        fcnt=fcnt+dx;                     // in the range of 0 to 2xpi  and 1/512 increments
        bb=127+fd;                        // add dc offset to sinewawe 
        tmpWave[iw]=bb;                        // write value into array
        ee.writeBlock(iw+384, (uint8_t *) &tmpWave[iw], 1);
    
   }
     Serial.println("Wavetable Created");
    changeWave(0);       
 
  }

}  


void changeWave(int index){ 
  Serial.print("changed wavetable");
  Serial.println(index);
  for ( int i = 1; i < 64; i++){
    wavetable[i] = ee.readByte(index * 64 + i);   
  }
  
  //dumpEEPROM(0,64);
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


