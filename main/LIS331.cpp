#include "LIS331.h"

// conversion factor LSB/g divide raw value by this to get acceleration in g's
// hint: look under sensitivity in Mechanical Characteristics table in the data sheet


/////////////////////////////////////////////
/* HELPER FUNCTIONS BELOW                 */
////////////////////////////////////////////


// read helper function
// should read axis and store properly into upper and lower halves of uint
// returns data as uint16
unsigned int read_axis(byte reg)
{
  

}

// conversion helper
// should take raw sensor values and convert from LSB (least significant bits) to g or m/s^2
float convert_axis(int raw)
{

}

// sensor initialization function
void LIS331_init(){

  // start the SPI library, hint: look in SPI_Driver.h
  

  // initalize the  chip select pin:
  

  // write to registers to configure sensor
  // make sure power mode is enabled and all axes are enabled
  // hint: look for register definitions in LIS331.h


  // delay 100 ms for setup


  // verify a sensor value using readRegister if you'd like


}

void LIS331_get_data(LIS331_t *gLIS331Data) {

  // zero raw data inputs in struct
  // hint: remember to use form "data->str" when referencing a pointer to a data struct


  // read each axis of data


  // convert data from LSB to g


}
