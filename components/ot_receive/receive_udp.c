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

