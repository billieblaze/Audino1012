// DAC 
#define SLAVESELECT 3

void setupDAC(){
  pinMode(SLAVESELECT, OUTPUT);
  digitalWriteFast(SLAVESELECT, HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin(); 
}

void SPISend(word value){  // TODO: add DAC addressing
  volatile byte data = highByte(value);
  data = B00111111 & data; // clear 4-bit command field (optional)
  data = B10000000 | data; // 0=DACA, 0=buffered, 1=1x, 1=output enabled

  digitalWriteFast(SLAVESELECT, LOW); // select the chip
  SPI.transfer(data);

  data = lowByte(value);
  SPI.transfer(data);
  digitalWriteFast(SLAVESELECT, HIGH);
}
