void disableInterrupts(){
  /* First disable the timer overflow interrupt while we're configuring */
  TIMSK2 &= ~(1<<TOIE2);  
 
}

void enableInterrupts(){
  /* Finally load end enable the timer */
  TCNT2 = tcnt2;  
  TIMSK2 |= (1<<TOIE2);    
}

void setupInterrupt(){
  Serial.print("Interrupt Setup started...");

  /* Configure timer2 in normal mode (pure counting, no PWM etc.) */
  //  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));  
  // TCCR2B &= ~(1<<WGM22);  
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

  /* Select clock source: internal I/O clock */
  ASSR &= ~(1<<AS2);  

  /* Disable Compare Match A interrupt enable (only want overflow) */
  TIMSK2 &= ~(1<<OCIE2A);  

  /* Now configure the prescaler to CPU clock divided by 128 */
  TCCR2B |= (1<<CS20) ; // Set bits  
  TCCR2B &= ~(1<<CS21) | (1<<CS22);             // Clear bit  

  Serial.println("complete");
}

//******************************************************************
// Timer2 Interrupt Service at 62.5 KHz
// here the audio and pot signal is sampled in a rate of:  16Mhz / 256 / 2 / 2 = 15625 Hz
// runtime : xxxx microseconds



ISR( TIMER2_OVF_vect ){

  div32=!div32;                      // divide timer2 frequency / 2 to 31.25kHz
  if (div32){ 
    playSample( );


    div16=!div16;  
    if (div16) { 


      // sample channel 1 and 2 alternately so each channel is sampled with 15.6kHz
      //badc1=ADCH;                    // get ADC channel 1
      //sbi(ADMUX,MUX1);               // set multiplexer to channel 1
      //    ADCValue = analogRead(A1);    

      //    f_sample=true;
    }
    else{

      f_sample=true;
    }
    ibb++;  

    div8=!div8;  
    if (div8) { 


      div4=!div4;  
      if (div4) { 
        div2=!div2;  
        if (div2) { 

          oneStep(0);

        }
      }
    }  
    // sbi(ADCSRA,ADSC);               // start next conversion
  }
}


