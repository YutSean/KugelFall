#include "calculator.h"
#define FALL_ZEIT 400


calculator::calculator(int l) {
    aSpeed = 0;
    beschleunigung = 0;
    latency = l;
}

void calculator::startTime() {
    sTime = millis();
}

void calculator::endTime() {
    eTime = millis();
}

//this function calculate the angle speed of the scheibe
void calculator::angleSpeed() {
        
        double t = (eTime - sTime) / 1000.0;
        //eigenheit round per second
        aSpeed = 0.5 / t;

}

//this function return the length of the wait time for servo motor
int calculator::predict() {
    //evaluate the average speed of the scheibe in the kugel fall time
    double avgSpeed = (aSpeed + (FALL_ZEIT / 1000.0 * beschleunigung + aSpeed)) / 2.0;

    double distance = avgSpeed * FALL_ZEIT / 1000.0;
    int numR = floor(avgSpeed * FALL_ZEIT / 1000.0);
    numR++;
    //intra sector bias
    double sectorAbw = (millis() - bTime) / 1000.0 * avgSpeed;
    double temp = (12 - sectorCount) / 12.0 - sectorAbw;
    
    double mittel = numR + temp;
    int t = floor((mittel / avgSpeed) * 1000.0) - FALL_ZEIT;
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

//calculate the accelerated speed
void calculator::setBeschleunigung() {
  beschleunigung = (aSpeed - altSpeed) / ((millis() - aTime) / 1000.0); 
  Serial.println(aSpeed);
  
}

//update the early speed for the next time to calculate the accelerated speed
void calculator::setAltSpeed() {
  
  altSpeed = aSpeed;
  aTime = millis();
  
}

void calculator::setLatency(int t) {
  latency = t;
}

