#include "Arduino.h"


// *****
// * more Arduino like
// *****

#include "esp32bledumbdisplay.h"
DumbDisplay dumbdisplay(new DDBLESerialIO("ESP_LE"));
DDMasterResetPassiveConnectionHelper pdd(dumbdisplay);

LedGridDDLayer *led;
int counter = 0;

void switchColor() {
  const char* color = "darkblue";
  switch (counter++ % 3) {
    case 0:
      color = "darkred";
      break;
    case 1:
      color = "darkgreen";
      break;
  }
  led->onColor(color);
  led->offColor("gray");
  dumbdisplay.log(String("!!! switched color to ") + String(color));
}
void initializeDD() {
  led = dumbdisplay.createLedGridLayer();
  led = dumbdisplay.createLedGridLayer();
  led->enableFeedback("fl");
  switchColor();
}
void updateDD(bool isFirstUpdate) {
  if (led->getFeedback()) {
    switchColor();
  }
  led->toggle();
  delay(1000);
}
void disconnectedDD() {
}
void handleIdle(bool justBecameIdle) {
}

void setup() {
}
void loop() {
 pdd.loop([](){
    // **********
    // *** initializeCallback ***
    // **********
    initializeDD();
  }, [](){
    // **********
    // *** updateCallback ***
    // **********
    updateDD(!pdd.firstUpdated());
  }, [](){
    // **********
    // *** disconnectedCallback ***
    // **********
    disconnectedDD();
  });
  if (pdd.isIdle()) {
    handleIdle(pdd.justBecameIdle());
  }
}




// *****
// * more ESP-IDF like
// *****

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define BLINK_GPIO  GPIO_NUM_2

static const char *TAG = "ble_dd_blink";

static void blink_task(void *args) {
  ESP_LOGW(TAG, "started blink_task");
  gpio_reset_pin(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  bool on = true;
  while (1) {
    gpio_set_level(BLINK_GPIO, on);
    const char* state;
    if (dumbdisplay.connected()) { // *** actually, it is not very safe to access variable from another task without synchronization ***
      state = "CONNECTED";
    } else {
      state = on ? "    ON   " : "   OFF   ";
    }
    printf("<<< %s >>>\n", state);
    on = !on;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void arduino_task(void *args) {
  setup();
  while (1) {
    loop();
  }
}

extern "C" void app_main(void)
{
  initArduino();
 
  BaseType_t ret_val = xTaskCreate(arduino_task, "Arduino Task", 8 * 1024, NULL, 1, NULL);
  ESP_ERROR_CHECK_WITHOUT_ABORT((pdPASS == ret_val) ? ESP_OK : ESP_FAIL);

  if (true) {
    //BaseType_t ret_val = xTaskCreatePinnedToCore(blink_task, "Blink Task", 8 * 1024, NULL, 1, NULL, 0);
    BaseType_t ret_val = xTaskCreate(blink_task, "Blink Task", 8 * 1024, NULL, 1, NULL);
    ESP_ERROR_CHECK_WITHOUT_ABORT((pdPASS == ret_val) ? ESP_OK : ESP_FAIL);
  }
}