#ifndef SPI_DRIVER_H_

#define SPI_DRIVER_H_

#include <Arduino.h>
#include <SPI.h>

const byte READ = 0b10000000;     // SCP1000's read command
const byte WRITE = 0b00000000;   // SCP1000's write command

// Start SPI interface
void SPI_init(void);

// read register function
unsigned int readRegister(int cs, byte reg, int len);

// write value to register
void writeRegister(int cs, byte reg, byte val);

#endif
