#include <ArduinoBLE.h>
#include <Servo.h>
#define PROP_PIN 21
#define DRIVE_PIN 23

BLEService service("00000001-2276-4574-8adf-33af0ecdf20f");
BLEByteCharacteristic propCharacteristic("00000001-6ebc-4ae9-8ca1-fec7da94d7d2", BLERead | BLEWrite);
BLEByteCharacteristic driveCharacteristic("00000002-e451-4f97-983f-51cce04e34bf", BLERead | BLEWrite);

Servo prop, drive;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    if (!BLE.begin()) {
        digitalWrite(LED_BUILTIN, 1);
        while (1);
    }

    // maybe set pinmode

    service.addCharacteristic(propCharacteristic);
    service.addCharacteristic(driveCharacteristic);
    BLE.setLocalName("Nano 33 BLE");
    BLE.setAdvertisedService(service);
    BLE.addService(service);

    propCharacteristic.writeValue(0);
    driveCharacteristic.writeValue(0);
    BLE.advertise();

    prop.attach(PROP_PIN, 1000, 2000);
    drive.attach(DRIVE_PIN, 1000, 2000);
}

void loop() {
    BLEDevice central = BLE.central();

    if (central) {
        while (central.connected()) {
            digitalWrite(LED_BUILTIN, HIGH);
            if (propCharacteristic.written()) {
                digitalWrite(LED_BUILTIN, LOW);
                delay(200);
                unsigned char value = propCharacteristic.value();
                prop.writeMicroseconds(value * 10 + 1000);
            }
            if (driveCharacteristic.written()) {
                unsigned char value = driveCharacteristic.value();
                drive.writeMicroseconds(value * 10 + 1000);
            }
        }
        digitalWrite(LED_BUILTIN, LOW);   
    }
}
