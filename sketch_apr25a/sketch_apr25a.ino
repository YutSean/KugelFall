#include <Servo.h>
#include "calculator.h"
#include "triggerManager.h"

#define TRIGGER_PIN 4
#define HALLSENSOR 3
#define PHOTOSENSOR 2
#define SERVO_OUTPUT 9

int pCount;
int kreisCount;
int lastTime;
Servo myServo;

bool dropped;

calculator cal;
triggerManager tm(TRIGGER_PIN);

bool getTriggerSignal() {
  return digitalRead(TRIGGER_PIN);
}

void driveServo() {

   for (int pos = 0; pos <= 33; pos++) {
      myServo.write(pos);
      //Serial.println(pos);
      delay(3);
   }

   for (int pos = 33; pos >= 0; pos--) {
      myServo.write(pos);
      //Serial.println(pos);
   }
}

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

void halFalling() {
  //pos = false;
  //cal.setBesch();
  Serial.println(kreisCount);
  kreisCount ++;
  if (kreisCount == 2) {
    cal.setBeschleunigung();
    cal.setAltSpeed();
    kreisCount = 0;
  }
  //cal.setLatency(i);
  cal.resetSector();
}

//void halRising() {
//  pos = true;
//  cal.resetSector();
//}

void initial() {

  pinMode(HALLSENSOR,INPUT);
  pinMode(PHOTOSENSOR,INPUT);
  pinMode(TRIGGER_PIN,INPUT);

  attachInterrupt(digitalPinToInterrupt(PHOTOSENSOR), phoCount, CHANGE);
  attachInterrupt(digitalPinToInterrupt(HALLSENSOR), halFalling, FALLING);
  //attachInterrupt(digitalPinToInterrupt(HALLSENSOR), halRising, RISING);

  tm = triggerManager(TRIGGER_PIN);
  cal = calculator();
  pCount = 0;
  kreisCount = 0;
  lastTime = 0;
  //pos = false;

  myServo.attach(SERVO_OUTPUT);
  myServo.write(0);
  Serial.begin(9600);
}


//double getTime(bool val) {
//  int startTime = millis();
//  int endTime = 0;
//  if (!val) {
//    while (true) {
//      if (digitalRead(PHOTOSENSOR)) {
//        endTime = millis();
//        break;
//      }
//    }
//  } else {
//    int startTime = millis();
//    int endTime = 0;
//    while (true) {
//      if (!digitalRead(PHOTOSENSOR)) {
//        endTime = millis();
//        break;
//      }
//    }
//  }
//
//  return ((endTime - startTime) / 1000.0);
//}

double getBeschleunigung() {

}
void setup() {
  initial();

}


void loop() {
  //Serial.println(tm.sendSignal());
  //Serial.println(cal.sectorCount);
  //Serial.println(tm.sendSignal());
  //Serial.println(lastTime);
//  Serial.println(tm.sendSignal());
//  if (tm.sendSignal()) {
//    Serial.println(tm.sendSignal());
    for (int i = tm.sendSignal(); i > 0; i--) {
      delay(cal.predict());
      driveServo();
      cal.setLatency(112);
      delay(80);
    }
    cal.setLatency(56);
     //Serial.println(1);
//    if (checkClick()) {
//      Serial.println(2);
//    }
//    if (false) {
//      //Serial.println(lastTime);
//      
//      for (int i = 0; i < 4; i++) {
//        delay(cal.predict());
//        driveServo();
//      }
//    }
    //Serial.println(predictTime);
    //double Aspeed = cal.getSpeed();
    //int temp = cal.predict();
    //Serial.println(temp);
   // delay(cal.predict());
   // lastTime = millis();
    //Serial.println(predictTime);
    //Serial.println(Aspeed);
    //Serial.println(millis());
//    driveServo();
    //Serial.println(millis());
    //Serial.println(millis());
  //Serial.println(t);

// int hallVal = digitalRead(HALLSENSOR);
// int photoVal = digitalRead(PHOTOSENSOR);
// Serial.print("Time: ");
//  double time = millis();
//
//   Serial.println(time/1000.0);
//Serial.print(hallVal);
//Serial.print(",");
//Serial.println(photoVal - 1);
//delay(50);




}
