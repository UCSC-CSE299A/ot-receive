#include "ot_receive.h"
#include <string.h>

/**
 * Based upon the OpenThread CLI UDP Handler code.
 * https://github.com/openthread/openthread/blob/main/src/cli/cli_udp.cpp#L461
 *
 * According to the handler code, `otMessageGetOffset()` returns the end
 * of the Message header, while `otMessageGetLength()` returns the size
 * of the Message header, payload included.
*/
void* udpGetPayload(const otMessage *aMessage) {
  uint16_t offset = otMessageGetOffset(aMessage);
  uint16_t length = otMessageGetLength(aMessage) - offset;

  void* buffer = calloc(1, length);
  uint16_t bytesRead = otMessageRead(aMessage, offset, buffer, length);
  if (bytesRead != length) {
    ERROR_PRINT(otLogCritPlat ("Read %d bytes but expected %d bytes.",
      bytesRead, length));
  }

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
    otLogNotePlat(payload);
    free(payload);
    return true;
  }
  return false;
}

void udpCreateReceiver(otInstance *aInstance) {
  otUdpReceiver* receiver = calloc(1, sizeof(otUdpReceiver));
  receiver->mHandler = udpReceiveCallback;
  handleError(otUdpAddReceiver(aInstance, receiver));
  return;
}