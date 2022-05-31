#include <ArduinoBLE.h>
#include <Servo.h>

BLEService service("00000001-2276-4574-8adf-33af0ecdf20f");
BLEByteCharacteristic propCharacteristic("00000001-6ebc-4ae9-8ca1-fec7da94d7d2", BLERead | BLEWrite);
BLEByteCharacteristic driveCharacteristic("00000002-e451-4f97-983f-51cce04e34bf", BLERead | BLEWrite);

Servo prop;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    if (!BLE.begin()) {
        digitalWrite(LED_BUILTIN, 1);
        while (1);
    }
    
    BLE.setLocalName("Nano 33 BLE");
    BLE.setAdvertisedService(service);
    service.addCharacteristic(propCharacteristic);
    service.addCharacteristic(driveCharacteristic);
    BLE.addService(service);

    propCharacteristic.writeValue(0);
    driveCharacteristic.writeValue(0);
    BLE.advertise();

    prop.attach(D3, 1000, 2000);
    prop.writeMicroseconds(1500);
    delay(7000);
}

void loop() {
    BLEDevice central = BLE.central();

    if (central) {
        while (central.connected()) {  
            if (propCharacteristic.written()) {
                unsigned char pval = propCharacteristic.value();
                prop.writeMicroseconds(pval * 10 + 1000);
            }        
            if (driveCharacteristic.written()) {
                unsigned char dval = driveCharacteristic.value();
                analogWrite(A0, dval * 2.55);
            }
        }
    }
}
