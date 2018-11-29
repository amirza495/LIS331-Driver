#include <SPI.h>

#define WHO_AM_I        0x0F

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24
#define HP_FILTER_RESET 0x25
#define REFERENCE       0x26
#define STATUS_REG      0x27
#define OUT_X_L         0x28
#define OUT_X_H         0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D

// CTRL_REG1 Values
#define PWR_MODE_ON     (1 << 5)
#define DATA_RATE_50HZ  (1 << 3)
#define DATA_RATE_100HZ (2 << 3)
#define DATA_RATE_400HZ (3 << 3)
#define Z_AXIS_ENABLE   (1 << 2)
#define Y_AXIS_ENABLE   (1 << 1)
#define X_AXIS_ENABLE   (1 << 0)

// CTRL_REG4
#define FS_2g           (0 << 4)
#define FS_4g           (1 << 4)
#define FS_8g           (3 << 4)


const byte READ = 0b10000000;     // SCP1000's read command
const byte WRITE = 0b00000000;   // SCP1000's write command

//const int dataReadyPin = 6;
const int chipSelectPin = 10;
const int adxl377XPin = A0;
const int adxl377YPin = A1;
const int adxl377ZPin = A2;

typedef struct{

  int raw_x;
  int raw_y;
  int raw_z;
  float x;
  float y;
  float z;
  
}adxl377_data_t;

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // start the SPI library:
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);

  // initalize the  data ready and chip select pins:
  //pinMode(dataReadyPin, INPUT);
  pinMode(chipSelectPin, OUTPUT);
  // give the sensor time to set up:
  delay(100);

  writeRegister(CTRL_REG1, PWR_MODE_ON | DATA_RATE_400HZ | Z_AXIS_ENABLE | Y_AXIS_ENABLE | X_AXIS_ENABLE);
  delay(100);

  int test = readRegister(CTRL_REG4, 1);
  Serial.println(test, BIN);


}

int data_x_raw;
int data_y_raw;
int data_z_raw;

float data_x;
float data_y;
float data_z;

float conversion = 1000.0*5.6;

float highGConvert = 4.9/6.5;

adxl377_data_t highGAccel;

unsigned int read_axis(byte reg)
{
  int data = 0;

  data = readRegister(reg+1, 1);
  data = data << 8;
  data |= readRegister(reg, 1); 

  return data;
}

void loop() {
  // put your main code here, to run repeatedly:

  data_x_raw = 0;
  data_y_raw = 0;
  data_z_raw = 0;
  
  data_x_raw = read_axis(OUT_X_L);
  data_x = data_x_raw/conversion;
  //Serial.print("The x accleration is: ");
  Serial.print(data_x);
  Serial.print(",");

  data_y_raw = read_axis(OUT_Y_L);
  data_y = data_y_raw/conversion;
  //Serial.print("The y accleration is: ");
  Serial.print(data_y);
  Serial.print(",");

  data_z_raw = read_axis(OUT_Z_L);
  data_z = data_z_raw/conversion;
  //Serial.print("The z accleration is: ");
  Serial.print(data_z);
//  Serial.print(",");
/*
  highGAccel.raw_x = analogRead(adxl377XPin) - 441;
  highGAccel.raw_y = analogRead(adxl377YPin) - 441;
  highGAccel.raw_z = analogRead(adxl377ZPin) - 441;

  highGAccel.x = highGAccel.raw_x * highGConvert;
  highGAccel.y = highGAccel.raw_y * highGConvert;
  highGAccel.z = highGAccel.raw_z * highGConvert;

  Serial.print(highGAccel.x);
  Serial.print(",");
  Serial.print(highGAccel.y);
  Serial.print(",");
  Serial.print(highGAccel.z);
*/  
  Serial.print("\n\r");

  delay(7);

}
