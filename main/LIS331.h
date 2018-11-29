#ifndef LIS331_H_

#define LIS331_H_

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

typedef struct{
  int x;
  int y;
  int z;
}LIS331_raw_data_t;

typedef struct {
  float x;
  float y;
  float z;
}LIS331_data_t;

typedef struct{ 
  LIS331_raw_data_t raw;
  LIS331_data_t data;  
}LIS331_t;


void LIS331_init();

void LIS331_get_data();


#endif