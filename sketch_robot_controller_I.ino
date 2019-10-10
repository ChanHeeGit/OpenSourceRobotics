// battle robot
#include <SoftwareSerial.h>     // 시리얼 통신 라이브러리 호출

int blueRx = 4;     // Rx (보내는핀 설정)
int blueTx = 5;     // Tx (받는핀 설정)

SoftwareSerial mySerial(blueRx, blueTx);      // 시리얼 통신을 위한 객체 선언
int phoneData;      // 시리얼 데이터를 받기 위한 변수 선언

  // 회전 방향  선언
#define CW  1   // clockwise
#define CCW 0   // counter-clockwise

  // 왼쪽, 오른쪽 바퀴  선언
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

 // motor 스피드 선언
#define SPEED 150 

 // 아두이노 PIN 설정
const byte PWMA = 3;      // PWM control (speed) for motor A
const byte PWMB = 11;     // PWM control (speed) for motor B
const byte DIRA = 12;     // Direction control for motor A
const byte DIRB = 13;     // Direction control for motor B

// LED
const int LED =  LED_BUILTIN;// the number of the LED pin


void setup()
{
  Serial.begin(9600);       // 시리얼 포트 설정
  mySerial.begin(9600);      // 선언된 객체와 시리얼 포트 설정
  
  setupArdumoto();      // Set all pins as outputs
  blinkLed();           // blink LED 
}
 
void loop()
{
  phoneData = mySerial.read();      // 시리얼 통신으로 받은 데이터 READ
  
  // If there is data to read and read is sucessful 
  if (phoneData != -1)
  {
    Serial.println(phoneData); // display data read to Serial port
    switch(phoneData)
    {
      case 1:
      // Serial.write("1");
      robotForward(SPEED);     
      break;
      
      case 2:
      // Serial.write("2");
      robotBackward(SPEED);
      break;
      
      case 3:
      // Serial.write("3");
      robotRight(SPEED);
      break;
      
      case 4:
      // Serial.write("4");
      robotLeft(SPEED);
      break;
      
    case 5:
      // Serial.write("5");
      robotStop();
      break;
      }
     }
}


void blinkLed()
{
 pinMode(LED, OUTPUT);
 digitalWrite(LED, HIGH);
 delay(500);
 digitalWrite(LED, LOW);
 delay(500);  
}

  // setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  
  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

  // stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

void driveArdumoto(byte motor, byte dir, byte spd)
{
  if(motor == MOTOR_RIGHT)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if(motor == MOTOR_LEFT)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}
 
void robotForward(int velocity)
{
  driveArdumoto(MOTOR_LEFT, CCW, velocity*1.35);
  driveArdumoto(MOTOR_RIGHT, CW, velocity);
}

void robotBackward(int velocity)
{
  driveArdumoto(MOTOR_LEFT, CW, velocity*1.35);
  driveArdumoto(MOTOR_RIGHT, CCW, velocity);
}

void robotRight(int velocity)
{
  driveArdumoto(MOTOR_LEFT, CCW, velocity*1.35);
  driveArdumoto(MOTOR_RIGHT, CCW, velocity);
}

void robotLeft(int velocity)
{
  driveArdumoto(MOTOR_LEFT, CW, velocity*1.35);
  driveArdumoto(MOTOR_RIGHT, CW, velocity);
}

void robotStop()
{
  stopArdumoto(MOTOR_LEFT);
  stopArdumoto(MOTOR_RIGHT);
}
