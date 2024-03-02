/**
 * All the code is the file comes from Espressif's ESP Blink example:
 * https://github.com/espressif/esp-idf/tree/master/examples/get-started/blink
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "led.h"

#define INDEX 0

/**
 * LED color will be a light blue. I got the color from:
 * https://hslpicker.com/#00330e
*/
#define HUE 137
#define SATURATION 100
#define VALUE 10

/**
 * Initialize the global Led.
 *
 * I re-learned how to use extern global variables from:
 * https://stackoverflow.com/a/1433387
*/
Led globalLed = {
  "",     // led->tag
  0,      // led->ledOn
  NULL    // led->ledStrip
};

void initLed(Led *led) {
  led->tag = "ot-receive-led";
  led->ledOn = 1;
  led->ledStrip = NULL;
  return;
}

/**
 * Although I will allocate the "Led" struct in the stack,
 * the "led_strip_handle_t" will use heap memory. This function
 * free the heap memory holding the no longer needed "led_strip_handle_t".
*/
void freeLed(Led *led) {
  led_strip_del(led->ledStrip);
  return;
}

void setLed(Led *led, bool ledOn) {
  led->ledOn = ledOn;
  return;
}

void flashLed(Led *led) {
  if (led->ledOn) {
      led_strip_set_pixel_hsv(led->ledStrip, INDEX,
                              HUE, SATURATION, VALUE);
      led_strip_refresh(led->ledStrip);
  } else {
      led_strip_clear(led->ledStrip);
  }

  return;
}

void configureLed(Led *led) {
  led_strip_config_t strip_config = {
      .strip_gpio_num = BLINK_GPIO,
      .max_leds = 1,
  };

  led_strip_rmt_config_t rmt_config = {
      .resolution_hz = 10 * 1000 * 1000, // 10MHz
  };

  ESP_ERROR_CHECK(
    led_strip_new_rmt_device(
    &strip_config,
    &rmt_config,
    &(led->ledStrip))
  );
  led_strip_clear(led->ledStrip);

  return;
}