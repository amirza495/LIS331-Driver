#include "LIS331.h"

// conversion factor LSB/g divide raw value by this to get acceleration in g's
float conversion = 1000.0*5.6;

unsigned int read_axis(byte reg)
{
  
  int data = 0;

  data = readRegister(csLIS331, reg+1, 1);
  data = data << 8;
  data |= readRegister(csLIS331, reg, 1); 

  return data;
}

float convert_axis(int raw)
{
  float value = 0.0;

  value = (float) raw/conversion;

  return value;
}

void LIS331_init(){
  
  Serial.begin(115200);

  // start the SPI library:
  SPI_init();

  // initalize the  chip select pin:
  pinMode(csLIS331, OUTPUT);
  // give the sensor time to set up:
  delay(100);

  writeRegister(csLIS331, CTRL_REG1, PWR_MODE_ON | DATA_RATE_400HZ | Z_AXIS_ENABLE | Y_AXIS_ENABLE | X_AXIS_ENABLE);
  delay(100);

  int test = readRegister(csLIS331, CTRL_REG4, 1);
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
