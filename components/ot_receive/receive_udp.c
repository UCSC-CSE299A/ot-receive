#include "ot_receive.h"
#include <string.h>
#include <assert.h>

/**
 * Empties all memory for `size` bytes starting at memory address `pointer`.
 *
 * @param[in] pointer: the pointer of the stack memory
 * @param[in] size:    the size of the memory that `pointer` points to
 *
 * I got the idea to use `memset()` to clear stack memory from
 * the Google Search AI:
 * https://docs.google.com/document/d/1o-NaEOA-vzWPCv7VX1dONUfwos2epveDk4H_Y2Y5g1Y/edit?usp=sharing
*/
static inline void emptyMemory(void* pointer, size_t size) {
  memset(pointer, 0, size);
  return;
}

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
void udpGetPayload(const otMessage *aMessage, void* buffer) {
  uint16_t offset = otMessageGetOffset(aMessage);
  uint16_t length = getPayloadLength(aMessage);

  uint16_t bytesRead = otMessageRead(aMessage, offset, buffer, length);
  assert(bytesRead == length);
  return;
}

/**
 * Only handle messages sent by the `ot-send` UDP sender.
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
    char payload[PAYLOAD_SIZE];
    char output[OUTPUT_STRING_SIZE];

    emptyMemory(payload, PAYLOAD_SIZE);
    emptyMemory(output, OUTPUT_STRING_SIZE);

    udpGetPayload((const otMessage *) aMessage, payload);
    sprintf(output, "Received %s", payload);
    otLogNotePlat(output);

    return true;
  }

  return false;
}

void udpInitReceiver(otUdpReceiver *receiver) {
  receiver->mContext = NULL;
  receiver->mHandler = NULL;
  receiver->mNext = NULL;
  return;
}

void udpCreateReceiver(otInstance *aInstance, otUdpReceiver *receiver) {
  receiver->mHandler = udpReceiveCallback;
  handleError(otUdpAddReceiver(aInstance, receiver));
  return;
}