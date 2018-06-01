#include "calculator.h"
#define FALL_ZEIT 404


calculator::calculator() {
    aSpeed = 0;
    beschleunigung = 0;
    latency = 112;
}

void calculator::startTime() {
    sTime = millis();
    //Serial.print("Stime:");
    //Serial.println(sTime);
}

void calculator::endTime() {
    eTime = millis();
   // Serial.print("Etime:");
    //Serial.println(eTime);
}

void calculator::angleSpeed() {
    
        double t = (eTime - sTime)/1000.00;
        //Serial.println(t);
        altSpeed = aSpeed;
        aSpeed = 0.5 / t;
                    //Serial.println("Speed");

        //Serial.println(beschleunigung);
       // Serial.println(beschleunigung);
        //Serial.println(beschleunigung);
        Serial.println(altSpeed);
//        Serial.println(beschleunigung);
}

int calculator::predict() {
    //Serial.println(millis());
    double avgSpeed = (aSpeed + (FALL_ZEIT / 1000.000 * beschleunigung + aSpeed)) / 2.0;
    
    int numR = floor((avgSpeed * (FALL_ZEIT / 1000.000)));
    numR++;
    
//    double abstand = distance - (int)distance;
//    Serial.println(abstand);
//    int t = ((abstand / avgSpeed) * 1000);
//    //Serial.println(t);
//    if (pos) {
//      t += 0.5 / avgSpeed;
//    }
    double sectorAbw = ((millis() - bTime) / 1000.000) * avgSpeed;
    //Serial.println(sectorAbw);
    double temp = (12 - sectorCount + 1) / 12.0 - sectorAbw;
    double mittel = numR + temp;
    int t = floor((((mittel / avgSpeed) - (FALL_ZEIT / 1000.000)) * 1000));
    //Serial.println(millis());
    return t - latency;  
}

double calculator::getSpeed() {
  return this->aSpeed;
}

void calculator::addSector() {
  this->sectorCount++;
}

void calculator::resetSector() {
  this->sectorCount = 0;
}

void calculator::setSectorTime() {
  this->bTime = millis();
}

void calculator::setBeschleunigung() {
  
  beschleunigung = (aSpeed - altSpeed) / ((millis() - aTime) / 1000.0);
  
}

void calculator::setAltSpeed() {
  this->altSpeed = aSpeed;
  this->aTime = millis();
}

void calculator::setLatency(int t) {
  this->latency = t;
}

