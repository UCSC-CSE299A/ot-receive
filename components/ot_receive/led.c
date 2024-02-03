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
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "led.h"

Led* blink_led(Led* led) {
  if (led->s_led_state) {
      led_strip_set_pixel_hsv(
        led->led_strip,
        0,
        random(),
        random(),
        10
      );
      led_strip_refresh(led->led_strip);
  } else {
      led_strip_clear(led->led_strip);
  }

  return led;
}

Led* configure_led(Led *led) {
  ESP_LOGI(led->tag, "Example configured to blink addressable LED!");

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
    &(led->led_strip))
  );
  led_strip_clear(led->led_strip);

  return led;
}