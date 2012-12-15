

void setupDAC(){
  // initialize SPI:22
  pinMode(SLAVESELECT, OUTPUT);
  digitalWrite(SLAVESELECT, HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin(); 
}

void SPISend(word value){
  byte data = highByte(value);
  data = B00111111 & data; // clear 4-bit command field (optional)
  data = B10000000 | data; // 0=DACA, 0=buffered, 1=1x, 1=output enabled

  digitalWrite(SLAVESELECT, LOW); // select the chip
  SPI.transfer(data);

  // send low byte
  data = lowByte(value);
  SPI.transfer(data);
  
  digitalWrite(SLAVESELECT, HIGH);
 
}
