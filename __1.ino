
  // 회전 방향  
#define CW  1   // clockwise
#define CCW 0   // counter-clockwise

  // 왼쪽, 오른쪽 바퀴  
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

 // 모터속도
#define DEFAULT_POWER 150

 // 아두이노 PIN 설정
const byte PWMA = 3;      // PWM control (speed) for motor A
const byte PWMB = 11;     // PWM control (speed) for motor B
const byte DIRA = 12;     // Direction control for motor A
const byte DIRB = 13;     // Direction control for motor B

void setup()
{
  // initialization
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
 
void loop()
{
  
  digitalWrite(DIRB, CW); //왼쪽모터, 시계방향
  analogWrite(PWMB,  DEFAULT_POWER); //왼쪽모터의 스피드를 DEFAULT_POWER로 설정

  delay(5000); //5초
 
  digitalWrite(DIRB, CW);
  analogWrite(PWMB, 0); //스피드를 0으로 설정->멈춤
   
   delay(1000); //1초
   
  digitalWrite(DIRB, CCW); //왼쪽모터, 반시계방향
  analogWrite(PWMB,  DEFAULT_POWER); //왼쪽모터의 스피드를 DEFAULT_POWER로 설정
  
  delay(5000); //5초 
 
  digitalWrite(DIRB, CW);
  analogWrite(PWMB, 0); //스피드를 0으로 설정->멈춤

   delay(1000);   
}

  
