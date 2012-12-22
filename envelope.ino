void oneStep ( int x ) {
  if (ADSRSample[x] < 0) { ADSRSample[x] = 0; envState[x] = DONE; gateState[x]=0;}
  
  switch (envState[x]) {
  
    case ATTACK:
        // gate stopped, release
      if (gateState[x] == 0) {
        envState[x] = RELEASE;
        break;
      }
  
      if (ADSRSample[x] + attackRate[x] < 255 ) {
        ADSRSample[x] += attackRate[x];
      } else {
        envState[x] = DECAY;
      }
      break;
  
    case DECAY:
      // gate stopped, release
      if (gateState[x] == 0) {
        envState[x] = RELEASE;
        break;
      }
      if (ADSRSample[x] - decayRate[x] > sustainLevel[x]) {
        ADSRSample[x] -= decayRate[x];      
      } else {
        envState[x] = SUSTAIN;
      }
      break;
    case SUSTAIN:
        // gate stopped, release
      if (gateState[x] == 0) {
         envState[x] = RELEASE;
        break;
      }
      ADSRSample[x] = sustainLevel[x];
      break;
  
    case RELEASE:
      if (gateState[x] == 1) {
        envState[x] = ATTACK;
        break;
      } 
      if (ADSRSample[x] - releaseRate[x] > 0) {
        ADSRSample[x] -= releaseRate[x];       
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
}



