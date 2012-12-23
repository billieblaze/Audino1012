
// shorthand for our envelope stages
const byte DONE = 0;
const byte ATTACK = 1;
const byte DECAY = 2;
const byte SUSTAIN = 3;
const byte RELEASE = 4;

boolean gateState[] = {0,0};
byte envState[] = {0,0};
word ADSRSample[] = {0,0};

byte attackRate[] = {10, 200};
byte decayRate[] = {50, 100};
byte sustainLevel[] = {2000, 255};
byte releaseRate[] = {3, 200};

void oneStep ( int x ) {
  if (ADSRSample[x] < 0) { ADSRSample[x] = 0; envState[x] = DONE; gateState[x]=0;}
  
  switch (envState[x]) {
  
    case ATTACK:
        // gate stopped, release
      if (gateState[x] == 0) {
        envState[x] = RELEASE;
        break;
      }
  
      if (ADSRSample[x] + attackRate[x] < 4096 ) {
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
//  Serial.print(envState[x]);
//  Serial.print("-");
//  Serial.println(ADSRSample[x]);
}


void envOn(int envelope){
  resetSamplePosition();
  gateState[envelope] = true;
}


void envOff(int envelope){
   gateState[envelope] = false;
}
