#include "Arduino.h"
class triggerManager {
  public:
  triggerManager(int trigger_pin);
  int sendSignal();          //if just one click return 1, double click return 5, else return 0

  private:
    int tp;                  //pin nummer of trigger
    bool getTriggerVal();    //read the value of the trigger
    bool dropped;            //a flag to mark wether the ball has falled
};
