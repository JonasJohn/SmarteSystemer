#include "Servo.h";
int motorPin = 5;  //speed motor a
Servo myservo;

long duration; 
int distance; 
#define echoPin 6 
#define trigPin 7 

int R_B = 11;
int C_B = 12;
int L_B = 13;

int R_F = 10; 
int C_F = 9; 
int L_F = 8; 


void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

Serial.begin(9600);
myservo.attach(3);
myservo.write(90);
pinMode(motorPin, OUTPUT);
analogWrite(motorPin, 175);
delay(2000);



pinMode(L_B, INPUT);
pinMode(C_B, INPUT);
pinMode(R_B, INPUT);

pinMode(L_F, INPUT);
pinMode(C_F, INPUT);
pinMode(R_F, INPUT);


}
void loop()
{  

analogWrite(motorPin, 183); 

if (((digitalRead(L_F) == 0)&&(digitalRead(C_F) == 0)&&(digitalRead(R_F) == 0)) ||
  ((digitalRead(L_B) == 0)&&(digitalRead(C_B) == 0)&&(digitalRead(R_B) == 0))){straight();}

if (((digitalRead(L_F) == 0)&&(digitalRead(C_F) == 1)&&(digitalRead(R_F) == 0)) ||
  ((digitalRead(L_B) == 0)&&(digitalRead(C_B) == 1)&&(digitalRead(R_B) == 0))){straight();}

if (((digitalRead(L_F) == 1)&&(digitalRead(C_F) == 1)&&(digitalRead(R_F) == 0)) || 
    ((digitalRead(L_B) == 1)&&(digitalRead(C_B) == 1)&&(digitalRead(R_B) == 0))){hardRight();}
    
if (((digitalRead(L_F) == 1)&&(digitalRead(C_F) ==0)&&(digitalRead(R_F) == 0)) || 
    ((digitalRead(L_B) == 1)&&(digitalRead(C_B) ==0)&&(digitalRead(R_B) == 0))){turnRight();}

if (((digitalRead(L_F) == 0)&&(digitalRead(C_F) == 1)&&(digitalRead(R_F) == 1)) || 
     ((digitalRead(L_B) == 0)&&(digitalRead(C_B) == 1)&&(digitalRead(R_B) == 1))){hardLeft();}
  
if (((digitalRead(L_F) == 0)&&(digitalRead(C_F) == 0)&&(digitalRead(R_F) == 1)) || 
    ((digitalRead(L_B) == 0)&&(digitalRead(C_B) == 0)&&(digitalRead(R_B) == 1))){turnLeft();}

  if (((digitalRead(L_F) == 1)&&(digitalRead(C_F) == 1)&&(digitalRead(R_F) == 1)) ||
    ((digitalRead(L_B) == 1)&&(digitalRead(C_B) == 1)&&(digitalRead(R_B) == 1))){Stop();} // Use two line reader sensors, for more accurate output

bool LeftF = digitalRead(L_F);
bool CenterF = digitalRead(C_F);
bool RightF = digitalRead(R_F);
bool LeftB = digitalRead(L_B);
bool CenterB = digitalRead(C_B);
bool RightB = digitalRead(R_B);


Serial.print("Front: ");
Serial.print(LeftF);
Serial.print(CenterF);
Serial.println(RightF);
Serial.print("Back: ");
Serial.print(LeftB);
Serial.print(CenterB);
Serial.println(RightB);



// Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 50) {  //not perfect, need to calculate recovery angle
    myservo.write(65);
    delay(1500);
    myservo.write(90);
    delay(500);
    myservo.write(115);
    delay(1500);
    myservo.write(90);
    delay(500);
    myservo.write(65);
    //delay(500);


  }
//delay(400);
}



void turnRight(){
myservo.write(86);

}


void hardRight(){
  myservo.write(65);
}


void turnLeft(){
myservo.write(94);
}

void hardLeft(){
  myservo.write(115);
}

void straight(){
  myservo.write(90);
}



void Stop(){
  analogWrite(motorPin, 175); 
  myservo.write(65);
  delay(500);
  analogWrite(motorPin, 183);
  delay(1000);
}
