
## idf_with_a_blink

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
* ***clean*** build again
* now, code `void setup()` and `void loop()` as with Arduino
```
...
#define LED_BUILTIN 2
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}
void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("* LOW");
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("* HIGH");
  delay(1000);
}
...
```