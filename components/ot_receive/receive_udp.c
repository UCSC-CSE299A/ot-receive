#include "ot_receive.h"
#include "led.h"
#include <string.h>
#include <assert.h>

static inline uint16_t getPayloadLength(const otMessage *aMessage) {
  return otMessageGetLength(aMessage) - otMessageGetOffset(aMessage);
}

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
  uint16_t length = getPayloadLength(aMessage);

  void* buffer = calloc(1, length);
  uint16_t bytesRead = otMessageRead(aMessage, offset, buffer, length);
  assert(bytesRead == length);
  return buffer;
}

/**
 * Only handle messages sent by the `ot-send` UDP sender, which broadcast
 * packets at MLEID_MULTICAST with port 12345.
 *
 * Based on observation, the PEER IP and port corresponds to the sender,
 * while the SOCKET IP and port corresponds to the receiver.
*/
bool udpReceiveCallback(void *aContext,
                        const otMessage *aMessage,
                        const otMessageInfo *aMessageInfo)
{
  uint16_t senderPort = aMessageInfo->mPeerPort;
  uint16_t receiverPort = aMessageInfo->mSockPort;

  if ((senderPort == UDP_DEST_PORT) && (receiverPort == UDP_SOCK_PORT)) {
    setLed(ON);

    char* payload = (char *) udpGetPayload((const otMessage *) aMessage);
    char *output = calloc(1, OUTPUT_STRING_SIZE);

    sprintf(output, "Received %s", payload);
    otLogNotePlat(output);

    free(output);
    free(payload);

    vTaskDelay(RECEIVE_WAIT_TIME);
    setLed(OFF);
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