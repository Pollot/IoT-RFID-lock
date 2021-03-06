/*
  The following variables are automatically generated and updated when changes are made to the Thing:

  bool access;
*/

#include <Servo.h>

#include "thingProperties.h"  // Arduino IoT cloud library

#define servoPin D0
#define relayPin D1  // Relay is used for cutting off servo power

Servo lockServo;

void setup() {
    lockServo.attach(servoPin);

    pinMode(relayPin, OUTPUT);

    digitalWrite(relayPin, HIGH);  // Turn relay off

    Serial.begin(9600);

    delay(1500);  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found

    initProperties();  // Defined in thingProperties.h

    ArduinoCloud.begin(ArduinoIoTPreferredConnection);  // Connect to Arduino IoT Cloud

    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
}

void loop() {
    ArduinoCloud.update();
}

void onAccessChange() {
    digitalWrite(relayPin, LOW);  // Turn relay on

    delay(100);

    if (access == true)
        lockServo.write(0);
    else
        lockServo.write(120);

    delay(2000);

    digitalWrite(relayPin, HIGH);  // Turn relay off
}