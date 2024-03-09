#include "ot_receive.h"

void udpCreateSocket(otUdpSocket *aSocket,
                     otInstance *aInstance,
                     otSockAddr *aSockName)
{
  handleError(otUdpOpen(aInstance, aSocket, NULL, NULL));
  handleError(otUdpBind(aInstance, aSocket, aSockName, OT_NETIF_THREAD));
  return;
}

void createReceiverSocket(otInstance *aInstance,
                          uint16_t port,
                          otSockAddr *aSockName,
                          otUdpSocket *aSocket)
{
  checkConnection(aInstance);

  aSockName->mAddress = *otThreadGetMeshLocalEid(aInstance);
  aSockName->mPort = port;

  udpCreateSocket(aSocket, aInstance, aSockName);
  return;
}