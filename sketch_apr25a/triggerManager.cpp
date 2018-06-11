#include "triggerManager.h"

triggerManager::triggerManager(int trigger_pin) {
    this->tp = trigger_pin;
    dropped = false;
}

int triggerManager::sendSignal() {
  //Serial.println(dropped);
    if (getTriggerVal() && !dropped) {
      //int start = millis();
      double start = (double) millis();
      while (true){
        if (getTriggerVal() == false){
          //Serial.println(123123);
          break;
        }
      }

      delay(200);
      //Serial.println(millis()-start);
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
        //delay(5);
    }
    return 0;
}

bool triggerManager::getTriggerVal() {
    return digitalRead(tp);
}
