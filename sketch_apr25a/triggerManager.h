#include "Arduino.h"
class triggerManager {
  public:
  triggerManager(int trigger_pin);
  int sendSignal();

  private:
    int tp;
    bool getTriggerVal();
    bool dropped;
};
