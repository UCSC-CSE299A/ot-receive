#ifndef OT_RECEIVE_
#define OT_RECEIVE_

#include "esp_ot_config.h"
#include <openthread/logging.h>

#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_netif_types.h"
#include "esp_openthread.h"
#include "esp_openthread_cli.h"
#include "esp_openthread_lock.h"
#include "esp_openthread_netif_glue.h"
#include "esp_openthread_types.h"
#include "esp_vfs_eventfd.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/uart_types.h"
#include "nvs_flash.h"
#include "openthread/cli.h"
#include "openthread/instance.h"
#include "openthread/logging.h"
#include "openthread/tasklet.h"
#include "openthread/udp.h"

#define DEBUG true
#define DELIMITER "************************************"
#define PRINT_DELIMIER otLogNotePlat(DELIMITER)
#define DEBUG_PRINT(ot_note) PRINT_DELIMIER; ot_note; PRINT_DELIMIER;
#define ERROR_PRINT(ot_error) otLogCritPlat(DELIMITER); ot_error; otLogCritPlat(DELIMITER);

#define MS_TO_TICKS(ms) ms / portTICK_PERIOD_MS
#define DEFAULT_WAIT_TIME MS_TO_TICKS(100)
#define PACKET_SEND_DELAY MS_TO_TICKS(5000) // 5 seconds

#define OT_DISCONNECTED(role) (role == OT_DEVICE_ROLE_DISABLED) || (role == OT_DEVICE_ROLE_DETACHED)

/**
 * https://openthread.io/guides/thread-primer/ipv6-addressing#multicast
*/
#define MLEID_MULTICAST "ff03::1"

#define UDP_SOCK_PORT 12345
#define UDP_DEST_PORT 12345

otError handleError(otError error);
void handleMessageError(otMessage *aMessage, otError error);

void ot_task_worker(void *aContext);

void checkConnection(otInstance *aInstance);

void udpCreateReceiver(otInstance *aInstance);

#endif // OT_RECEIVE_
