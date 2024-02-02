idf_component_register(SRCS "connect.c" "receive_udp.c" "init.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES "esp_event" "esp_netif" "esp_ot_cli_extension"
                    REQUIRES "openthread" "nvs_flash")
