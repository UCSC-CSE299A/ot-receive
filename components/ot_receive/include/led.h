/**
 * All the code is the file comes from Espressif's ESP Blink example:
 * https://github.com/espressif/esp-idf/tree/master/examples/get-started/blink
*/
#ifndef LED
#define LED

#include "freertos/FreeRTOS.h"
#include "led_strip.h"

#define BLINK_GPIO 8 // default GPIO used in the ESP Blink example
#define BLINK_PERIOD 500

typedef struct led {
  char* tag;
  uint8_t s_led_state;
  led_strip_handle_t led_strip;
} Led;

typedef struct Led led;

Led* blink_led(Led*);
Led* configure_led(Led*);

#endif