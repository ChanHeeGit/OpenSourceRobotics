
// 회전 방향
#define CW  1   // clockwise
#define CCW 0   // counter-clockwise

// 왼쪽, 오른쪽 바퀴
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

// motor POWER setting
#define DEFAULT_POWER 150

// 아두이노 PIN 설정
const byte PWMA = 3;      // PWM control (speed) for motor A
const byte PWMB = 11;     // PWM control (speed) for motor B
const byte DIRA = 12;     // Direction control for motor A
const byte DIRB = 13;     // Direction control for motor B

void setup()
{
  // 핀 초기화
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);

  Serial.begin(9600);
  Serial.println("왼쪽바퀴 : 1, 오른쪽바퀴 : 0");
  Serial.println("시계방향 : 1, 반시계방향 : 0");
}

void loop()
{
  driveArdumoto(); //밑에서 만든 함수 실행
}


void driveArdumoto() {
  int motor = 0; // 왼쪽 모터, 오른쪽 모터 설정
  int dir = 0; // 시계방향, 반시계방향 설정
  Serial.print("input motor :"); // 처음에 왼쪽, 오른쪽 모터를 설정함
  while (Serial.available() == 0) {}
  motor = Serial.parseInt(); // 입력받은 motor값을 int로 변환
  Serial.println(motor); //확인을 위해 출력

  if (motor == 1) { // motor가 1이면 왼쪽바퀴이다.
    Serial.println("왼쪽바퀴");
    Serial.print("input direction :"); // 왼쪽바퀴일때 시계인지, 반시계인지 고를 수 있다.
    while (Serial.available() == 0) {}
    dir = Serial.parseInt(); // 입력받은 dir도 int로 변환
    Serial.println(dir);
    if (dir == 1) { // 시계방향일때
      Serial.println("시계방향");
      digitalWrite(DIRB, CW);
      analogWrite(PWMB,  DEFAULT_POWER);
      delay(5000);
      digitalWrite(DIRB, CW);
      analogWrite(PWMB, 0);
    }
    else if (dir == 0) { //반시계방향일떄
      Serial.println("반시계방향");
      digitalWrite(DIRB, CCW);
      analogWrite(PWMB,  DEFAULT_POWER);
      delay(5000);
      digitalWrite(DIRB, CCW);
      analogWrite(PWMB, 0);
    }
  }

  if ( motor == 0) { //motor가 0이면 오른쪽바퀴
    Serial.println("오른쪽바퀴");
    Serial.print("input direction :");
    while (Serial.available() == 0) {}
    dir = Serial.parseInt();
    Serial.println(dir);
    if (dir == 1) { //시계방향일때
      Serial.println("시계방향");
      digitalWrite(DIRA, CW);
      analogWrite(PWMA,  DEFAULT_POWER);
      delay(5000);
      digitalWrite(DIRA, CW);
      analogWrite(PWMA, 0);
    }
    else if (dir == 0) { //반시계방향일때
      Serial.println("반시계방향");
      digitalWrite(DIRA, CCW);
      analogWrite(PWMA,  DEFAULT_POWER);
      delay(5000);
      digitalWrite(DIRA, CCW);
      analogWrite(PWMA, 0);
    }
  }
}
