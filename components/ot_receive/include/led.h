/**
 * All the code is the file comes from Espressif's ESP Blink example:
 * https://github.com/espressif/esp-idf/tree/master/examples/get-started/blink
*/
#ifndef LED
#define LED

#include <stdbool.h>
#include "freertos/FreeRTOS.h"

#include "led_strip.h"

/**
 * According to the ESP Docs, GPIO 8 controls the internal LED:
 * https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32h2/esp32-h2-devkitm-1/user_guide.html#description-of-components
*/
#define BLINK_GPIO 8
#define BLINK_PERIOD 500

#define ON true
#define OFF false

typedef struct led {
  char* tag;
  bool ledOn;
  led_strip_handle_t ledStrip;
} Led;

typedef struct Led led;

void initLed(void);
void flashLed(void);
void configureLed(void);
void setLed(bool ledOn);

#endif