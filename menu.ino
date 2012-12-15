

void setupLCDKeypad(){
 // LCD
  lcd.begin(lcd_columns, lcd_rows);
  lcd.clear();
  lcd.print("Audino 1012");
  lcd.setCursor(0,1);
  lcd.print("by billieblaze");
  lcd.clear();
  delay(500);
  init_phi_prompt(&lcd,keypads,function_keys, lcd_columns, lcd_rows, '~'); // Supply the liquid crystal object, input keypads, and function key names. Also supply the column and row of the lcd, and indicator as '>'. You can also use '\x7e', which is a right arrow.

}


void top_menu()
{
  int menu_pointer_1=0; // This stores the menu choice the user made.
  phi_prompt_struct myMenu; // This structure stores the main menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&top_menu_items; // Assign the list to the pointer
  myMenu.low.i=0; // Default item highlighted on the list
  myMenu.high.i=4; // Last item of the list is size of the list - 1.
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
    center_text("Top Menu");

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
      top_menu_function_3(&myMenu); // This is the setting function that changes how menu is rendered
      break;
      
  
      default:
      break;
    }

  }
}


void top_menu_function_2() //Replace this with the actual function of menu item #2
{
  lcd.clear();
  lcd.print("Sending data....");
  lcd.setCursor(0,1);
  lcd.print("-Your code here-");
  wait_on_escape(4000);
}

void top_menu_function_3(phi_prompt_struct * para) //Settings
{
  char buffer[32];
  byte opt=global_style, yn;
  
  lcd.clear();
  sprintf(buffer, "%s%d","Current style:", global_style);
  lcd.print(buffer);
  wait_on_escape(2000);
  for (byte i=0;i<7;i++)
  {
    lcd.clear();
    strcpy_P(buffer,(char*)pgm_read_word(menu_styles+i));
    yn=yn_dialog(buffer);
    bitWrite(opt,i,yn);
  }

  lcd.clear();
  sprintf(buffer, "%s%d","New style:", global_style=opt);
  lcd.print(buffer);
  wait_on_escape(2000);
  lcd.clear();
}

void sub_menu_1() // This is the sub_menu_1
{
  int menu_pointer_1=0;
  phi_prompt_struct myMenu; // This structure stores the sub menu.

// Initialize the top menu
  myMenu.ptr.list=(char**)&sub_menu_1_items; // Assign the list to the pointer
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
      sub_menu_1_function_3();
      break;
      
      case 5: // This option returns to previous level.
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

void top_menu_function_5() //Replace this with the actual function of menu item #2
{
//  show_credit();
}

void sub_menu_1_function_0()
{
  lcd.clear();
  lcd.print("Waveform");
  lcd.setCursor(0,1);
  int waveform;

  phi_prompt_struct myListInput; // This struct stores information for library functions 
  myListInput.ptr.list=(char**)&waveform_items;
myListInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myListInput.high.i=64; // Upper limit. The number wraps to 0 when increased from 20. 
myListInput.col=0; // Display the number at column 7 
myListInput.row=1; // Display the number at row 1 
myListInput.width=2; // The number occupies 2 character space. 
myListInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 
 myListInput.step.c_arr[0]=1; // Display the list as two rows 
myListInput.step.c_arr[1]=1; // Display the list as two columns 

  select_list(&myListInput);

  changeWave(myListInput.low.i-1, 0, 0,0);
}


void sub_menu_1_function_1()
{
  lcd.clear();
  lcd.print("WT Start");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&sampleStart; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=64; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=0; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_1_function_2()
{
  lcd.clear();
  lcd.print("WT End");
  lcd.setCursor(0,1);
  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&sampleEnd; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=64; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_1_function_3()
{
  lcd.clear();
  lcd.print("WT Offset");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&sampleOffset; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=63; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_1_function_4()
{
  lcd.clear();
  lcd.print("WT Delay");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&sampleDelay; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=63; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
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

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&gateState[0]; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=1; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=0; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_2_function_1()
{
  lcd.clear();
  lcd.print("Attack");
  lcd.setCursor(0,1);
  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&attackRate; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=64; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_2_function_2()
{
  lcd.clear();
  lcd.print("Decay");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&decayRate; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=63; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_2_function_3()
{
  lcd.clear();
  lcd.print("Sustain");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&sustainLevel; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=63; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}

void sub_menu_2_function_4()
{
  lcd.clear();
  lcd.print("Release");
  lcd.setCursor(0,1);

  phi_prompt_struct myIntegerInput; // This struct stores information for library functions 
  myIntegerInput.ptr.i_buffer=&releaseRate; // Pass the address of user_input to the library. After library function call, user input will be stored in this variable. Note the use of “&”. 
myIntegerInput.low.i=0; // Lower limit. The number wraps to 20 when decreased from 0. 
myIntegerInput.high.i=63; // Upper limit. The number wraps to 0 when increased from 20. 
myIntegerInput.step.i=1; // Step size. You will get 0, 2, 4, 6, 8, etc if you set it to 2. 
myIntegerInput.col=7; // Display the number at column 7 
myIntegerInput.row=1; // Display the number at row 1 
myIntegerInput.width=2; // The number occupies 2 character space. 
myIntegerInput.option=0; // Option 0, space pad right, 1, zero pad left, 2, space pad left. 

  input_integer(&myIntegerInput);

}
