#include "Joystick.h"

Joystick_ Joystick;

#define CLUTCH 0
#define BRAKE 1
#define ACCELERATOR 2

constexpr int NUM_PEDALS{ 3 };

int pedalMins[NUM_PEDALS];
int pedalMaxs[NUM_PEDALS];


void setup() {
    Joystick.begin();

    for (int pedalIndex = 0; pedalIndex < NUM_PEDALS; i++) {
        pedalMins[pedalIndex]       = 1023;
        pedalMaxs[pedalIndex]       = 0;
    }
    
}

// Returns a remapped value of the 'raw' position.
// Raw values from the potentiometers might not be
// full-range. To accomodate for that, we store the
// minimum and maximum values from the sensor and
// remap the position, wo we always get a full 0 - 1023
// range for the pedal position.
int getMappedPedalPosition(int pedal, int position) {
    // store (new) extremes of the pedal
    pedalMins[pedal] = min(position, pedalMins[pedal]);
    pedalMaxs[pedal] = max(position, pedalMaxs[pedal]);

    // remap the position to a 0 - 1023 range
    int mappedPostion = map(position, pedalMins[pedal], pedalMaxs[pedal], 0 , 1023 );
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
