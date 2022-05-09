/*
  The following variables are automatically generated and updated when changes are made to the Thing:

  bool access;
*/

#include "thingProperties.h"

int incomingByte = 0;  // For incoming serial data

void setup() {
    Serial.begin(9600);

    delay(1500);  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found

    initProperties();  // Defined in thingProperties.h

    ArduinoCloud.begin(ArduinoIoTPreferredConnection);  // Connect to Arduino IoT Cloud

    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
}

void loop() {
    ArduinoCloud.update();

    if (Serial.available() > 0) {  // When data has been received
        incomingByte = Serial.read();

        if (incomingByte == 1)
            access = true;  // Open door lock

        if (incomingByte == 0)
            access = false;  // Close door lock
    }
}

void onAccessChange() {
}