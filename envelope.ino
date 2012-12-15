
void oneStep ( int x ) {
  
  if (sample[x] < 0) { sample[x] = 0; envState[x] = DONE; gateState[x]=0;}
  
  switch (envState[x]) {
  
  case ATTACK:
      //      Serial.println("attack");

    // gate stopped, release
    if (gateState[x] == 0) {
      envState[x] = RELEASE;
      break;
    }

    if (sample[x] + attackRate < 4000 ) {
      sample[x] += attackRate;
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
    if (sample[x] - decayRate > sustainLevel) {
      sample[x] -= decayRate;      
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
    sample[x] = sustainLevel;
    break;

  case RELEASE:
//   Serial.println("release");
    if (gateState[x] == 1) {
      envState[x] = ATTACK;
      break;
    } 
    if (sample[x] - releaseRate > 0) {
      sample[x] -= releaseRate;      
      
    } else {
      sample[x] = 0;   
      envState[x] = DONE;
    }
    break;
    
  case DONE:
    sample[x] = 0;   
    if (gateState[x] == 1) {
      envState[x] = ATTACK;
      break;
    }

    break;
    }
      writeDAC (sample[x], x);
}

int envelopeValue;
void writeDAC( int sample, int dac) { 
// Serial.println(sample);
  envelopeValue = sample;
}
