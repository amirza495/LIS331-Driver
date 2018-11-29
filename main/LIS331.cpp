#include "LIS331.h"


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
  
  int data = 0;

  data = readRegister(reg+1, 1);
  data = data << 8;
  data |= readRegister(reg, 1); 

  return data;
}

float calibrate_axis(int raw)
{
  float value = 0.0;

  value = (float) raw/conversion;

  return value;
}

void LIS331_init(){
  
  Serial.begin(115200);

  // start the SPI library:
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);

  // initalize the  chip select pin:
  pinMode(chipSelectPin, OUTPUT);
  // give the sensor time to set up:
  delay(100);

  writeRegister(CTRL_REG1, PWR_MODE_ON | DATA_RATE_400HZ | Z_AXIS_ENABLE | Y_AXIS_ENABLE | X_AXIS_ENABLE);
  delay(100);

  int test = readRegister(CTRL_REG4, 1);
  Serial.println(test, BIN);

}

void LIS331_get_data(LIS331_t *gLIS331Data) {

  // zero raw data inputs
  gLIS331Data->raw.x = 0;
  gLIS331Data->raw.y = 0;
  gLIS331Data->raw.z = 0;

  // read each axis of data
  gLIS331Data->raw.x = read_axis(OUT_X_L);
  gLIS331Data->raw.y = read_axis(OUT_Y_L);
  gLIS331Data->raw.z = read_axis(OUT_Z_L);

  // convert data from LSB to g
  gLIS331Data->data.x = convert_axis(gLIS331Data->raw.x);
  gLIS331Data->data.y = convert_axis(gLIS331Data->raw.y);
  gLIS331Data->data.z = convert_axis(gLIS331Data->raw.z);

}
