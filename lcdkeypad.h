

DFR_Key keypad;
int localKey = 0;
String keyString = "";


void setupLCDKeypad(){
 // LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DAC Test");

  // keypad
  keypad.setRate(300);
 
}

void handleKeypad(){
  // Keypad
   localKey = keypad.getKey();
    
    if (localKey != SAMPLE_WAIT)
    {
      switch(localKey){
        case 1:
          menu.use();
        break;
        case 2:
         
          menu.moveLeft();
        break;
        case 3:
           menu.moveUp();
        break;
        
        case 4:
           menu.moveDown();
        break;
        case 5:
          menu.moveRight();
        break;
      }    
  }
  

}
