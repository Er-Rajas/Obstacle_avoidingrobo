
//open source code
//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //

 
#include <AFMotor.h>  
 
#include <NewPing.h>
#include <Servo.h> 
 
#define TRIG_PIN A0
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
 
#define MAX_SPEED 250 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 10
 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
 
  AF_DCMotor motor1(1, MOTOR12_64KHZ); 
  AF_DCMotor motor2(2, MOTOR12_64KHZ);
  //AF_DCMotor motor3(3, MOTOR34_1KHZ);
  //AF_DCMotor motor4(4, MOTOR34_64KHZ);
Servo myservo;   
 
boolean goesForward=false;
int distance = 255;
int speedSet = 250;
 
void setup() {
 
  myservo.attach(10);  
  myservo.write(90); 
  delay(1000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}
 
void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=20)
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(400);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(150);
  distanceL = lookLeft();
  delay(150);
 
  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
 delay(200);
}
 
int lookRight()
{
    myservo.write(10); 
    delay(700);
    int distance = readPing();
    delay(150);
    myservo.write(90); 
    return distance;
}
 
int lookLeft()
{
    myservo.write(170); 
    delay(700);
    int distance = readPing();
    delay(150);
    myservo.write(90); 
    return distance;
    delay(150);
}
 
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 255;
  }
  return cm;
}
 
void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  //motor3.run(RELEASE);
  //motor4.run(RELEASE);
  } 
  
void moveForward() {
 
 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    //motor3.run(FORWARD); 
    //motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);  //left
    motor2.setSpeed(speedSet-102 );  //right
    //motor3.setSpeed(speedSet);
    //motor4.setSpeed(speedSet);
    delay(10);
   }
  }
}
 
void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    //motor3.run(BACKWARD);
    //motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet-102);
    //motor3.setSpeed(speedSet);
    //motor4.setSpeed(speedSet);
    delay(10);
  }
}  
 
void turnRight() 
{
  motor1.run(BACKWARD);
//  motor4.run(BACKWARD);
//  motor3.run(FORWARD);
  motor2.run(FORWARD);     
  delay(1000);
  motor1.run(BACKWARD);      
//  motor4.run(FORWARD);
//  motor3.run(FORWARD);
  motor2.run(BACKWARD);      
} 
 
void turnLeft() {
  motor1.run(FORWARD);     
  //motor4.run(FORWARD);  
  //motor3.run(BACKWARD);
  motor2.run(BACKWARD);   
  delay(1000);
  motor1.run(BACKWARD);     
//  motor4.run(FORWARD);
//  motor3.run(FORWARD);
  motor2.run(BACKWARD);
}  
