// 회전 방향  
#define CW  1   // clockwise
#define CCW 0   // counter-clockwise

  // 왼쪽, 오른쪽 바퀴  
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

 // motor POWER setting
#define DEFAULT_POWER 184

int sensorValue0 = 0; // variable to store the value coming from A0

 // 아두이노 PIN 설정
const byte PWMA = 3;      // PWM control (speed) for motor A
const byte PWMB = 11;     // PWM control (speed) for motor B
const byte DIRA = 12;     // Direction control for motor A
const byte DIRB = 13;     // Direction control for motor B
const unsigned int TRIG_PIN=8;
const unsigned int ECHO_PIN=9;

void setup()
{
  // initialization
   pinMode(TRIG_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
  setupArdumoto();
  Serial.begin(9600); 
}

void loop()
{
  digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 robotForward();
 const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
int distance= duration/29/2;
if(distance<10){
  robotRight();
  Serial.println(distance);
   Serial.println(" cm");
  } 
delay(100);
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



void driveArdumoto(byte motor, byte dir)
{
  if(motor == MOTOR_LEFT)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, DEFAULT_POWER*1.25);
  }
  else if(motor == MOTOR_RIGHT)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, DEFAULT_POWER*0.85);
  }  
}

void driveArdumoto2(byte motor, byte dir)
{
  if(motor == MOTOR_LEFT)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, DEFAULT_POWER*0);
  }
  else if(motor == MOTOR_RIGHT)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, DEFAULT_POWER*0.95);
    analogWrite(PWMA, DEFAULT_POWER*0);
  }  
}

void robotForward()
{
  driveArdumoto(MOTOR_LEFT, CCW);
  driveArdumoto(MOTOR_RIGHT, CW);
}

void robotBackward()
{
  driveArdumoto(MOTOR_LEFT, CW);
  driveArdumoto(MOTOR_RIGHT, CCW);
}

void robotRight()
{
  driveArdumoto(MOTOR_LEFT, CCW);
  driveArdumoto(MOTOR_RIGHT, CCW);
}

void robotLeft()
{
  driveArdumoto(MOTOR_LEFT, CW);
  driveArdumoto(MOTOR_RIGHT, CW);
}
//void robotRightBack()
//{
//  driveArdumoto(MOTOR_LEFT, CW);
//  driveArdumoto(MOTOR_RIGHT, CCW);
//}
