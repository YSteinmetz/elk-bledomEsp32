#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>


#define SCAN_TIME 5



class elkBleDom{
  private:
    BLEAddress _addr;

  public:

    elkBleDom(BLEAddress& addr) : _addr(addr){};

    BLEAddress getAddr(){return _addr;};

    char serviceUUID[37] = "0000fff0-0000-1000-8000-00805f9b34fb";
    char characteristicUUID[37] = "0000fff3-0000-1000-8000-00805f9b34fb";

    uint8_t liga[9] = {0x7e, 0x00, 0x04, 0xf0, 0x00, 0x01, 0xff, 0x00, 0xef};
    uint8_t desliga[9] = {0x7e, 0x00, 0x04, 0x00, 0x00, 0x00, 0xff, 0x00, 0xef};
    //                                               R     G     B
    uint8_t vermelho[9] = {0x7e, 0x00, 0x05, 0x03, 0xff, 0x00, 0x00, 0x00, 0xef};
    uint8_t verde[9] =    {0x7e, 0x00, 0x05, 0x03, 0x00, 0xff, 0x00, 0x00, 0xef};
    uint8_t azul[9] =     {0x7e, 0x00, 0x05, 0x03, 0x00, 0x00, 0xff, 0x00, 0xef};

    uint8_t brightness(int value){ // min = 0, max = 64

      if(value < 0) value = 0;
      if(value > 100) value = 100;

      uint8_t brightness[9] = {0x7e, 0x00, 0x01, (uint8_t)value, 0x00, 0x00, 0x00, 0x00, 0xef};

      return (uint8_t)value;
    };

    uint8_t color(int r, int g, int b){ // min = 0, max = 255

      if(r < 0) r = 0;
      if(r > 255) r = 255;

      if(g < 0) g = 0;
      if(g > 255) g = 255;

      if(b < 0) b = 0;
      if(b > 255) b = 255;

      uint8_t color[9] = {0x7e, 0x00, 0x05, 0x03, (uint8_t)r, (uint8_t)g, (uint8_t)b, 0x00, 0xef};

      return (uint8_t)color;
    };

    uint8_t effect(int effect){

      if(effect < 0x80){
          effect = 0x80;
      }
      if(effect > 0x9c){
          effect = 0x9c;
      }

      uint8_t effect_[9] = {0x7e, 0x00, 0x03, (uint8_t)effect, 0x00, 0x00, 0x00, 0x00, 0xef};

    }



};





class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {

        BLEAddress deviceAddr = advertisedDevice.getAddress();
        String strAddr = deviceAddr.toString().c_str();

        Serial.printf("Dispositivo anunciado: %s\n", advertisedDevice.toString().c_str());

        if(strAddr.equals("be:58:de:01:cf:60")){

            Serial.printf("Encontrado!");

        }

    }
};


class MyClientCallbacks: public BLEClientCallbacks{
  void onConnect(BLEClient* pClient){
    Serial.println("Conexao estabelecida!");
  }

  void onDisconnect(BLEClient* pClient){
    Serial.println("Conexao perdida!");
  }
};


BLEScan* pBLEScan;
BLEAddress targetAddress("be:58:de:01:cf:60");
elkBleDom device(targetAddress);



void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  BLEDevice::init("Controller");

  Serial.printf("Iniciando...");

  BLEClient* pClient = BLEDevice::createClient();

  pClient->connect(device.getAddr());
  pClient->setClientCallbacks(new MyClientCallbacks());

  BLERemoteCharacteristic* pCharacteristic = pClient->getService(device.serviceUUID)->getCharacteristic(device.characteristicUUID);

  Serial.println("Ligando...");

  pCharacteristic->writeValue(device.liga,sizeof(device.liga));

  delay(1000);

  pCharacteristic->writeValue(device.vermelho,sizeof(device.liga));

  delay(1000);

  pCharacteristic->writeValue(device.verde,sizeof(device.liga));

  delay(1000);

  pCharacteristic->writeValue(device.azul,sizeof(device.liga));

  delay(1000);

}

void loop() {
  delay(2000);
  digitalWrite(2,true);
  delay(500);
  digitalWrite(2,false);
}


