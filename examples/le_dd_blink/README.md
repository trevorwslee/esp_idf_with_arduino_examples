
# `bt_dd_blink`

* with IDF v5.3.2
* new project
  - for ESP32 (***with in-built LED @ 2***)
  - with ESP-IDF template sample_project 

* add `idf_components.yml` to `main`
```
dependencies:
idf:
  version: '>=4.1.0'
espressif/arduino-esp32: ^3.0.2
```

* change `CMakeLists.txt` to be like
```
idf_component_register(
  SRC_DIRS "."
  INCLUDE_DIRS "."
)
```  

* rename `main.c` to `main.cpp` with new content like
```
#include "Arduino.h"

void setup() {
}
void loop() {
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
```  

* try build
* change `sdkconfig` key `CONFIG_FREERTOS_HZ` to 1000
* use SDK Configure editor
  - search for and tick ***Bluetooth***
* ***clean*** build again

* create folder `main/arduino_libraries`
* open prompt in `main/arduino_libraries`
* clone ***Arduino-DumbDisplay*** like
```
git clone https://github.com/trevorwslee/Arduino-DumbDisplay.git
```
  this will clone the library to `arduino_libraries/Freenove_WS2812_Lib_for_ESP32`
* add `arduino_libraries/Freenove_WS2812_Lib_for_ESP32` as SRC_DIR and INCLUDE_DIR to `main/CMakeLists.txt` like
```
idf_component_register(
    SRC_DIRS "." "arduino_libraries/Arduino-DumbDisplay"
    INCLUDE_DIRS "arduino_libraries/Arduino-DumbDisplay"
)
```
* now, code `void setup()` and `void loop()` as with Arduino
* first, add `main/_secret.h`
```
#define WIFI_SSID           "your wifi ssid"
#define WIFI_PASSWORD       "your wifi password"
```
* next, modify `main.cpp` like
```
...

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

...
```

* actually, might want to add more ESP-IDF favor to it, like
```
```
* for more of the final program, see `main.cpp`
