#include "ot_receive.h"

/**
 * Only handle messages sent by the `ot-send` UDP sender, which broadcast
 * packets at MLEID_MULTICAST with port 12345.
*/
bool udpReceiveCallback(void *aContext,
                        const otMessage *aMessage,
                        const otMessageInfo *aMessageInfo)
{
  otIp6Address *ipPeer = &(aMessageInfo->mPeerAddr);
  char *ipPeerString = calloc(1, OT_IP6_SOCK_ADDR_STRING_SIZE);
  otIp6AddressToString(ipPeer, ipPeerString, OT_IP6_SOCK_ADDR_STRING_SIZE);

  uint16_t peerPort = aMessageInfo->mPeerPort;

  if (ipPeer == MLEID_MULTICAST) && (peerPort == UDP_DEST_PORT) {
    return true;
  }
  return false;
}

void udpCreateReceiver(otInstance *aInstance) {
  otUdpReceiver* receiver = calloc(1, sizeof(otUdpReceiver));
  receiver->mHandler = udpReceiveCallback;
  handleError(otUdpAddReceiver(aInstance, receiver));
}