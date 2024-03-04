/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * OpenThread Command Line Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
*/

#include "ot_receive.h"

inline otInstance* getInstance() {
  return esp_openthread_get_instance();
};

void app_main(void)
{
    // Used eventfds:
    // * netif
    // * ot task queue
    // * radio driver
    esp_vfs_eventfd_config_t eventfd_config = {
        .max_fds = 3,
    };

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_vfs_eventfd_register(&eventfd_config));

    xTaskCreate(ot_task_worker, "ot_cli_main", 10240,
                xTaskGetCurrentTaskHandle(), 5, NULL);

    otSockAddr aSockName;
    otUdpSocket aSocket;
    createReceiverSocket(getInstance(), UDP_SOCK_PORT, &aSockName, &aSocket);

    otUdpReceiver receiver;
    udpInitReceiver(&receiver);
    udpCreateReceiver(getInstance(), &receiver);

    // Keep "main" thread running on an infite loop,
    // so the OpenThread worker thread will always be able
    // to access the memory addresses of `aSocket` and `aSockName`.
    //
    while (true) {
      vTaskDelay(MAIN_WAIT_TIME);
    }
    return;
}