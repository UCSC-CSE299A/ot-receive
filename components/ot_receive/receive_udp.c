#include "ot_receive.h"

void udpBindSocket(otUdpSocket *aSocket, otSockAddr *aSockName) {
  handleError(otUdpBind(esp_openthread_get_instance(),
                        aSocket,
                        aSockAddr,
                        OT_NETIF_THREAD));
  return;
}