
void HandleNoteOn(byte channel, byte pitch, byte velocity) { 
  envState[0] = 0;
  // Do whatever you want when you receive a Note On.
  envState[0] = 1;   // start the wavetable
  sampleDelay = (1000 - (pitch*12)) ;
  //sampleVelocity = velocity;
  
  if (velocity == 0) {
    envState[0] = 0;
  }

}

void HandleNoteOff(byte channel, byte pitch, byte velocity) { 
  envState[0] = 0;   // stop the wavetable
}


void setupMIDI() {
//lcd.print("MIDI");
  // Initiate MIDI communications, listen to all channels
  //MIDI.begin(MIDI_CHANNEL_OMNI);    
  
  MIDI.setHandleNoteOn(HandleNoteOn);  
  MIDI.setHandleNoteOff(HandleNoteOff);
  
}

