#include <Servo.h>
#define PROP_PIN 21
#define DRIVE_PIN 23

Servo prop, drive;

void setup() {
    prop.attach(PROP_PIN, 1000, 2000);
    drive.attach(DRIVE_PIN, 1000, 2000);
}

void loop() {
    delay(5000);
    prop.writeMicroseconds(2000);
    drive.writeMicroseconds(1200);
}