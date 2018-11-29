/* This set of documents is intended to function as a driver writing tutorial
   If you follow the instructions in the comments and reference the datasheet, you should end up with a fully functioning driver
   This document is a copy of the program in master, just with every line of code replaced with a comment
   You can check your code using hardware or reference it against the functioning code in master - You can purchase one of these sensors here (https://www.sparkfun.com/products/10345)
   This is certainly not the only way to write a driver, but its the method that has worked well for me in the past and is simple and straight forward
   To get the most out of this try to think about the purpose of each line as you write it, and understand why its necessary. There should be no need for erraneous lines of code
   I have included a fully functioning SPI driver, all of the register definitions I needed to write my version of the driver, and function prototypes for your convenience
   Good luck and enjoy writing your simple LIS331 3-axis accelerometer driver! 
   */

// include driver header file


// declare global data struct

void setup() {

  // configure serial output - use a high baud rate for faster polling times ex: 115200

  
  // initialize sensor


}

void loop() {
  // poll sensor for data
  

  // print each axis in a CSV format

  // delay for polling rate below that of sensor setting

}
