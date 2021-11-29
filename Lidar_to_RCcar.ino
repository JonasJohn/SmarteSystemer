#include <Servo.h>
#include "math.h"
Servo LidarServo;
Servo RCServo;
#define LidarServo 2
#define RCServo 3
  int motorPin = 5;
  float rOldDistance;
  float rNewDistance;
  float lengthB;
  float lengthC;
  int i;
  float angleA;
  int lengthA;
  float turnRadious;
analogWrite(motorPin, 175);
void setup() {
  // put your setup code here, to run once:
  //unsigned int distance = readLIDAR( 2000 );

  Serial.begin(115200);
  Serial1.begin(115200);
  LidarServo.attach(2);
  RCServo.attach(3);
  LidarServo.write(90);
  RCServo.write(90);
  Serial.println("Lidar ready...");
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:


  //right side scan
  LidarServo.write(90);
  delay(10);
  rOldDistance = readLIDAR (2000);
  rNewDistance = readLIDAR (2000);
  Serial.println("RESET");
  Serial.println(rOldDistance);
  Serial.println(rNewDistance);
  delay(1000);

  for (i = 90; i > 45; i--) {
    LidarServo.write(i);
    delay(50);
    rNewDistance = readLIDAR( 2000 );                     //read distance to obstacle at angle i
    delay(50);
    if (rNewDistance - rOldDistance > 50 ) {              //if true, then obstacle is not in the way anymore
      Serial.print(rNewDistance);
      Serial.print("\t - \t");
      Serial.print(rOldDistance);
      Serial.print("\t == \t");
      Serial.println(rNewDistance - rOldDistance);
      lengthB = rOldDistance;                        //set a designated distance for the car to drive around obstacle
      angleA = i;                                         //set i as angle a for calculations
      Serial.print("path found!! \nDist: \t");
      Serial.println(lengthB);
      Serial.print("Angle: \t");
      Serial.println(angleA);
      delay(10);
      //obstacleAvoidance();                               //call the funtion to avoid obstacle
      break;                                               //stop the for loop
    }

 
    
      Serial.print("newDist: \t");
      Serial.println(rNewDistance);
      Serial.print("oldDist: \t");
      Serial.println(rOldDistance);
      Serial.println();
    
    rOldDistance = rNewDistance;
    delay(10);
  }
    Serial.println("loop done!");
    

}

  void angleCalculation(){
    float lengthA = sqrt((sq(lengthB)) + (sq(lengthC)) - (2*lengthB*lengthC) * cos(angleA * 1000 / 57296));
    float angleBRad = acos(((sq(lengthA))+(sq(lengthC))-(sq(lengthB)))/(2*lengthA*lengthB));
    float angleBDeg = ((angleBRad * 57296) / 1000);
    Serial.println(lengthA);
    Serial.println(angleBDeg);
    Serial.println("calc complete!");
    Serial.println();
    delay(5000);
  }
   

  void obstacleAvoidance(){
    //turn the car to drive in paralell to the obstacle
    //drive for distance equal to "newDistance"
    //turn car 180 degrees in a semi-circle
    //drive back in paralell with the obstacle
    //turn car to come back to original path
   }


unsigned int readLIDAR( long timeout ) {

  unsigned char readBuffer[ 9 ];
  long t0 = millis();
  while ( Serial1.available() < 9 ) {
    if ( millis() - t0 > timeout ) {
      // Timeout
      return 0;
    }
    delay( 10 );
  }
  for ( int i = 0; i < 9; i++ ) {
    readBuffer[ i ] = Serial1.read();
  }
  while ( ! detectFrame( readBuffer ) ) {
    if ( millis() - t0 > timeout ) {
      // Timeout
      return 0;
    }
    while ( Serial1.available() == 0 ) {
      delay( 10 );
    }
    for ( int i = 0; i < 8; i++ ) {
      readBuffer[ i ] = readBuffer[ i + 1 ];
    }
    readBuffer[ 8 ] = Serial1.read();
  }
  // Distance is in bytes 2 and 3 of the 9 byte frame.
  unsigned int distance = ( (unsigned int)( readBuffer[ 2 ] ) ) |
                          ( ( (unsigned int)( readBuffer[ 3 ] ) ) << 8 );
  return distance;
}
bool detectFrame( unsigned char *readBuffer ) {
  return  readBuffer[ 0 ] == 0x59 &&
          readBuffer[ 1 ] == 0x59 &&
          (unsigned char)(
            0x59 +
            0x59 +
            readBuffer[ 2 ] +
            readBuffer[ 3 ] +
            readBuffer[ 4 ] +
            readBuffer[ 5 ] +
            readBuffer[ 6 ] +
            readBuffer[ 7 ]
          ) == readBuffer[ 8 ];
}
