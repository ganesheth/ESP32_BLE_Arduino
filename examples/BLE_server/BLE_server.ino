/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define ADV_SERVICE_UUID        "1801"
#define MFG_DATA        "Some data"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  //pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertisementData advData;
  BLEUUID serviceId((uint16_t)0x1801);
  advData.setCompleteServices(serviceId);
  char cdata[22] = {0x0c, 0x03, 0x00, 0xb8, 0xdc, 0x20, 0x3e, 0xbd, 0xe1, 0x11, 0x0f, 0xbe, 0x20, 0x00, 0x16, 0x60, 0x45, 0x04, 0x16, 0xb0, 0x00, 0x00};
  //---------------------------------------------------.......................-----------------------------------------------------------------------
  advData.setManufacturerData(std::string(cdata, 22));
  pAdvertising->setAdvertisementData(advData);
  pAdvertising->setAdvertisementInterval(7900, 8100);
  pAdvertising->start();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}