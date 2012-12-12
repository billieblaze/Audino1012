volatile byte ibb;
boolean div32;
boolean div16;

volatile boolean f_sample;

void setupInterrupt(){
  // Timer2 Clock Prescaler to : 1 
  sbi (TCCR2B, CS20);
  cbi (TCCR2B, CS21);
  cbi (TCCR2B, CS22);

  //cli();                         // disable interrupts to avoid distortion
//  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay is off now
//  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt
}

//******************************************************************
// Timer2 Interrupt Service at 62.5 KHz
// here the audio and pot signal is sampled in a rate of:  16Mhz / 256 / 2 / 2 = 15625 Hz
// runtime : xxxx microseconds
/*
ISR(TIMER2_OVF_vect) {

  div32=!div32;                      // divide timer2 frequency / 2 to 31.25kHz
  if (div32){ 
    div16=!div16;  // 
    if (div16) {                     // sample channel 1 and 2 alternately so each channel is sampled with 15.6kHz
      //badc1=ADCH;                    // get ADC channel 1
     //sbi(ADMUX,MUX1);               // set multiplexer to channel 1
  //    ADCValue = analogRead(A1);    
     
    }else{
       f_sample=true;
    }
 //   ibb++;                          // short delay before start conversion
 //   ibb--; 
 //   ibb++; 
 //   ibb--;    
//   sbi(ADCSRA,ADSC);               // start next conversion
  }

}

*/
