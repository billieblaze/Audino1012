
void HandleNoteOn(byte channel, byte pitch, byte velocity) { 
  envOn(0);
  setPitch(pitch);
  setVelocity(velocity);
  
  if (velocity == 0) {
    envOff(0);
  }

}

void HandleNoteOff(byte channel, byte pitch, byte velocity) { 
    envOff(0);   // stop the wavetable
}


void setupMIDI() {
  MIDI.begin(MIDI_CHANNEL_OMNI);    
  MIDI.setHandleNoteOn(HandleNoteOn);  
  MIDI.setHandleNoteOff(HandleNoteOff);
}

