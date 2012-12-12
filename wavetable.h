int wavetablePosition = 0;
byte wavetable[64];  // Audio Memory Array 
boolean reinitializeWavetable = 1;

word playWavetable(int wtposition){
  word originalValue = wavetable[wtposition];         
  word newValue = originalValue;
  
// Decay   
  /*
  iw = (originalValue * 2) - offset;
  i2 = (15625-cnt2)/64;
  
  iw *= i2;              // decay of wave
  iw /= 256;
    
  DACValue = iw + offset;
  */
  
  
  return newValue;
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
        tmpWave[iw+32] = (255 - iw * 4);
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
   
  changeWave(0);       
   Serial.println("Wavetable Created");
  }

}  


