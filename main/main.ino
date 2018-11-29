#include "LIS331.h"

LIS331_t gLIS331Data;

void setup() {
  // put your setup code here, to run once:
  LIS331_init();

}

void loop() {
  // put your main code here, to run repeatedly:
  LIS331_get_data(gLIS331Data);

}
