/*
 * Ultrasonic.cpp
 *
 * Library for Ultrasonic Ranging Module in a minimalist way
 *
 * created 3 Apr 2014
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 23 Jan 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 04 Mar 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 15 May 2017
 * by Eliot Lim    (github: @eliotlim)
 * modified 10 Jun 2018
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 14 Jun 2018
 * by Otacilio Maia (github: @OtacilioN | linkedIn: in/otacilio)
 *
 * Released into the MIT License.
 */

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(uint8_t trigPin, uint8_t echoPin, unsigned long timeOut) {
  //초기화 
  trig = trigPin; 
  echo = echoPin; 
  threePins = trig == echo ? true : false; //trig == echo면 threePins에 1대입, false면 0 대입
  // 핀 설정하는 부분
  pinMode(trig, OUTPUT); // 트리거는 출력으로 설정, 초음파 쏘는곳
  pinMode(echo, INPUT); // echo는 입력으로 설정, 초음파 받는곳
  timeout = timeOut;
}

unsigned int Ultrasonic::timing() { // 펄스를 만들고 계산을 하는 부분
  if (threePins)
    pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); // 초기상태는 LOW
  delayMicroseconds(2); // LOW상태로 2us 대기
  digitalWrite(trig, HIGH); // HIGH상태
  delayMicroseconds(10); // 10us만큼 신호 유지를 하고 
  digitalWrite(trig, LOW); // LOW로 변환
  //trig 가 LOW가 되면 그 이후에 echo는 초음파가 돌아올 때까지 대기하면서 그 시간을 측정한다.


  if (threePins)
    pinMode(trig, INPUT); 
  // micros() 함수는 아두이노 보드에서 스케치 프로그램을 시작하여 흐른 시간을 us(마이크로세컨드: microsecond) 단위의 숫자로 돌려 주는 기능이다.
  previousMicros = micros(); 
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // timeout은 기본적으로 1초로 설정되어 있다. 
 // !digitalRead(echo)는 echo 신호가 읽히지 않을 때, 즉 LOW를 의미함 && micros()-preciousMicros가 timeout보다 작아야 함
 // 여기서 previousMicros는 시작 시 시간을 저장해놓은 것,  while문이 끝나게 된 이후의 시간은 micros()이고 이 micros()에서 초기 시간인 previousMicros를 빼는 것
 // echo 신호가 읽히기 전에만 while문이 유지되므로 echo 신호가 read되면 밑으로 내려감
  previousMicros = micros(); // echo의 high가 read되는 순간 그 시간을 previousMicros에 저장한다.
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout -> echo는 초음파가 돌아오는 것을 기다린다.
  // previousMicros에는 echo가 read되는 시간을 저장해놓았고 이후 echo가 마지막으로 읽힐때의 시간은 while문 안의 micros()이다
  //duration은 echo가 low에서 high까지의 시간을 말하는 것

  return micros() - previousMicros; // duration 
  // 위의 while문이 종료되는 순간의 micros() 함수의 반환된 시간에서 처음에 echo가 read된 시간을 빼면 duration이 나오게 된다.
}

/*
 * If the unit of measure is not passed as a parameter,
 * sby default, it will return the distance in centimeters.
 * To change the default, replace CM by INC.
 */
unsigned int Ultrasonic::read(uint8_t und) {
  return timing() / und / 2;  //distance by divisor
  //distance는 echo pulse time/und/2이므로 timing()은 echo pulse time을 return함
}

/*
 * This method is too verbal, so, it's deprecated.
 * Use read() instead.
 */
unsigned int Ultrasonic::distanceRead(uint8_t und) {
  return read(und);
}
