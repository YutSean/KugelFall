#include "Arduino.h"
#include "math.h"

class calculator {
  public:
    calculator();
    void  startTime();         //save the left bound of the time interval to calculate the angle speed
    void  endTime();           //save the right bound of the time interval to calculate the angle speed
    void angleSpeed();         //calculate the angle speed with units rpms
    int predict();             //this function return the length of the wait time for servo motor
    double getSpeed();         //return the angle speed
    void addSector();          //inter sector bias +1
    void resetSector();        //reset the inter sector bias to 0
    void setSectorTime();      //record the time point to calculate the intra sector bias
    void setBeschleunigung();  //update the accelerate
    void setAltSpeed();        //update the old speed for calculating the accelerate
    void setLatency(int t);    //set the system latency
    

  private:
    int sectorCount;           //inter sector bias
    unsigned long aTime;       //a time point to calculate the accelerate
    double altSpeed;           //the last time update the old speed, that is used to calculate the accelerate
    unsigned long bTime;       //a time point to calculate the intra sector bias
    unsigned long sTime;       //left time bound for angle speed
    unsigned long eTime;       //right time bound for anlge speed
    double aSpeed;             //real-time angle speed
    double beschleunigung;     //variable to save the up to date accelerate
    
    int latency;
};
