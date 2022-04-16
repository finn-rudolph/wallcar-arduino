#include <ArduinoBLE.h>

const char[] serviceUuid = "00-00-00-01-22-76-45-74-8a-df-33-af-0e-cd-f2-0f";
const char[] propUuid = "00-00-00-01-6e-bc-4a-e9-8c-a1-fe-c7-da-94-d7-d2";
const char[] driveUuid = "00-00-00-02-e4-51-4f-97-98-3f-51-cc-e0-4e-34-bf";

BLEService service(serviceUuid);
BLEByteCharacteristic propCharacteristic(propUuid);
BLEByteCharacteristic driveCharacteristic(driveUuid);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    if (!BLE.begin()) {
        digitalWrite(LED_BUILTIN, 1);
        while (1);
    }

    BLE.setLocalName("Nano 33");
    BLE.setAdvertisedService(service);
    service.addCharacteristic(propCharacteristic);
    service.addCharacteristic(driveCharacteristic);

    propCharacteristic.writeValue(0);
    driveCharacteristic.writeValue(0);
    BLE.advertise();
}

void loop() {
    BLEDevice central = BLE.central();

    if (central) {
        while (central.connected()) {
            if (propCharacteristic.written()) {
                digitalWrite(LED_BUILTIN, 1);
                delay(5);
                digitalWrite(LED_BUILTIN, 0);
            }
            if (driveCharacteristic.written()) {

            }
        }    
    }
}