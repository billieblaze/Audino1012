
void oneStep ( int x ) {
  
  if (ADSRSample[x] < 0) { ADSRSample[x] = 0; envState[x] = DONE; gateState[x]=0;}
  
  switch (envState[x]) {
  
  case ATTACK:
      //      Serial.println("attack");

    // gate stopped, release
    if (gateState[x] == 0) {
      envState[x] = RELEASE;
      break;
    }

    if (ADSRSample[x] + attackRate < 4000 ) {
      ADSRSample[x] += attackRate;
    } else {
      envState[x] = DECAY;
    //  Serial.println("decay");

    }
    break;

  case DECAY:
    // gate stopped, release
    if (gateState[x] == 0) {
      envState[x] = RELEASE;
      break;
    }
    if (ADSRSample[x] - decayRate > sustainLevel) {
      ADSRSample[x] -= decayRate;      
    } else {
      envState[x] = SUSTAIN;
  //    Serial.println("sustain");

    }
    break;
  case SUSTAIN:
      // gate stopped, release
    if (gateState[x] == 0) {
       envState[x] = RELEASE;

      break;
    }
    ADSRSample[x] = sustainLevel;
    break;

  case RELEASE:
//   Serial.println("release");
    if (gateState[x] == 1) {
      envState[x] = ATTACK;
      break;
    } 
    if (ADSRSample[x] - releaseRate > 0) {
      ADSRSample[x] -= releaseRate;      
      
    } else {
      ADSRSample[x] = 0;   
      envState[x] = DONE;
    }
    break;
    
  case DONE:
    ADSRSample[x] = 0;   
    if (gateState[x] == 1) {
      envState[x] = ATTACK;
      break;
    }

    break;
    }
      writeDAC (ADSRSample[x], x);
}

int envelopeValue;
void writeDAC( int sample, int dac) { 
// Serial.println(sample);
  envelopeValue = sample;
}
