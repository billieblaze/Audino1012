prog_char string_0[] PROGMEM = "Audino1012";   // "String 0" etc are strings to store - change to suit.
prog_char string_1[] PROGMEM = "WT";
prog_char string_2[] PROGMEM = "Sample";
prog_char string_3[] PROGMEM = "Env 1";
prog_char string_4[] PROGMEM = "Env 2";
prog_char string_5[] PROGMEM = "LFO 1";
prog_char string_6[] PROGMEM = "LFO 2";   // "String 0" etc are strings to store - change to suit.
prog_char string_7[] PROGMEM = "Ext In";
prog_char string_8[] PROGMEM = "Sta";
prog_char string_9[] PROGMEM = "End";
prog_char string_10[] PROGMEM = "Off";
prog_char string_11[] PROGMEM = "Del";
prog_char string_12[] PROGMEM = "Att";
prog_char string_13[] PROGMEM = "Dec";
prog_char string_14[] PROGMEM = "Sus";
prog_char string_15[] PROGMEM = "Rel";


// Then set up a table to refer to your strings.

PROGMEM const char *string_table[] = 	   // change "string_table" name to suit
{   
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5,
  string_6,
  string_7,
  string_8,
  string_9,
  string_10,
  string_11
 };

char buffer[16];

char* labels[4];

int values[4];
volatile int currentSetting=0;

void setupMenu(){
  g_menuLCD.MenuLCDSetup();  

  //Add nodes via a depth-first traversal order
  MenuEntry * p_menuEntryRoot;

  //Add root node
  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0])));
  
  p_menuEntryRoot = new MenuEntry(buffer, NULL, NULL);
  g_menuManager.addMenuRoot( p_menuEntryRoot );

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[1])));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, wavetableCallback ) );  

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[2])));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, wavetableCallback ) );

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[3])));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );
  
  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[4])));
  g_menuManager.addChild( new MenuEntry( buffer, NULL, envelopeCallback) );

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[5])));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[6])));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[7])));
  g_menuManager.addChild( new MenuEntry(buffer, NULL, envelopeCallback ) );

  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[8])));
  g_menuManager.addChild( new MenuEntry( buffer, NULL, externalCallback) );

  g_menuManager.DrawMenu();
  
  analogButtons.addButton(b_up);
  analogButtons.addButton(b_down);
  analogButtons.addButton(b_left);
  analogButtons.addButton(b_right);
  analogButtons.addButton(b_enter);    
}
      
void doConfigScreen( char* pMenuText[], int menuvalues[]){ 
  g_isDisplaying = false;
  g_updateLabels = true;
  g_updateValues = true;

   while ( g_isDisplaying == false ) { 
    
    analogButtons.checkButtons(); 

      if ( g_updateValues == true ) { 
        
        char* pTextLines[2];
        
        // Line 1
          for( int i = 0; i < 4; i++){
            if ( currentSetting == i){
              strncat(pTextLines[0], "*",1);  
            } else { 
               strncat(pTextLines[0], " ",1);  
            }         
            strncat(pTextLines[0], pMenuText[i],3);  
          }


          // Line 2
          sprintf(buffer," %3d %3d %3d %3d", menuvalues[0], menuvalues[1], menuvalues[2], menuvalues[3]);
          pTextLines[1] = buffer;
          // Send it!
          g_menuLCD.PrintMenu( pTextLines, 2, 3 );
          
      }
      
      g_updateValues = false;
      
  }  
}

  
void wavetableCallback( char* pMenuText, void *pUserData ){

char buffer1[3];
char buffer2[3];
char buffer3[3];
char buffer4[3];

  labels[0] = strcpy_P(buffer1, (char*)pgm_read_word(&(string_table[8])));;
  labels[1] = strcpy_P(buffer2, (char*)pgm_read_word(&(string_table[9])));;
  labels[2] = strcpy_P(buffer3, (char*)pgm_read_word(&(string_table[10])));;
  labels[3] = strcpy_P(buffer4, (char*)pgm_read_word(&(string_table[11])));;
  
  values[0] = sampleStart;
  values[1] = sampleEnd;
  values[2] = sampleOffset;
  values[3] = sampleDelay;

  doConfigScreen( labels, values);  
}

void envelopeCallback( char* pMenuText, void *pUserData ){

  labels[0] = strcpy_P(buffer, (char*)pgm_read_word(&(string_table[12])));;
  labels[1] = strcpy_P(buffer, (char*)pgm_read_word(&(string_table[13])));;
  labels[2] = strcpy_P(buffer, (char*)pgm_read_word(&(string_table[14])));;
  labels[3] = strcpy_P(buffer, (char*)pgm_read_word(&(string_table[15])));;
  
  values[0] = attackRate[0];
  values[1] = decayRate[0];
  values[2] = sustainLevel[0];
  values[3] = releaseRate[0];
  doConfigScreen( labels, values);  
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


