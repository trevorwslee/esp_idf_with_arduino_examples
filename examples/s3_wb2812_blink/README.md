
# `s3_wb2812_blink`

* with IDF v5.3.2
* new project
  - for ESP32S3 ***with WB2812 pixel @ 48***
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
* ***clean*** build again

* create folder `main/arduino_libraries`
* open prompt in `main/arduino_libraries`
* clone ***Freenove_WS2812_Lib_for_ESP32*** like
```
git clone https://github.com/Freenove/Freenove_WS2812_Lib_for_ESP32
```
  this will clone the library to `arduino_libraries/Freenove_WS2812_Lib_for_ESP32`
* add `arduino_libraries/Freenove_WS2812_Lib_for_ESP32` as SRC_DIR and INCLUDE_DIR to `main/CMakeLists.txt` like
```
idf_component_register(
    SRC_DIRS "." "arduino_libraries/Freenove_WS2812_Lib_for_ESP32"
    INCLUDE_DIRS "arduino_libraries/Freenove_WS2812_Lib_for_ESP32"
)
```
* now, code `void setup()` and `void loop()` as with Arduino
```
...

#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  1
#define LEDS_PIN	 48
#define CHANNEL		  0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
  strip.begin();
  strip.setBrightness(20);  
}
void loop() {
  for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
    }
    strip.show();
    delay(10);
  }  
}

...
```