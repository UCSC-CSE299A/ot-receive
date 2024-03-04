idf_component_register(SRCS "socket_udp.c" "receive_udp.c" "common.c" "init.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES "esp_event" "esp_netif" "esp_ot_cli_extension" "esp_driver_gpio"
                    REQUIRES "openthread" "nvs_flash")
