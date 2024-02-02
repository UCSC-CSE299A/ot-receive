#include "ot_receive.h"

bool udpReceiveCallback(void *aContext,
                        const otMessage *aMessage,
                        const otMessageInfo *aMessageInfo) {
  DEBUG_PRINT(otLogNotePlat("Received UDP message"));
  return true;
}

void udpCreateReceiver(otInstance *aInstance) {
  otUdpReceiver* receiver = calloc(1, sizeof(otUdpReceiver));
  receiver->mHandler = udpReceiveCallback;
  handleError(otUdpAddReceiver(aInstance, receiver));
}

void udpReceiveInit(otInstance *aInstance, uint16_t port, uint16_t destPort) {
  checkConnection(aInstance);

  // otSockAddr aSockName;
  // aSockName.mAddress = *otThreadGetMeshLocalEid(aInstance);
  // aSockName.mPort = port;
  // otUdpSocket *aSocket = udpCreateSocket(aInstance, port, &aSockName);

  udpCreateReceiver(aInstance);
  return;
}

