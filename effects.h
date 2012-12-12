
  
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
