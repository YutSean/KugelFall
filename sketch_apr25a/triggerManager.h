#include "Arduino.h"
class triggerManager {
  public:
  triggerManager(int trigger_pin);
  bool sendSignal();

  private:
    int tp;
  bool getTriggerVal();
  bool dropped;
  
};

