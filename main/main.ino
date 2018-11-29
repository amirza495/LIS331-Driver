#include "LIS331.h"

LIS331_t gLIS331Data;

void setup() {
  // put your setup code here, to run once:
  LIS331_init();

  Serial.println("Initialization Complete");

}

void loop() {
  // put your main code here, to run repeatedly:
  LIS331_get_data(&gLIS331Data);

  //Serial.print("The x accleration is: ");
  Serial.print(gLIS331Data.data.x);
  Serial.print(",");

  //Serial.print("The y accleration is: ");
  Serial.print(gLIS331Data.data.y);
  Serial.print(",");
  
  //Serial.print("The z accleration is: ");
  Serial.print(gLIS331Data.data.z);
  Serial.print("\r\n");

  delay(10);

}
