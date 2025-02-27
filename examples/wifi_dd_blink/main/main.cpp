#include "Arduino.h"

#include "_secret.h"
#include "wifidumbdisplay.h"

DumbDisplay dumbdisplay(new DDWiFiServerIO(WIFI_SSID, WIFI_PASSWORD));
LedGridDDLayer *led;

void setup() {
  led = dumbdisplay.createLedGridLayer();
  led->offColor("lightgray");
  led->border(0.1, "blue");
}
void loop() {
  led->toggle();
  delay(1000);
}

extern "C" void app_main(void)
{
  initArduino();
  setup();
  while(1)
  {
    loop();
  }
}