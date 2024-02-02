#include "ot_receive.h"
#include <openthread/thread.h>

void checkConnection(otInstance *aInstance) {
  otDeviceRole currentRole;
  do {
    currentRole = otThreadGetDeviceRole(aInstance);
    vTaskDelay(DEFAULT_WAIT_TIME);
  }
  while(OT_DISCONNECTED(currentRole));

  otLogNotePlat("OpenThread Connection has been established.");
  return;
}

otError handleError(otError error) {
  if (error != OT_ERROR_NONE) {
    ERROR_PRINT(otLogCritPlat("%s", otThreadErrorToString(error)));
  }
  return error;
}

void handleMessageError(otMessage *aMessage, otError error) {
  if (handleError(error) != OT_ERROR_NONE) {
    otMessageFree(aMessage);
  }
  return;
}