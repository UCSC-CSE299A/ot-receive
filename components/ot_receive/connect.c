#include "ot_receive.h"
#include <openthread/thread.h>

void checkConnection(otInstance *aInstance) {
  otDeviceRole currentRole;
  do {
    currentRole = otThreadGetDeviceRole(aInstance);
    vTaskDelay(DEFAULT_WAIT_TIME);
  }
  while(OT_DISCONNECTED(currentRole));

  DEBUG_PRINT(otLogNotePlat("OpenThread Connection has been established."));
  return;
}