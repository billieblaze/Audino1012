// Menu texts
PROGMEM prog_char top_menu_item00[]="Oscillator";
PROGMEM prog_char top_menu_item01[]="Envelope";
PROGMEM prog_char top_menu_item02[]="Effects";
PROGMEM const char *top_menu_items[] = {top_menu_item00, top_menu_item01, top_menu_item02};

PROGMEM prog_char sub_menu_1_item00[]="Waveform";

PROGMEM prog_char sub_menu_1_item01[]="Sample Start";
PROGMEM prog_char sub_menu_1_item02[]="Sample End";
PROGMEM prog_char sub_menu_1_item03[]="Sample Offset";
PROGMEM prog_char sub_menu_1_item04[]="Sample Delay";

PROGMEM prog_char sub_menu_1_item05[]="Sample Velocity";
PROGMEM prog_char sub_menu_1_item06[]="Sample <<";
PROGMEM prog_char sub_menu_1_item07[]="Sample >>";
PROGMEM prog_char sub_menu_1_item08[]="Sample Position";

PROGMEM prog_char sub_menu_1_item09[]="Ext In Vol";
PROGMEM prog_char sub_menu_1_item10[]="Ext In Shift";
PROGMEM prog_char sub_menu_1_item11[]="Ext In Dest";
PROGMEM prog_char sub_menu_1_item12[]="Ext In Efx";

PROGMEM prog_char sub_menu_1_item13[]="Back to main menu";
PROGMEM const char *sub_menu_1_items[] = {sub_menu_1_item00, sub_menu_1_item01, sub_menu_1_item02, sub_menu_1_item03, sub_menu_1_item04, sub_menu_1_item05, sub_menu_1_item06, sub_menu_1_item07, sub_menu_1_item08, sub_menu_1_item09, sub_menu_1_item10, sub_menu_1_item11, sub_menu_1_item12, sub_menu_1_item13};

PROGMEM prog_char sub_menu_2_item00[]="Attack";
PROGMEM prog_char sub_menu_2_item01[]="Decay";
PROGMEM prog_char sub_menu_2_item02[]="Sustain";
PROGMEM prog_char sub_menu_2_item03[]="Release";
PROGMEM prog_char sub_menu_2_item04[]="DAC <<";
PROGMEM prog_char sub_menu_2_item05[]="DAC >>";
PROGMEM prog_char sub_menu_2_item06[]="Back to main menu";
PROGMEM const char *sub_menu_2_items[] = {sub_menu_2_item00, sub_menu_2_item01, sub_menu_2_item02, sub_menu_2_item03, sub_menu_2_item04, sub_menu_2_item05, sub_menu_2_item06};

// lcdkeypad
#define lcd_rows 2
#define lcd_columns 16

#define buttons_per_column 5 // Each analog pin has five buttons with resistors.
#define buttons_per_row 1 // There are two analog pins in use.

char analog_mapping[]={'U','D','L','R','B'}; // This is an analog keypad.
byte analog_pins[]={0}; // The pin numbers are analog pin numbers.
int values[]={142, 327, 504, 0, 741}; //These numbers need to increase monotonically. The 342 works better on my setup but you will need to change it back.
phi_analog_keypads analog_keypad(analog_mapping, analog_pins, values, buttons_per_row, buttons_per_column);

// The following sets up function keys for phi_prompt library
char up_keys[]={"U"}; ///< All keys that act as the up key are listed here.
char down_keys[]={"D"}; ///< All keys that act as the down key are listed here.
char left_keys[]={"L"}; ///< All keys that act as the left key are listed here.
char right_keys[]={"R"}; ///< All keys that act as the right key are listed here.
char enter_keys[]={"B"}; ///< All keys that act as the enter key are listed here.
char escape_keys[]={"A"}; ///< All keys that act as the escape key are listed here.
char * function_keys[]={up_keys,down_keys,left_keys,right_keys,enter_keys,escape_keys}; ///< All function key names are gathered here fhr phi_prompt.

// The following adds all available keypads as inputs for phi_prompt library
multiple_button_input * keypads[]={&analog_keypad, 0};

//This program is the main menu. It handles inputs from the keys, updates the menu or executes a certain menu function accordingly.
int global_style=49; // This is the style of the menu


void setupLCDKeypad(){
 // LCD
  lcd.begin(lcd_columns, lcd_rows);
  lcd.clear();
  lcd.print("Audino 1012");
  lcd.setCursor(0,1);
  lcd.print("by billieblaze");
  
  delay(500);
  lcd.clear();
//  init_phi_prompt(&lcd,keypads,function_keys, lcd_columns, lcd_rows, '~'); // Supply the liquid crystal object, input keypads, and function key names. Also supply the column and row of the lcd, and indicator as '>'. You can also use '\x7e', which is a right arrow.

}


void top_menu()
{
  int menu_pointer_1=0; // This stores the menu choice the user made.
  phi_prompt_struct myMenu; // This structure stores the main menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&top_menu_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=2; // Last item of the list is size of the list - 1.
  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  myMenu.step.c_arr[1]=1; // one col list
  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
  myMenu.step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // x for additional feature such as an index
  myMenu.col=0; // Display menu at column 0
  myMenu.row=1; // Display menu at row 1
  myMenu.option=global_style; // Option 0, display classic list, option 1, display 2X2 list, option 2, display list with index, option 3, display list with index2.
  while(1) // This loops every time a menu item is selected.
  {
   
    lcd.clear();  // Refresh menu if a button has been pushed

    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // This makes sure the change of menu style is updated if there is a menu style option in this level of menu. Auto fit the size of the list to the screen. Length in characters of the longest list item.
    myMenu.step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // This makes sure the change of menu style is updated if there is a menu style option in this level of menu. x for additional feature such as an index
    select_list(&myMenu); // Use the select_list to ask the user to select an item of the list, that is a menu item from your menu.
    menu_pointer_1=myMenu.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      sub_menu_1();
      break;
      case 1:
      sub_menu_2();
      break;
      
      case 2:
      sub_menu_3();
      break;
      
  
      default:
      break;
    }

  }
}

void sub_menu_1() // This is the sub_menu_1
{
  int menu_pointer_1=0;
  phi_prompt_struct myMenu; // This structure stores the sub menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&sub_menu_1_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=13; // Last item of the list is size of the list - 1.
  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  myMenu.step.c_arr[1]=1; // one col list
  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
  myMenu.step.c_arr[3]=lcd_columns-4; // x for additional feature such as an index
  myMenu.col=0; // Display prompt at column 0
  myMenu.row=1; // Display prompt at row 1
  myMenu.option=global_style;

  while(1)
  {
    lcd.clear();  // Refresh menu if a button has been pushed
    center_text("Oscillator");

    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.


    select_list(&myMenu);
    menu_pointer_1=myMenu.low.i;
    switch (menu_pointer_1)
    {
      
      case 0:
      sub_menu_1_function_0();
      break;
      
      case 1:
      sub_menu_1_function_1();
      break;
      case 2:
      sub_menu_1_function_2();
      break;
      
      case 3:
      sub_menu_1_function_3();
      break;

      case 4:
      sub_menu_1_function_4();
      break;
            

      case 5:
      sub_menu_1_function_5();
      break;

      case 6:
      sub_menu_1_function_6();
      break;

      case 7:
      sub_menu_1_function_7();
      break;

      case 8:
      sub_menu_1_function_8();
      break;

      
      case 13: // This option returns to previous level.
      return; // This returns to previous menu level. Only sub menus should have this unless the top level menu also returns.
      break;
  
      default:
      break;
    }
  }
}

void sub_menu_2() // This is the sub_menu_1
{
  int menu_pointer_1=0;
  phi_prompt_struct myMenu; // This structure stores the sub menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&sub_menu_2_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=5; // Last item of the list is size of the list - 1.
  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  myMenu.step.c_arr[1]=1; // one col list
  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
  myMenu.step.c_arr[3]=lcd_columns-4; // x for additional feature such as an index
  myMenu.col=0; // Display prompt at column 0
  myMenu.row=1; // Display prompt at row 1
  myMenu.option=global_style;

  while(1)
  {
    lcd.clear();  // Refresh menu if a button has been pushed
    center_text("Envelope");

    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.


    select_list(&myMenu);
    menu_pointer_1=myMenu.low.i;
    switch (menu_pointer_1)
    {
      
      case 0:
      sub_menu_2_function_0();
      break;
      
      case 1:
      sub_menu_2_function_1();
      break;
      case 2:
      sub_menu_2_function_2();
      break;
      
      case 3:
      sub_menu_2_function_3();
      break;

      case 4:
      sub_menu_2_function_4();
      break;
      
      case 5: // This option returns to previous level.
      return; // This returns to previous menu level. Only sub menus should have this unless the top level menu also returns.
      break;
  
      default:
      break;
    }
  }
}

void sub_menu_3() // This is the sub_menu_1
{
  int menu_pointer_1=0;
  phi_prompt_struct myMenu; // This structure stores the sub menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&sub_menu_2_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=5; // Last item of the list is size of the list - 1.
  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  myMenu.step.c_arr[1]=1; // one col list
  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
  myMenu.step.c_arr[3]=lcd_columns-4; // x for additional feature such as an index
  myMenu.col=0; // Display prompt at column 0
  myMenu.row=1; // Display prompt at row 1
  myMenu.option=global_style;

  while(1)
  {
    lcd.clear();  // Refresh menu if a button has been pushed
    center_text("Envelope");

    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.


    select_list(&myMenu);
    menu_pointer_1=myMenu.low.i;
    switch (menu_pointer_1)
    {
      
      case 0:
      sub_menu_2_function_0();
      break;
      
      case 1:
      sub_menu_2_function_1();
      break;
      case 2:
      sub_menu_2_function_2();
      break;
      
      case 3:
      sub_menu_2_function_3();
      break;

      case 4:
      sub_menu_2_function_4();
      break;
      
      case 5: // This option returns to previous level.
      return; // This returns to previous menu level. Only sub menus should have this unless the top level menu also returns.
      break;
  
      default:
      break;
    }
  }
}

void sub_menu_1_function_0()
{
  lcd.clear();
  lcd.print("Waveform");
  lcd.setCursor(0,1);


  showMenu = 0;
}


void sub_menu_1_function_1()
{
  lcd.clear();
  lcd.print("Sample Start");
    phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleStart; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=sampleSize; // Upper limit. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
  
  showMenu = 0;
}

void sub_menu_1_function_2()
{
  lcd.clear();
  lcd.print("Sample End");
  lcd.setCursor(0,1);

    phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleEnd; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=sampleSize; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
}

void sub_menu_1_function_3()
{
  lcd.clear();
  lcd.print("Sample Offset");
  lcd.setCursor(0,1);
  phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleOffset; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=64; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
  showMenu = 0;
}

void sub_menu_1_function_4()
{
  lcd.clear();
  lcd.print("Sample Delay");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleDelay; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=500; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
}


void sub_menu_1_function_5()
{
  lcd.clear();
  lcd.print("Sample Velocity");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleVelocity; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=500; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
}


void sub_menu_1_function_6()
{
  lcd.clear();
  lcd.print("Sample <<");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleShiftLeft; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=8; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
}

void sub_menu_1_function_7()
{
  lcd.clear();
  lcd.print("Sample >>");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&sampleShiftRight; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=8; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
}


void sub_menu_1_function_8()
{
  lcd.clear();
  lcd.print("Sample Position");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions
  myIntegerInput.ptr.i_buffer=&samplePosition; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”.
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0.
myIntegerInput.high.i=sampleSize; // Upper limit. The number wraps to 0 when increased from 20.
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2.
myIntegerInput.col=0; // Display the number at column 7
myIntegerInput.row=1; // Display the number at row 1
myIntegerInput.width=2; // The number occupies 2 character space.
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left.

  input_integer(&myIntegerInput);
}


void sub_menu_2_function_0()
{
  lcd.clear();
  lcd.print("Trigger");
  lcd.setCursor(0,1);

}

void sub_menu_2_function_1()
{
  lcd.clear();
  lcd.print("Attack");
  lcd.setCursor(0,1);
}

void sub_menu_2_function_2()
{
  lcd.clear();
  lcd.print("Decay");
  lcd.setCursor(0,1);


}

void sub_menu_2_function_3()
{
  lcd.clear();
  lcd.print("Sustain");
  lcd.setCursor(0,1);

}

void sub_menu_2_function_4()
{
  lcd.clear();
  lcd.print("Release");
  lcd.setCursor(0,1);


}
