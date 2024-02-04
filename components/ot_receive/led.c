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
 * LED color will be a light blue:
*/
#define HUE 137
#define SATURATION 100
#define VALUE 10

/**
 * Stores a reference to the built-in LED on the MCU
 * as a global variable accessible by any function in the
 * `led.h` API.
*/
Led* globalLed;

void initLed() {
  globalLed = calloc(1, sizeof(Led));
  globalLed->tag = "example";
  globalLed->ledOn = 1;
  globalLed->ledStrip = NULL;
  return;
}

void setLed(bool ledOn) {
  globalLed->ledOn = ledOn;
  return;
}

void flashLed() {
  if (globalLed->ledOn) {
      led_strip_set_pixel_hsv(globalLed->ledStrip, INDEX,
                              HUE, SATURATION, VALUE);
      led_strip_refresh(globalLed->ledStrip);
  } else {
      led_strip_clear(globalLed->ledStrip);
  }

  return;
}

void configureLed() {
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
    &(globalLed->ledStrip))
  );
  led_strip_clear(globalLed->ledStrip);

  return;
}