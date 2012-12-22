// Keypad
AnalogButtons analogButtons(0, 700, &handleButtons);
Button b_left = Button(2, 500,510);
Button b_up = Button(3, 140, 148);
Button b_down = Button(4, 325, 334);
Button b_right = Button(5, 0, 10);

// Default hold duration is 1 second, lets make it 5 seconds for button5
Button b_enter = Button(1, 738, 747);

// Menu
MenuLCD g_menuLCD(8, 9, 4, 5, 6, 7, 16,2); 
MenuManager g_menuManager( &g_menuLCD);//pass the g_menuLCD object to the g_menuManager with the & operator.

 boolean g_isDisplaying = true; 

 boolean g_updateLabels = false; 
 boolean g_updateValues = false; 

volatile char* labels[4];
volatile int values[4];
char buffer1[4];
char buffer2[4];
char buffer3[4];
char buffer4[4];
volatile int currentSetting=0;

void setupMenu(){
  char buffer[16];

  g_menuLCD.MenuLCDSetup();  

  //Add nodes via a depth-first traversal order
  MenuEntry * p_menuEntryRoot;

  //Add root node
  strcpy_P(buffer, PSTR("Audino1012"));
  
  p_menuEntryRoot = new MenuEntry(buffer, NULL, NULL);
  g_menuManager.addMenuRoot( p_menuEntryRoot );

  strcpy_P(buffer, PSTR("WT"));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, wavetableCallback ) );  

  strcpy_P(buffer, PSTR("Sample"));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, wavetableCallback ) );

  strcpy_P(buffer, PSTR("Env 1"));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );
  
  strcpy_P(buffer, PSTR("Env 2"));
  g_menuManager.addChild( new MenuEntry( buffer, NULL, envelopeCallback) );

  strcpy_P(buffer, PSTR("LFO 1"));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );

  strcpy_P(buffer, PSTR("LFO 2"));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );

  strcpy_P(buffer, PSTR("Ext In"));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, externalCallback ) );

  g_menuManager.DrawMenu();
  
  analogButtons.addButton(b_up);
  analogButtons.addButton(b_down);
  analogButtons.addButton(b_left);
  analogButtons.addButton(b_right);
  analogButtons.addButton(b_enter);    
}
      
void doConfigScreen( char* pMenuText[], int menuvalues[]){ 
  g_isDisplaying = false;
  g_updateValues = true;
  currentSetting = 0;      
        
   while ( g_isDisplaying == false ) { 
    
    checkKeys(); 

      if ( g_updateValues == true ) { 
        char* pTextLines[2];
        char line1[17]="";
        char line2[17]="";
        
        // Line 1
          for( int i = 0; i < 4; i++){
            if ( currentSetting == i){
              strncat(line1, "*",1);  
            } else { 
               strncat(line1, " ",1);  
            }         
            strncat(line1, pMenuText[i],3);  
          }
          pTextLines[0] = line1;
    
          // Line 2
          sprintf(line2," %3d %3d %3d %3d", menuvalues[0], menuvalues[1], menuvalues[2], menuvalues[3]);
          pTextLines[1] = line2;
                  
          // Send it!
          g_menuLCD.PrintMenu( pTextLines, 2, 3 );
          
      }
      
      g_updateValues = false;
      
  }  
}

void wavetableCallback( char* pMenuText, void *pUserData ){

  labels[0] = strcpy_P(buffer1,PSTR("Sta"));
  labels[1] = strcpy_P(buffer2,PSTR("End"));
  labels[2] = strcpy_P(buffer3,PSTR("Off"));
  labels[3] = strcpy_P(buffer4,PSTR("Del"));
  
//  values[0] = sampleStart;
//  values[1] = sampleEnd;
//  values[2] = sampleOffset;
//  values[3] = sampleDelay;

  doConfigScreen( (char**)labels, (int*)values);  
}

void envelopeCallback( char* pMenuText, void *pUserData ){


  labels[0] = strcpy_P(buffer1,PSTR("Att"));
  labels[1] = strcpy_P(buffer2,PSTR("Dec"));
  labels[2] = strcpy_P(buffer3,PSTR("Sus"));
  labels[3] = strcpy_P(buffer4,PSTR("Rel"));
  
  //values[0] = attackRate[0];
  //values[1] = decayRate[0];
  //values[2] = sustainLevel[0];
  //values[3] = releaseRate[0];
  doConfigScreen( (char**)labels, (int*)values);  
}

void externalCallback( char* pMenuText, void *pUserData ){

//  char *pTextLines[2] = {"External", "" };
//  g_menuLCD.PrintMenu( pTextLines, 2, 3 );
  g_isDisplaying = false;  
}

void handleButtons(int id, boolean held){ 
    if( g_isDisplaying ){
      switch (id) {
        case 3:  g_menuManager.DoMenuAction( MENU_ACTION_UP ); break;
        case 4: g_menuManager.DoMenuAction( MENU_ACTION_DOWN ); break;
        case 5: break;// menu.moveRight(); break;
        case 2: g_menuManager.DoMenuAction( MENU_ACTION_BACK ); break;
        case 1: g_menuManager.DoMenuAction( MENU_ACTION_SELECT );break;
      }
    
    }else{
      switch (id) {
        case 3: valueUp(); break;
        case 4: valueDown(); break;
        case 5: nextValue(); break;
        case 2: prevValue(); break;
        case 1: g_isDisplaying = true; g_menuManager.DrawMenu();break;
      }
   }
}

void valueUp(){
  g_updateValues = true;
}

void valueDown(){
  g_updateValues = true;
}

void nextValue(){
  if ( currentSetting != 3 ){
     currentSetting++; 
  } else { 
     currentSetting = 0;
  }  
  g_updateValues = true;
}

void prevValue(){
  if ( currentSetting != 0 ){
     currentSetting--; 
  } else { 
    currentSetting = 3;
  }
  g_updateValues = true;
}

void checkKeys() { 
   analogButtons.checkButtons();
}

char showString (PGM_P s) {
    char c;
    while ((c = pgm_read_byte(s++)) != 0)
        return c;
}
