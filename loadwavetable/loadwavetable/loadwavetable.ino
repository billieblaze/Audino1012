#include <avr/eeprom.h>

int sampleSize = 128;

void setup(){
  Serial.begin(9600);
  Serial.println("Initializing Waveform");
}

void loop(){ 

      float pi = 3.141592;
      float dx ;
      float fd ;
      float fcnt;
      int iw;
      word iw1;
      word iw2;
      
      int i2;
      
      word bb;
    
     word tmpWave[sampleSize];
  
  word temp[sampleSize];

   // Serial.println("Triangle Up");
     // triangle
       for (iw = 0; iw <= (sampleSize / 2); iw++){    
        eeprom_write_word((uint16_t *)iw, (iw *16))  ;
      
//        ee.writeBlock(iw, (uint8_t *) &tmpWave[iw], 2);
      }


 

    Serial.println("Triangle Down");       
       for (iw = 0; iw <= (sampleSize / 2); iw++){    
        eeprom_write_word((uint16_t *)(iw+(sampleSize / 2)), (4096 - iw *16))  ;
      }
           

  // Square
  Serial.println("Square On");
      for (iw = 0; iw <= (sampleSize / 2); iw++){      // with  50 periods sinewawe
        eeprom_write_word( (uint16_t *)(iw+sampleSize) , 4096)  ;
      }
  Serial.println("Square Off")     ; 
      for (iw = 0; iw <= (sampleSize / 2); iw++){      // with  50 periods sinewawe
        eeprom_write_word( (uint16_t *)(iw+(sampleSize+(sampleSize/2))) , 0)  ;
      }

   // ramp up
      Serial.println("Ramp Up");
      for (iw = 0; iw <= sampleSize; iw++){      // with  50 periods sinewawe
        eeprom_write_word( (uint16_t *)(iw+(sampleSize*3)) , iw*32)  ;     
     }
    
      
      // ramp down
      Serial.println("Ramp down");
      for (iw = 0; iw <= sampleSize; iw++){      // with  50 periods sinewawe
        eeprom_write_word( (uint16_t *)(iw+(sampleSize*4)) , 4096-(iw*32))  ;
      }
      
      // sine
      Serial.println("Sine");
      dx=2 * pi / 4096;                    // fill the 512 byte bufferarry
      for (iw = 0; iw <= sampleSize; iw++){      // with  50 periods sinewawe
        fd= 64*sin(fcnt);                // fundamental tone
        fcnt=fcnt+dx;                     // in the range of 0 to 2xpi  and 1/512 increments
        bb=127+fd;                        // add dc offset to sinewawe 

        eeprom_write_word( (uint16_t *)(iw+(sampleSize*5)) , bb)  ;

   }
 

dumpEEPROM(1, sampleSize*10);     
   

Serial.println("COMPLETE");
delay(50000);
 }
 
 
 
void dumpEEPROM(unsigned int addr, unsigned int length){
  
  
  // block to 10
  addr = addr / 10 * 10;
  length = (length + 9)/10 * 10;

  word b = eeprom_read_word((uint16_t*)addr);
  for (int i = 0; i < length; i++)
  {
    if (addr % 10 == 0)
    {
      Serial.println();
      Serial.print(addr);
      Serial.print(":\t");
    }

    b =  eeprom_read_word((uint16_t*)i);
    Serial.print("  ");
  }
  Serial.println();
}


