#include <Joystick.h>

#include "Joystick.h"

Joystick_ Joystick(
  0x03,                       // Default, don't change
  JOYSTICK_TYPE_MULTI_AXIS,   // Type
  0,                          // Button Count
  0,                          // HatSwitch Count
  false,                      // includeXAxis
  false,                      // includeYAxis
  false,                      // includeZAxis
  false,                      // includeRxAxis
  false,                      // includeRyxis
  false,                      // includeRzxis
  false,                      // includeRudder
  true,                       // includeThrottle
  true,                       // includeAccelerator
  true,                       // includeBrake
  false                      // includeSteering
  
);

#define CLUTCH 0
#define BRAKE 1
#define ACCELERATOR 2

constexpr int NUM_PEDALS{ 3 };

int pedalMins[NUM_PEDALS];
int pedalMaxs[NUM_PEDALS];
//const int limit = (1 << 16) -1;
constexpr long int RANGE_LIMIT{ 1023 };

void setup() {
    Joystick.begin();

    for (int pedalIndex = 0; pedalIndex < NUM_PEDALS; pedalIndex++) {
        pedalMins[pedalIndex] = RANGE_LIMIT;
        pedalMaxs[pedalIndex] = 0;
    }
    
}

// Returns a remapped value of the 'raw' position.
// Raw values from the potentiometers might not be within a 0 - 1023 range. 
// To accomodate for that, we store the minimum and maximum values from the sensor and
// remap the position, so we always get a full 0 - 1023 range for that pedal's position.
int getMappedPedalPosition(int pedal, int rawPosition) {
    // store (new) extremes of the pedal
    pedalMins[pedal] = min(rawPosition, pedalMins[pedal]);
    pedalMaxs[pedal] = max(rawPosition, pedalMaxs[pedal]);

    // remap the position to a 0 - 1023 range
    int mappedPostion = map(rawPosition, pedalMins[pedal], pedalMaxs[pedal], RANGE_LIMIT, 0);
    return mappedPostion;
}


void loop() {
    
    int rawClutchPosition = analogRead(A0);
    int mappedClutchPosition = getMappedPedalPosition(CLUTCH, rawClutchPosition);
    Joystick.setThrottle(mappedClutchPosition);

    int rawAcceleratorPosition = analogRead(A1);
    int mappedAcceleratorPostion = getMappedPedalPosition(ACCELERATOR, rawAcceleratorPosition);
    Joystick.setBrake(mappedAcceleratorPostion);

    int rawBrakePosition = analogRead(A2);
    int mappedBrakePosition = getMappedPedalPosition(BRAKE, rawBrakePosition);
    Joystick.setAccelerator(mappedBrakePosition);

    

    delay(20);
  
}
