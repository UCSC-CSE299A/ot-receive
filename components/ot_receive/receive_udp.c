#include "ot_receive.h"
#include <string.h>

void udpGetPayload(const otMessage *aMessage, char *buffer) {
  uint16_t payloadStart = otMessageGetOffset(aMessage) - UDP_PAYLOAD_SIZE;
  otMessageRead(aMessage, payloadStart, buffer, UDP_PAYLOAD_SIZE);
  return;
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
    char* payload = calloc(1, UDP_PAYLOAD_SIZE);
    udpGetPayload((const otMessage *) aMessage, payload);

    DEBUG_PRINT(otLogNotePlat("Recevied UDP Packet: \"%s\"", payload));
    return true;
  }
  return false;
}

void udpCreateReceiver(otInstance *aInstance) {
  otUdpReceiver* receiver = calloc(1, sizeof(otUdpReceiver));
  receiver->mHandler = udpReceiveCallback;
  handleError(otUdpAddReceiver(aInstance, receiver));
}