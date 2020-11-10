#include "Joystick.h"

Joystick_ Joystick;

#define CLUTCH 0
#define BRAKE 1
#define ACCELERATOR 2

constexpr int NUM_PEDALS{ 3 };

int pedalMins[NUM_PEDALS];
int pedalMaxs[NUM_PEDALS];

constexpr int RANGE_LIMIT{ 1023 };

void setup() {
    Joystick.begin();

    for (int pedalIndex = 0; pedalIndex < NUM_PEDALS; i++) {
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
    int mappedPostion = map(rawPosition, pedalMins[pedal], pedalMaxs[pedal], 0 , RANGE_LIMIT);
    return mappedPostion;
}


void loop() {

    int clutchRawValue = analogRead(A0);
    int mappedClutchPosition = getMappedPedalPosition(CLUTCH, clutchRawValue);
    Joystick.setZAxis(mappedClutchPosition);

    int brakeRawValue = analogRead(A1);
    int mappedBrakePosition = getMappedPedalPosition(BRAKE, brakeRawValue);
    Joystick.setRxAxis(mappedBrakePosition);

    int acceleratorRawValue = analogRead(A2);
    int mappedAcceleratorPostion = getMappedPedalPosition(ACCELERATOR, acceleratorRawValue);
    Joystick.setRyAxis(mappedAcceleratorPostion);

    delay(20);
  
}
