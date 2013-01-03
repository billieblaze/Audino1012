/*int lfoWave[] = {0, 1};
int lfoValue[] = {0,0};
int lfoRate[] = {10, 20};
word lfoCnt[] = {0,0};

void LFOStep(){ 
   
    for ( int x = 0; x < 2; x++){
      
      switch(lfoWave[x]){
        case 0: // triangle
          
          if (lfoCnt[x] < 2048){ 
            lfoValue[x]++;
          } else {
            lfoValue[x]--;
          }
        break;
        
        case 1: // Square
          if (lfoCnt[x] < 2048){ 
            lfoValue[x] = 0;
          } else {
            lfoValue[x] = 1;
          }
      
        break;
        
        case 2: // ramp
          lfoCnt[x]++;
      }      
      
      lfoCnt[x] = lfoCnt[x] + lfoRate[x] ;
   } 
}*/
