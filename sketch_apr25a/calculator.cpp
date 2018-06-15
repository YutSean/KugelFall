#include "calculator.h"
#define FALL_ZEIT 400


calculator::calculator() {
    aSpeed = 0;
    beschleunigung = 0;
    latency = 85;
}

void calculator::startTime() {
    sTime = millis();
}

void calculator::endTime() {
    eTime = millis();
}

//this function calculate the angle speed of the scheibe
void calculator::angleSpeed() {
        
        double t = eTime - sTime;
        altSpeed = aSpeed;
        //eigenheit round per milisecond
        aSpeed = 0.5 / t;

}

//this function return the length of the wait time for servo motor
int calculator::predict() {
    //evaluate the average speed of the scheibe in the kugel fall time
    double avgSpeed = (aSpeed + (FALL_ZEIT * beschleunigung + aSpeed)) / 2.0;

    double distance = avgSpeed * FALL_ZEIT;
    int numR = floor(avgSpeed * FALL_ZEIT);
    numR++;
    //intra sector bias
    double sectorAbw = (millis() - bTime) * avgSpeed;
    double temp = (12 - sectorCount) / 12.0 - sectorAbw;
    
    double mittel = numR + temp;
    int t = floor((mittel / avgSpeed) - FALL_ZEIT);
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
  beschleunigung = (aSpeed - altSpeed) / (millis() - aTime); 
}

//update the early speed for the next time to calculate the accelerated speed
void calculator::setAltSpeed() {

  this->altSpeed = aSpeed;
  this->aTime = millis();
}

void calculator::setLatency(int t) {
  latency = t;
}

