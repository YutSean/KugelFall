#include <Servo.h>
#include "calculator.h"
#include "triggerManager.h"

#define TRIGGER_PIN 4
#define HALLSENSOR 3
#define PHOTOSENSOR 2
#define SERVO_OUTPUT 9

int pCount;
int kreisCount;
Servo myServo;

bool dropped;

calculator cal;
triggerManager tm(TRIGGER_PIN);

//drive servo motor to release the ball
void driveServo() {

   for (int pos = 0; pos <= 45; pos++) {
      myServo.write(pos);
      delay(3);
   }

   for (int pos = 45; pos >= 0; pos--) {
      myServo.write(pos);
   }
}

//every half round calculate once the angle speed
void phoCount() {
  pCount = (pCount + 1) % 7;
  cal.setSectorTime();
  switch (pCount) {
    case 0:
      cal.startTime();
      break;
    case 6:
      cal.endTime();
      cal.angleSpeed();
      break;
  }
  cal.addSector();
}

void hallFalling() {
  //when the value of hall sensor falls run this function
  //every 2 runds calculate once the accelerate speed
  kreisCount ++;
  if (kreisCount == 2 ) {
    cal.setBeschleunigung();
    cal.setAltSpeed();                                     //update the speed
    kreisCount = 0;
  }
  
  cal.resetSector();                                       //reset the counter for sector(inter sector bias)
}

void initial() {

  pinMode(HALLSENSOR,INPUT);
  pinMode(PHOTOSENSOR,INPUT);
  pinMode(TRIGGER_PIN,INPUT);

  attachInterrupt(digitalPinToInterrupt(PHOTOSENSOR), phoCount, CHANGE);
  attachInterrupt(digitalPinToInterrupt(HALLSENSOR), hallFalling, FALLING);

  tm = triggerManager(TRIGGER_PIN);
  cal = calculator();
  pCount = 0;
  kreisCount = 0;

  myServo.attach(SERVO_OUTPUT);
  myServo.write(0);
  Serial.begin(9600);
}

void setup() {
  initial();
}


void loop() {
    //listen the signal from trigger
    for (int i = tm.sendSignal(); i > 0; i--) {
      int t1 = cal.predict();
      delay(cal.predict());
      driveServo();
      delay(200);                               //wait the time, in which the Servo motor reset itself
    }
}
