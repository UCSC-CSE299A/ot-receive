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
#define EmptyMemory(pointer, size) memset((void *) pointer, 0, size)

#define MS_TO_TICKS(ms) ms / portTICK_PERIOD_MS
#define DEFAULT_WAIT_TIME MS_TO_TICKS(100)
#define MAIN_WAIT_TIME MS_TO_TICKS(5000) // 5 seconds

#define OT_DISCONNECTED(role) (role == OT_DEVICE_ROLE_DISABLED) || (role == OT_DEVICE_ROLE_DETACHED)

/**
 * Each send packet will have the following payload:
 * 
 *    "Packet Number [uint_32t]"
 *
 * Substring "Packet Number " makes up 14 bytes.
 *
 * The 32 bit integer will be represented as a string.
 * 2^32 - 1 = 4294967295 has 10 digits, and thus, the
 * string representation of the uint32_t will make up 10 bytes.
 *
 * Thus, the total payload isze is 14 + 10 = 24 bytes.
*/
#define PAYLOAD_SIZE 24

#define OUTPUT_STRING_SIZE strlen("Received ") + PAYLOAD_SIZE

#define UDP_SOCK_PORT 54321
#define UDP_DEST_PORT 12345

otError handleError(otError error);
void handleMessageError(otMessage *aMessage, otError error);

void ot_task_worker(void *aContext);

void checkConnection(otInstance *aInstance);
void setTxPower();

void udpInitReceiver(otUdpReceiver *receiver);

void udpCreateReceiver(otInstance *aInstance, otUdpReceiver *receiver);

void createReceiverSocket(otInstance *aInstance,
                          uint16_t port,
                          otSockAddr *aSockName,
                          otUdpSocket *aSocket);

#define DEBUG true
#define DELIMITER "************************************"
#define PRINT_DELIMIER otLogNotePlat(DELIMITER)
#define DEBUG_PRINT(ot_note) PRINT_DELIMIER; ot_note; PRINT_DELIMIER;
#define ERROR_PRINT(ot_error) otLogCritPlat(DELIMITER); ot_error; otLogCritPlat(DELIMITER);

#endif // OT_RECEIVE_
