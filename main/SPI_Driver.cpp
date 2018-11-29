#include "SPI_Driver.h"

// Start SPI interface
// still must configure chip select pin as OUTPUT
void SPI_init(){
    // start SPI
    SPI.begin();

    // set to MSB first mode
    SPI.setBitOrder(MSBFIRST);
}

//Read from a register over SPI
unsigned int readRegister(int cs, byte reg, int len) {
  
  byte inByte = 0;           // incoming byte from the SPI
  unsigned int result = 0;   // result to return

  byte dataToSend = reg | READ;

  // take the chip select low to select the device:
  digitalWrite(cs, LOW);
  // send the device the register you want to read:
  SPI.transfer(dataToSend);
  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);

  // decrement the number of bytes left to read:
  len--;

  // if you still have another byte to read:
  if (len > 0) {
    // shift the first byte left, then get the second byte:
    result = result << 8;
    inByte = SPI.transfer(0x00);
    // combine the byte you just got with the previous one:
    result = result | inByte;
    // decrement the number of bytes left to read:
    len--;

  }

  // take the chip select high to de-select:
  digitalWrite(cs, HIGH);

  // return the result:
  return (result);
}


//Sends a write command to SPI device
void writeRegister(int cs, byte reg, byte val) {

  // now combine the register address and the command into one byte:
  byte data = reg | WRITE;

  // take the chip select low to select the device:
  digitalWrite(cs, LOW);

  SPI.transfer(data); //Send register location
  SPI.transfer(val);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(cs, HIGH);
}
