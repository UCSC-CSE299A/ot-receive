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

otUdpSocket *udpCreateSocket(otInstance *aInstance,
                             uint16_t port,
                             otSockAddr *aSockName) {
  otUdpSocket *aSocket = calloc(1, sizeof(otUdpSocket));
  handleError(otUdpOpen(aInstance, aSocket, NULL, NULL));

  handleError(otUdpBind(aInstance, aSocket, aSockName, OT_NETIF_THREAD));
  return aSocket;
}