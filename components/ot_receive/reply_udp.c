#include "ot_receive.h"

otUdpSocket *udpCreateSocket(otInstance *aInstance, otSockAddr *aSockName) {
  otUdpSocket *aSocket = calloc(1, sizeof(otUdpSocket));
  handleError(otUdpOpen(aInstance, aSocket, NULL, NULL));

  handleError(otUdpBind(aInstance, aSocket, aSockName, OT_NETIF_THREAD));
  return aSocket;
}

void udpAttachReply(otMessage *aMessage, void* buffer, uint16_t length) {
  otError error = otMessageAppend(aMessage, buffer, length);
  handleMessageError(aMessage, error);
  return;
}

void udpSendReply(otInstance *aInstance,
             uint16_t port,
             uint16_t destPort,
             otUdpSocket *aSocket,
             otMessageInfo *aMessageInfo,
             void* payload,
             uint16_t payloadLength)
{
  otMessage *aMessage = otUdpNewMessage(aInstance, NULL);
  udpAttachReply(aMessage, payload, payloadLength);

  otError error = otUdpSend(aInstance, aSocket, aMessage, aMessageInfo);
  handleMessageError(aMessage, error);
  return;
}

void udpReply(otInstance *aInstance,
              uint16_t port,
              uint16_t destPort,
              void* payload,
              uint16_t payloadLength) 
{
  checkConnection(aInstance);

  otSockAddr aSockName;
  aSockName.mAddress = *otThreadGetMeshLocalEid(aInstance);
  aSockName.mPort = port;
  otUdpSocket *aSocket = udpCreateSocket(aInstance, &aSockName);

  otMessageInfo aMessageInfo;
  aMessageInfo.mSockAddr = *otThreadGetMeshLocalEid(aInstance);
  aMessageInfo.mSockPort = port;
  aMessageInfo.mPeerPort = destPort;
  aMessageInfo.mLinkInfo = NULL;
  aMessageInfo.mHopLimit = 0;  // default
  otIp6Address *peerAddr = &(aMessageInfo.mPeerAddr);
  handleError(otIp6AddressFromString(MLEID_MULTICAST, peerAddr));

  udpSendReply(aInstance, port, destPort,
               aSocket, &aMessageInfo, payload,
               payloadLength);
  return;
}