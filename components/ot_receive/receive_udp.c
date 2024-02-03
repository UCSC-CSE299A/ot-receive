#include "ot_receive.h"
#include <string.h>

void* udpGetPayload(const otMessage *aMessage) {
  uint16_t offset = otMessageGetOffset(aMessage) - UDP_PAYLOAD_SIZE;
  void* buffer = calloc(1, UDP_PAYLOAD_SIZE);
  uint16_t bytesRead = otMessageRead(aMessage, offset, buffer, UDP_PAYLOAD_SIZE);

  DEBUG_PRINT(otLogNotePlat("Bytes read: %d", (int) bytesRead));
  return buffer;
}

/**
 * Only handle messages sent by the `ot-send` UDP sender, which broadcast
 * packets at MLEID_MULTICAST with port 12345.
*/
bool udpReceiveCallback(void *aContext,
                        const otMessage *aMessage,
                        const otMessageInfo *aMessageInfo)
{
  uint16_t peerPort = aMessageInfo->mPeerPort;
  uint16_t sockPort = aMessageInfo->mSockPort;

  if ((peerPort == UDP_DEST_PORT) && (sockPort == UDP_SOCK_PORT)) {
    char* payload = (char *) udpGetPayload((const otMessage *) aMessage);

    otLogNotePlat("--------------------");
    for (char c = 0; c < otMessageGetOffset(aMessage); c++) {
      otLogNotePlat("%c", payload[c]);
    }
    otLogNotePlat("--------------------");

    // DEBUG_PRINT(otLogNotePlat("%x", payload));
    free(payload);
    return true;
  }
  return false;
}

void udpCreateReceiver(otInstance *aInstance) {
  otUdpReceiver* receiver = calloc(1, sizeof(otUdpReceiver));
  receiver->mHandler = udpReceiveCallback;
  handleError(otUdpAddReceiver(aInstance, receiver));
}