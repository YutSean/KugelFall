#include "Arduino.h"
#include "math.h"

class calculator {
  public:
    calculator();
    void  startTime();
    void  endTime();
    void angleSpeed();
    int predict();
    double getSpeed();
    void addSector();
    void resetSector();
    void setSectorTime();
    void setBeschleunigung();
    void setAltSpeed();
    void setLatency(int t);

  private:
    int aTime;
    double altSpeed;
    int bTime;
    bool pos;
    int sTime;
    int eTime;
    double aSpeed;
    double beschleunigung;
    int sectorCount;
    int latency;
};
