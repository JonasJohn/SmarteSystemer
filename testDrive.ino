#include <PS4BT.h>            //Including libraries.
#include <Servo.h>
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR); 

Servo servo1;        // servo1 is the steering servo and servo2 is the ESC motor .
Servo servo2;

int offset = 0; 
int steer = 127; 

void setup() {
  Serial.begin(115200);                                              
  if (Usb.Init() == -1) {                                            
    Serial.print(F("\r\nOSC did not start"));
    while(1); 
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));              
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  servo1.attach(5);                      //Steering servo on digital pin 5
  servo2.attach(3);                        //ESC on sigital pin 3
}
void loop() 
{
  Usb.Task();

  if (PS4.connected()) {
    
    steer = PS4.getAnalogHat(RightHatX); // read right joystick
    
    if(PS4.getButtonClick(RIGHT)) { 
      offset += 1;
    }
    if(PS4.getButtonClick(LEFT)) { 
      offset -= 1;
    }
    steer = steer + offset; 
    if(steer > 255) steer = 255;
    if(steer < 0) steer = 0; 
    
    servo1.write(map(steer, 0, 255, 0, 180)); 
    servo2.write(map(PS4.getAnalogHat(LeftHatY), 0, 255, 180, 0)); 
  }
  else 
   {
    servo1.write(90);
    servo2.write(90);
   } 
    if(PS4.getButtonClick(PS)) {
      PS4.disconnect(); }
}
