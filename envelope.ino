
// shorthand for our envelope stages
const byte DONE = 0;
const byte ATTACK = 1;
const byte DECAY = 2;
const byte SUSTAIN = 3;
const byte RELEASE = 4;

boolean gateState[] = {0,0};
byte envState[] = {0,0};
word ADSRSample[] = {0,0};

int attackRate[] = {100, 200};
int decayRate[] = {50, 100};
int sustainLevel[] = {255, 255};
int releaseRate[] = {3, 200};

boolean droneMode = false;

void envelopeStep ( ) {
  for ( int x = 0; x < 2; x++ ){
    if (ADSRSample[x] < 0) { ADSRSample[x] = 0; envState[x] = DONE; gateState[x]=0;}
    int tmp_decay;
        
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
        
        tmp_decay  = decayRate[x] * 16;
        if (ADSRSample[x] - tmp_decay > sustainLevel[x]) {
          ADSRSample[x] -= tmp_decay;      
        } else {
          envState[x] = SUSTAIN;
        }
        break;
      case SUSTAIN:
//        Serial.println("sus");
          // gate stopped, release
        if (gateState[x] == 0) {
           envState[x] = RELEASE;
          break;
        }
        ADSRSample[x] = sustainLevel[x];
        break;
    
      case RELEASE:
        if (gateState[x] == 1) {
          ADSRSample[x] = 0;
          envState[x] = ATTACK;
          break;
        } 
        if (ADSRSample[x] - releaseRate[x] > 0 ) {
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
  
}


void envOn(int envelope){
  resetSamplePosition();
  gateState[envelope] = true;
}

void envOff(int envelope){
   gateState[envelope] = false;
}
