gbdb
  // 회전 방향  
#define CW  1   // clockwise
#define CCW 0   // counter-clockwise

  // 왼쪽, 오른쪽 바퀴  
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

 // 모터 기본 스피드 설정
#define DEFAULT_POWER 85

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
  robotForward(); //전진
  delay(2000);
  robotBackward(); //후진
  delay(2000);
  robotRight(); //우회전
  delay(2000);
  robotLeft(); //좌회전
  delay(2000);
}

  
void setupArdumoto()
{
  //핀들 초기화
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}



void driveArdumoto(byte motor, byte dir)
{
  unsigned char spd = 150; // 모터 기본 스피드 설정
  if(motor == MOTOR_RIGHT) //오른쪽 모터이면
  {
    digitalWrite(DIRA, dir); // 오른쪽에다가 설정한 dir 적용
    analogWrite(PWMA, spd); // 오른쪽에 spd 적용
  }
  else if(motor == MOTOR_LEFT) // 왼쪽일때도 마찬가지
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}
 
void robotForward() //전진 
{
  driveArdumoto(MOTOR_LEFT, CCW); //왼쪽모터는 반시계
  driveArdumoto(MOTOR_RIGHT, CW); //오른쪽모터는 시계
}

void robotBackward() //후진
{
  driveArdumoto(MOTOR_LEFT, CW); //왼쪽모터는 시계
  driveArdumoto(MOTOR_RIGHT, CCW); //오른쪽모터는 반시계
}

void robotRight() //우회전
{
  driveArdumoto(MOTOR_LEFT, CCW); //왼쪽 반시계
  driveArdumoto(MOTOR_RIGHT, CCW); // 오른쪽 반시계
}

void robotLeft() //좌회전
{
  driveArdumoto(MOTOR_LEFT, CW); // 왼쪽 시계
  driveArdumoto(MOTOR_RIGHT, CW); //오른쪽 시계
}
