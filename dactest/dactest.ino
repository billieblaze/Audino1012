/*
Uses Sainsmart LCD Shield for Arduino
*/


#include <LiquidCrystal.h>
#include <DFR_Key.h>

//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

DFR_Key keypad;
int localKey = 0;
String keyString = "";

// set pin 10 as the slave select for the digital pot:f
#define SLAVESELECT 3
#include <SPI.h>


// setup interrupt based operation
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

boolean div32;
boolean div16;
// vars altered by interrupt
volatile boolean f_sample;

volatile word badc0;
volatile word badc1;
volatile byte badc2;
volatile byte ibb;

int ii;


int cnta;
int icnt;
int cnt2;

int icnt1;
int icnt2;

float pi = 3.141592;
float dx ;
float fd ;
float fcnt;
int iw;
word iw1;
word iw2;

int i2;

word bb;

byte potVal = 20 ;
 
word dd[512];  // Audio Memory Array 8-Bit
int offset = 510;
word sensorValue;
  
void setup() 
{ 
  
  // LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DAC Test");
  delay(2500);

  // keypad
  keypad.setRate(120);

  // initialize SPI:22
  pinMode(SLAVESELECT, OUTPUT);

  digitalWrite(SLAVESELECT, HIGH);

  SPI.setBitOrder(MSBFIRST);
  SPI.begin(); 

  // ISR Based Audio
    Serial.begin(9600);        // connect to the serial port
  Serial.println("Arduino Audio Loopback");
   fill_sinewave(); 
  
  // set adc prescaler  to 64 for 19kHz sampling frequency
  cbi(ADCSRA, ADPS2);
  sbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);


  sbi(ADMUX,REFS0);  // VCC Reference
  cbi(ADMUX,REFS1);
  cbi(ADMUX,MUX0);   // Set Input Multiplexer to Channel 0
  cbi(ADMUX,MUX1);
  cbi(ADMUX,MUX2);
  cbi(ADMUX,MUX3);

  // Timer2 Clock Prescaler to : 1 
  sbi (TCCR2B, CS20);
  cbi (TCCR2B, CS21);
  cbi (TCCR2B, CS22);

  //cli();                         // disable interrupts to avoid distortion
  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay is off now
  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt
  
  Serial.print("ADC offset=");     // trim to 127
  ii=badc1;  
  Serial.println(ii);
  delay(500);
}

void loop() 
{ 
  
  //while (!f_sample) {         // wait for Sample Value from ADC 
  //}                           // Cycle 15625 KHz = 64uSec 
  //f_sample=false;


// Keypad
   localKey = keypad.getKey();
    
    if (localKey != SAMPLE_WAIT)
    {
      switch(localKey){
        case 3:
          if(potVal < 255){
            potVal++;
          }
        break;
        
        case 4:
        if (potVal > 0 ) {
          potVal--;
        }
        break;
        
      }    
//      lcd.setCursor(0,1);
//      lcd.print(potVal);
      
    }
    

  // "audio thru"
//sensorValue = badc1 ;
  
// play wavetable
  sensorValue = dd[icnt];         // get the buffervalue on indexposition

// Decay   
  badc1=dd[icnt];            // get the buffervalue on indexposition
  
  iw = (badc1 * 2) - offset;
  i2 = (15625-cnt2)/64;
  
  iw *= i2;              // decay of wave
  iw /= 256;
    
  badc1 = iw + offset;
  
  icnt=icnt + potVal/2;         // Variable frequency with potentiometer
  icnt *= i2; 
  
  sensorValue = badc1;
 
  if (cnt2 >= 15625){
  
    cnt2=0;
    icnt=0;
    //fill_sinewave();          // reload wave after 1 second

  } 
  cnt2++;
  
// reverb
  //bb=dd[icnt] ;              // read the delay buffer
   //iw = offset - bb ;              // substract offset
  //iw = iw * potVal / 255;     // scale delayed sample with potentiometer

  //iw1 = offset - sensorValue;          // substract offset from new sample
  //iw1=iw1+iw;                 // add delayed sample and new sample
  //if (iw1 < -127) iw1=-127;   // Audio limiter 
  //if (iw1 > 127) iw1=127;     // Audio limiter 

  //bb= offset+iw1;                // add offset
  //dd[icnt]=bb;                // store sample in audio buffer
//sensorValue = bb;


// phasor

/*
  bb=badc1;
  dd[icnt1]=bb;          // write to buffer
  iw1=dd[icnt2] ;              // read the delay buffer

  icnt1++;

  icnt2= icnt1 - potVal /3;

  icnt2 = icnt2 & 511;         // limit index 0..  
  icnt1 = icnt1 & 511;         // limit index 0..511  

  sensorValue = (iw1+bb)/2;
*/

  icnt++;                 // increment index
  icnt = icnt & 511;      // limit index 0..511


  // send high byteu
  byte data = highByte(sensorValue);
  data = B00111111 & data; // clear 4-bit command field (optional)
  data = B10000000 | data; // 0=DACA, 0=buffered, 1=1x, 1=output enabled

 digitalWrite(SLAVESELECT, LOW); // select the chip
 SPI.transfer(data);

  // send low byte
  data = lowByte(sensorValue);
  SPI.transfer(data);
  
  digitalWrite(SLAVESELECT, HIGH);

 //  variable delay controlled by potentiometer    
  // when distortion then delay / processing time is too long   
  badc2=0 ;
  for (cnta=0; cnta <= badc2; cnta++) { 
    ibb = ibb * 5;              
  }

 
}


//******************************************************************
// Timer2 Interrupt Service at 62.5 KHz
// here the audio and pot signal is sampled in a rate of:  16Mhz / 256 / 2 / 2 = 15625 Hz
// runtime : xxxx microseconds
ISR(TIMER2_OVF_vect) {

  div32=!div32;                      // divide timer2 frequency / 2 to 31.25kHz
  if (div32){ 
    div16=!div16;  // 
            

    if (div16) {                     // sample channel 1 and 2 alternately so each channel is sampled with 15.6kHz
      //badc1=ADCH;                    // get ADC channel 1
     //sbi(ADMUX,MUX1);               // set multiplexer to channel 1
      badc1 = analogRead(A1);    
     
    }
    else
    {

      f_sample=true;
    }
    ibb++;                          // short delay before start conversion
    ibb--; 
    ibb++; 
    ibb--;    
//   sbi(ADCSRA,ADSC);               // start next conversion
  }

}
void fill_sinewave(){
  // sine
  /*
  dx=2 * pi / 512;                    // fill the 512 byte bufferarry
  for (iw = 0; iw <= 511; iw++){      // with  50 periods sinewawe
    fd= 127*sin(fcnt);                // fundamental tone
    fcnt=fcnt+dx;                     // in the range of 0 to 2xpi  and 1/512 increments
    bb=127+fd;                        // add dc offset to sinewawe 
    dd[iw]=bb;                        // write value into array
 }
  */
  // ramp up
   /*
   for (iw = 0; iw <= 511; iw++){      // with  50 periods sinewawe
     dd[iw]=iw/2;
   }
*/
  
  // ramp down
  //dx=2 * pi / 512;                    // fill the 512 byte bufferarry
  //for (iw = 0; iw <= 511; iw++){      // with  50 periods sinewawe
   // dd[iw]=1024-iw;
  //}
  
   // triangle

   for (iw = 0; iw <= 256; iw++){      // with  50 periods sinewawe
    dd[iw]=iw ;
  }
   for (iw = 0; iw <= 256; iw++){      // with  50 periods sinewawe
    dd[iw+256]= 1024 - iw;
  }

  // Square
//  for (iw = 0; iw <= 256; iw++){      // with  50 periods sinewawe
 //  dd[iw]=2048;
 // }

    // Noise


}



