#include <Arduino.h>

bool isRunning= true;
volatile int counter = 0;
bool isOn = false;
volatile bool useAudio = false;
bool useIMU = true;
const int buzzerPin = 2;
const int buttonInteruptPin = 4;
int freq = 1000;
float x, y, z;


//ble
#include "ArduinoBLE.h"
BLEService ControllerService = BLEService("19b10000e8f2537e4f6cd104768a1214");
BLECharCharacteristic Movement = BLECharCharacteristic("19b10001e8f2537e4f6cd104768a1214", BLERead | BLEWrite);

void ToggleLED() {
  isOn = !isOn;
  digitalWrite(LED_BUILTIN, isOn);
}

void setup() {
  //Set pin 13 (buildin LED) to output
  pinMode(LED_BUILTIN, OUTPUT);
 
  //Start serial
  Serial.begin(115200);

    //ble
    if (!BLE.begin()) {
      Serial.println("starting BLE failed!");    
    }  
    else {
      // set local name and advertised service for BLE:
      BLE.setLocalName("IRTS-BOT");
      BLE.setAdvertisedService(ControllerService);
    
      // add the characteristic and service:
      ControllerService.addCharacteristic(Movement);
      BLE.addService(ControllerService);
    
      // start advertising
      BLE.advertise(); 

      Serial.println("BLE Started!");    
    }

    
}

void loop() {
  if (isRunning)
  {
    BLEDevice central = BLE.central();

    if (central) {
          // print the central's BT address:
          Serial.print("Connected to central: ");
          Serial.println(central.address());
      
          while (central.connected()) {
            if (Movement.written())
            {
              unsigned char receivedContent = Movement.value();
              Serial.print(receivedContent); 
            }
           
          }
    }
    else
    {
      ToggleLED();      
      delay(2000);    
    }
  }
}
