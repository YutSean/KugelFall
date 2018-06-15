#include "triggerManager.h"

triggerManager::triggerManager(int trigger_pin) {
    this->tp = trigger_pin;
    dropped = false;
}

//if just one click return 1, double click return 5, else return 0
int triggerManager::sendSignal() {
    if (getTriggerVal() && !dropped) {
      double start = (double) millis();
      while (true){
        if (getTriggerVal() == false){
          break;
        }
      }

      //time for human reflection
      delay(200);
      while(millis() - start < 300) {
        if (getTriggerVal()) {
          
          this->dropped = true;
          start = 0;
          return 5;
        }
      }
        this->dropped = true;
        return 1;
    } else if (dropped && !getTriggerVal()) {
        this->dropped = false;
    }
    return 0;
}

//read the value of trigger
bool triggerManager::getTriggerVal() {
    return digitalRead(tp);
}
