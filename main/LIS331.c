#include "LIS331.h"
#include <SPI.h>

const int chipSelectPin = 10;

float conversion = 1000.0*5.6;


void LIS331_init(){
  

  // start the SPI library:
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);

  // initalize the  chip select pin:
  pinMode(chipSelectPin, OUTPUT);
  // give the sensor time to set up:
  delay(100);

  // config power and mode CTRL_REG1 register
  writeRegister(CTRL_REG1, PWR_MODE_ON | DATA_RATE_400HZ | Z_AXIS_ENABLE | Y_AXIS_ENABLE | X_AXIS_ENABLE);
  delay(100);

  // read out CTRL_REG4
  int test = readRegister(CTRL_REG4, 1);
  Serial.println(test, BIN);

}

//Read from a register over SPI
unsigned int readRegister(byte thisRegister, int bytesToRead) {
  byte inByte = 0;           // incoming byte from the SPI
  unsigned int result = 0;   // result to return

  byte dataToSend = thisRegister | READ;

  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);
  // send the device the register you want to read:
  SPI.transfer(dataToSend);
  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);

  // decrement the number of bytes left to read:
  bytesToRead--;

  // if you still have another byte to read:
  if (bytesToRead > 0) {
    // shift the first byte left, then get the second byte:
    result = result << 8;
    inByte = SPI.transfer(0x00);
    // combine the byte you just got with the previous one:
    result = result | inByte;
    // decrement the number of bytes left to read:
    bytesToRead--;

  }

  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);

  // return the result:
  return (result);
}


//Sends a write command to SCP1000
void writeRegister(byte thisRegister, byte thisValue) {

  // now combine the register address and the command into one byte:
  byte dataToSend = thisRegister | WRITE;

  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);

  SPI.transfer(dataToSend); //Send register location
  SPI.transfer(thisValue);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);
}

unsigned int read_axis(byte reg)
{
  
}
  int data = 0;

  data = readRegister(reg+1, 1);
  data = data << 8;
  data |= readRegister(reg, 1); 

  return data;
}

void LIS331_get_data(LIS331_t gLIS331Data) {

  gLIS331Data.raw.x = 0;
  gLIS331Data.raw.x = 0;
  gLIS331Data.raw.x = 0;
  
  gLIS331Data.raw.x = read_axis(OUT_X_L);
  gLIS331Data.raw.y = read_axis(OUT_Y_L);
  gLIS331Data.raw.z = read_axis(OUT_Z_L);

  
  data_x = data_x_raw/conversion;
  data_y = data_y_raw/conversion;
  data_z = data_z_raw/conversion;
  
  //Serial.print("The x accleration is: ");
  Serial.print(data_x);
  Serial.print(",");

  //Serial.print("The y accleration is: ");
  Serial.print(data_y);
  Serial.print(",");

  //Serial.print("The z accleration is: ");
  Serial.print(data_z);
  Serial.print(",");

}
