Assume:
* VSCode
* git


Init (from prompt):
* create directory "esp_idf_with_arduino_examples" (say, in "VSCodePrjs"
```
mkdir esp_idf_with_arduino_examples
```
* open folder "esp_idf_with_arduino_examples" with VSCode
```
code esp_idf_with_arduino_examples
```


In VSCode:
* create folder "examples"
* add that folder "esp_idf_with_arduino_examples" to workspace
* save the workspace


Install ESP-IDF for VSCode
* install extension ESP-IDF
* install ESP-IDF v5.3.2


Example "idf_blink" (for ESP32 with built-in LED @ 2): 
* create "idf_blink" sample in the "examples" folder
* add the "idf_blink" folder to workspace
* select "idf_blink" as ESP-IDF current project
* use SDK Config editor to set blink pin 2
* build
* upload
* monitor


Example "idf_with_a_blink" (for ESP32 with built-in LED @ 2)
* create "idf_with_a_blink" in "examples" folder (using empty template)
* add "idf_with_a_blink" to workspace
* select "idf_with_a_blink" as ESP-IDF current project
* add to "main" folder "idf_component.yml"
```
dependencies:
  idf:
    version: '>=4.1.0'
  espressif/arduino-esp32: ^3.0.2
```
* change CMakeLists.txt sample
```
idf_component_register(
  SRC_DIRS "."
  INCLUDE_DIRS "."
)
```
* rename "main.c" to "main.cpp" with content
  - https://raw.githubusercontent.com/trevorwslee/esp_idf_with_arduino_examples/refs/heads/main/examples/idf_with_a_blink/main/main.cpp
* build
* upload
* monitor


Example "s3_wb2812_blink" (for ESP32S3 with WB2812 pixel @ 48)
* create "s3_wb2812_blink" in "examples" folder (using empty template)
* add "s3_wb2812_blink" to workspace
* select "s3_wb2812_blink" as ESP-IDF current project
* SELECT ESP32S3
* add to "main" folder "idf_component.yml"
```
dependencies:
  idf:
    version: '>=4.1.0'
  espressif/arduino-esp32: ^3.0.2
```
* add "arduino_libraries" to "main" folder
* in "arduino_libraries", clone ***Freenove_WS2812_Lib_for_ESP32***
```
git clone https://github.com/Freenove/Freenove_WS2812_Lib_for_ESP32
```
* change CMakeLists.txt sample
```
idf_component_register(
  SRC_DIRS "." "arduino_libraries/Freenove_WS2812_Lib_for_ESP32/src"
  INCLUDE_DIRS "." "arduino_libraries/Freenove_WS2812_Lib_for_ESP32/src"
)
```
* rename "main.c" to "main.cpp" with content
  - https://raw.githubusercontent.com/trevorwslee/esp_idf_with_arduino_examples/refs/heads/main/examples/s3_wb2812_blink/main/main.cpp
* set sdkconfig
  - CONFIG_FREERTOS_HZ=1000 
* build
* upload
* monitor


Example "wifi_dd_blink" (for ESP32 or ESP32S3 or etc)
* for this to work, you will need
  - Android phone
  - DumbDisplay Android app -- https://play.google.com/store/apps/details?id=nobody.trevorlee.dumbdisplay
* create "wifi_dd_blink" in "examples" folder (using empty template)
* add "wifi_dd_blink" to workspace
* select "wifi_dd_blink" as ESP-IDF current project
* add to "main" folder "idf_component.yml"
```
dependencies:
  idf:
    version: '>=4.1.0'
  espressif/arduino-esp32: ^3.0.2
```
* add "arduino_libraries" to "main" folder
* in "arduino_libraries", clone ***DumbDisplay***
```
git clone https://github.com/trevorwslee/Arduino-DumbDisplay
```
* change CMakeLists.txt sample
idf_component_register(
    SRC_DIRS "." "arduino_libraries/Arduino-DumbDisplay"
    INCLUDE_DIRS "arduino_libraries/Arduino-DumbDisplay"
)
```
* rename "main.c" to "main.cpp" with content
  - https://raw.githubusercontent.com/trevorwslee/esp_idf_with_arduino_examples/refs/heads/main/examples/wifi_dd_blink/main/main.cpp
* add "_secret.h" with content like
```
#define WIFI_SSID           "wifi ssid"
#define WIFI_PASSWORD       "wifi password"
```
* set sdkconfig
  - CONFIG_FREERTOS_HZ=1000 
* build
* upload
* monitor ... to see the IP DumbDisplay Android app to make connection with
* make connection from DumbDisplay Android app with that IP


Example "le_dd_blink" (for ESP32 with built-in LED @ 2)
* create "le_dd_blink" in "examples" folder (using empty template)
* add "le_dd_blink" to workspace
* select "le_dd_blink" as ESP-IDF current project
* add to "main" folder "idf_component.yml"
```
dependencies:
  idf:
    version: '>=4.1.0'
  espressif/arduino-esp32: ^3.0.2
```
* add "arduino_libraries" to "main" folder
* in "arduino_libraries", clone ***DumbDisplay***
```
git clone https://github.com/trevorwslee/Arduino-DumbDisplay
```
* change CMakeLists.txt sample
idf_component_register(
    SRC_DIRS "." "arduino_libraries/Arduino-DumbDisplay"
    INCLUDE_DIRS "arduino_libraries/Arduino-DumbDisplay"
)
```
* rename "main.c" to "main.cpp" with content
  - https://raw.githubusercontent.com/trevorwslee/esp_idf_with_arduino_examples/refs/heads/main/examples/le_dd_blink/main/main.cpp
* set sdkconfig
  - CONFIG_FREERTOS_HZ=1000 
* menuconfig ... search for and tick ***Bluetooth***   
* build
* upload
* monitor
* make connection from DumbDisplay Android app with that IP with Bluetooth Low Energy with device name "ESP_LE"