#include "triggerManager.h"

triggerManager::triggerManager(int trigger_pin) {
    this->tp = trigger_pin;
    dropped = false;
}

bool triggerManager::sendSignal() {
  //Serial.println(dropped);
    if (getTriggerVal() && !dropped) {
        this->dropped = true;
        return true;
    } else if (dropped && !getTriggerVal()) {
        this->dropped = false;
        //delay(5);
    }
    return false;
}

bool triggerManager::getTriggerVal() {
    return digitalRead(tp);
}

