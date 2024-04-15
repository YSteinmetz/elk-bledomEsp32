#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>


class MyCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.println(advertisedDevice.toString().c_str());
  }
};

//BLEAdvertisedDevice target = "be:58:de:01:cf:60"; //Put the mac address of yours led strip


void setup() {
  
   Serial.begin(9600);
   Serial.println("Starting BLE work!");

   BLEDevice::init("ESP32");
   BLEScan* pBLEScan = BLEDevice::getScan();
   pBLEScan->setAdvertisedDeviceCallbacks(new MyCallbacks());
   pBLEScan->start(30);

   if(pBLEScan);



   


}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}