	//beneath is list of menu items needed to build the menu
	MenuItem mi_oscillator = MenuItem("Oscillator");
	    MenuItem mi_waveform = MenuItem("Waveform");
                MenuItem mi_triangle = MenuItem("Triangle");
                MenuItem mi_square = MenuItem("Square");
                MenuItem mi_rampup = MenuItem("Rampup");
                MenuItem mi_rampdown = MenuItem("Rampdown");
                MenuItem mi_sine = MenuItem("Sine");
                MenuItem mi_noise = MenuItem("Noise");
                MenuItem mi_external = MenuItem("External");                
            MenuItem mi_frequency = MenuItem("Frequency");
        MenuItem mi_effect = MenuItem("Effect");
	    MenuItem mi_reverb = MenuItem("Reverb");    
	    MenuItem mi_phasor = MenuItem("Phasor");    
	    MenuItem mi_bitcrush = MenuItem("Bitcrush");    

/*
	This is an important function
	Here all use events are handled
	
	This is where you define a behaviour for a menu item
*/
void menuUseEvent(MenuUseEvent used){      
        lcd.setCursor(0,1); 
        
        
        if (used.item == mi_triangle){ 
            changeWave(0);
        }

        if (used.item == mi_square){ 
           changeWave(1);
        }

        if (used.item == mi_rampup){ 
           changeWave(2);
        }

        if (used.item == mi_rampdown){ 
           changeWave(3);
        }
       
       if (used.item == mi_sine){ 
           changeWave(4);
        }
        
        if (used.item == mi_noise){ 
           changeWave(5);
        }
        
        if (used.item == mi_external){ 
           changeWave(6);
        }
}


/*
	This is an important function
	Here we get a notification whenever the user changes the menu
	That is, when the menu is navigated
*/
void menuChangeEvent(MenuChangeEvent changed)
{
//        lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(changed.to.getName());

//	Serial.println(changed.to.getName());
}



//this controls the menu backend and the event generation
MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent);

//this function builds the menu and connects the correct items together
void menuSetup()
{
	//add the file menu to the menu root
	menu.getRoot().add(mi_oscillator).add(mi_waveform);
            
            mi_waveform.addRight(mi_triangle).addAfter(mi_square).addAfter(mi_rampup).addAfter(mi_rampdown).addAfter(mi_sine).addAfter(mi_noise).addAfter(mi_external);
            mi_waveform.addAfter(mi_frequency);

        mi_oscillator.addRight(mi_effect).addAfter(mi_reverb).addAfter(mi_phasor).addAfter(mi_bitcrush);
}

