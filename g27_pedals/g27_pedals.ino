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


void setMinAndMaxForPedal(int pedal, int position) {
    pedalMins[pedal] = min(analogValue, pedalMins[pedal]);
    pedalMaxs[pedal] = max(analogValue, pedalMaxs[pedal]);
}

int getMappedPedalPosition(int pedal, int position) {
    setMinAndMaxForPedal(pedal, position);
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
