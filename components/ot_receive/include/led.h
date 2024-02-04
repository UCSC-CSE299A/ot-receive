/**
 * All the code is the file comes from Espressif's ESP Blink example:
 * https://github.com/espressif/esp-idf/tree/master/examples/get-started/blink
*/
#ifndef LED
#define LED

#include "freertos/FreeRTOS.h"
#include "led_strip.h"

/**
 * According to the ESP Docs, GPIO 8 controls the internal LED:
 * https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32h2/esp32-h2-devkitm-1/user_guide.html#description-of-components
*/
#define BLINK_GPIO 8
#define BLINK_PERIOD 500

typedef struct led {
  char* tag;
  uint8_t s_led_state;
  led_strip_handle_t led_strip;
} Led;

typedef struct Led led;

/**
 * Stores a reference to the built-in LED on the MCU
 * as a global variable accessible by any function in the
 * `led.h` API.
*/
extern Led* globalLed;

void initLed(void);
void blinkLed(void);
void configureLed(void);

#endif