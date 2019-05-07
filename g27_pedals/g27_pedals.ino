#include "Joystick.h"

Joystick_ Joystick;

int zAxis_ = 0; 
int RxAxis_ = 0;                    
int RyAxis_ = 0;  

int zAxisMin = 1023;
int zAxisMax = 0;

int RxAxisMin = 1023;
int RxAxisMax = 0;

int RyAxisMin = 1023;
int RyAxisMax = 0;


void setup() {
  Joystick.begin();
}


void calibrate()
{
  int newZAxis = analogRead(A0);
  zAxisMin = min(newZAxis, zAxisMin);
  zAxisMax = max(newZAxis, zAxisMax); 

  int newRxAxis = analogRead(A1);
  RxAxisMin = min(RxAxisMin, newRxAxis);
  RxAxisMax = max(RxAxisMax, newRxAxis);


  int newRyAxis = analogRead(A2);
  RyAxisMin = min(RyAxisMin, newRyAxis);
  RyAxisMax = max(RyAxisMax, newRyAxis);
  
}


void loop() {

  calibrate();
  //should be Clutch
  zAxis_ = analogRead(A0);
  zAxis_ = map(zAxis_, zAxisMin, zAxisMax, 0 , 1023);
  Joystick.setZAxis(zAxis_);

  RxAxis_ = analogRead(A1);
  RxAxis_ = map(RxAxis_, RxAxisMin, RxAxisMax, 0 , 1023);
  Joystick.setRxAxis(RxAxis_);
  
  RyAxis_ = analogRead(A2);
  RyAxis_ = map(RyAxis_, RyAxisMin, RyAxisMax, 0, 1023);
  Joystick.setRyAxis(RyAxis_);

  delay(20);
  
}
