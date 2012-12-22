#include <Wire.h> 

#include <I2C_eeprom.h>
I2C_eeprom ee(0x50);

int sampleSize = 128;

void setup(){
Serial.begin(115200);
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
  

   // Serial.println("Triangle Up");
     // triangle
       for (iw = 0; iw <= (sampleSize / 2); iw++){    
        tmpWave[iw]=iw *16  ;

        ee.writeBlock(iw, (uint8_t *) &tmpWave[iw], 2);
      }
    Serial.println("Triangle Down");       
       for (iw = 0; iw <= (sampleSize / 2); iw++){    
        tmpWave[iw+32] = (4096 - iw * 16);
        ee.writeBlock(iw+(sampleSize / 2), (uint8_t *) &tmpWave[iw+32], 2);

      }
           

  // Square
  Serial.println("Square On");
      for (iw = 0; iw <= (sampleSize / 2); iw++){      // with  50 periods sinewawe
       tmpWave[iw]=4096;
        ee.writeBlock(iw+sampleSize, (uint8_t *) &tmpWave[iw], 2);

      }
  Serial.println("Square Off")     ; 
      for (iw = 0; iw <= (sampleSize / 2); iw++){      // with  50 periods sinewawe
       tmpWave[iw]=0;
        ee.writeBlock(iw+(sampleSize+(sampleSize / 2)), (uint8_t *) &tmpWave[iw], 2);
      }

            // ramp up
         Serial.println("Ramp Up");
      for (iw = 0; iw <= sampleSize; iw++){      // with  50 periods sinewawe
         tmpWave[iw]=iw * 32;
        ee.writeBlock(iw+(sampleSize*3), (uint8_t *) &tmpWave[iw], 2);
     }
    
      
      // ramp down
      Serial.println("Ramp down");
      for (iw = 0; iw <= sampleSize; iw++){      // with  50 periods sinewawe
       tmpWave[iw]= 255 - (iw * 32);
        ee.writeBlock(iw+(sampleSize*4), (uint8_t *) &tmpWave[iw], 2);
      }
      
      // sine
               Serial.println("Sine");
      dx=2 * pi / 4096;                    // fill the 512 byte bufferarry
      for (iw = 0; iw <= sampleSize; iw++){      // with  50 periods sinewawe
        fd= 64*sin(fcnt);                // fundamental tone
        fcnt=fcnt+dx;                     // in the range of 0 to 2xpi  and 1/512 increments
        bb=127+fd;                        // add dc offset to sinewawe 
        tmpWave[iw]=bb;                        // write value into array
        ee.writeBlock(iw+(sampleSize*5), (uint8_t *) &tmpWave[iw], 2);
   }
 
     
//   dumpEEPROM(1, sampleSize*10);     
   

Serial.println("COMPLETE");
delay(5000);
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


