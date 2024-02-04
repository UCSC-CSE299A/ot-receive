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

#define HUE 10
#define SATURATION 188
#define VALUE 10

void initLed() {
  globalLed = calloc(1, sizeof(Led));
  globalLed->tag = "example";
  globalLed->s_led_state = 1;
  globalLed->led_strip = NULL;
  return;
}

void blinkLed() {
  if (globalLed->s_led_state) {
      led_strip_set_pixel_hsv(globalLed->led_strip, INDEX,
                              HUE, SATURATION, VALUE);
      led_strip_refresh(globalLed->led_strip);
  } else {
      led_strip_clear(globalLed->led_strip);
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
    &(globalLed->led_strip))
  );
  led_strip_clear(globalLed->led_strip);

  return;
}