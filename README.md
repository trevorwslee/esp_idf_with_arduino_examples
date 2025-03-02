

# ESP-IDF with Arduino Examples

![](/images/esp-idf-arduino.png)


ESP32 microcontroller program development with Arduino framework is fun.
Nevertheless, in order to be more flexible, it is often easier to go the route of ESP32 program development with ESP-IDF.

Say,
* With microphone module installed, it is possible to develop "wake-word" recognition; however, it is not clear / easy to do so in Arduino framework. E.g. [ESP-Box](https://github.com/espressif/esp-box).
* With camera module installed, it is possible to develop face recognition (not just face detection); however, it is not clear / easy to do so in Arduino framework. E.g. [ESP-Eye](https://github.com/espressif/esp-who).

Consequently, one might then choose to develop ESP32 program directly and completely with the well-supported native ESP-IDF framework.

Nevertheless, it is possible to do it the other way around, by incorporating Arduino framework style in ESP-IDF programming.
Will this make ESP32 programming looks easier? Moreover, it might be possible to use libraries written using the Arduino framework. At the very least, this way might be helpful in transition from the easier non-native Arduino framework for ESP32 to the native ESP-IDF. 

As stated in [Arduino as an ESP-IDF component](https://github.com/espressif/arduino-esp32/blob/master/docs/en/esp-idf_component.rst)
> You can use the Arduino framework as an ESP-IDF component. This allows you to use the Arduino framework in your ESP-IDF projects with the full flexibility of the ESP-IDF.

It is yet to see how compatible is Arduino code with ESP-IDF code; regardless, let's have some fun trying some ESP-IDF with Arduino examples, as will be described next.

Here
* VSCode will be used as the development IDE, certainly, together with ESP-IDF VSCode extension
* The target [ESP-IDF](https://github.com/espressif/esp-idf) version is v5.3.2
* The target [Arduino core for ESP32](https://github.com/espressif/arduino-esp32) is v3.0.2


# Examples

The examples that we will try out are:
* [`idf-blink`](/examples/idf_blink/README.md): A simple ESP-IDF blink program that is essentially generated by ESP-IDF without modification; it blinks the built-in LED (***pin 2***)
* [`idf_with_a_blink`](/examples/idf_with_a_blink/README.md): From an "empty" ESP-IDF program, modified to incorporate with Arduino to blink the built-in LED, the same as `idf-blink` but coded in Arduino style
* [`s3_wb2812_blink`](/examples/s3_wb2812_blink/README.md): Again, started from an "empty" ESP-IDF program, modified to incorporate with Arduino, in order to be able to use the Arduino library [Freenove_WS2812_Lib_for_ESP32](https://github.com/Freenove/Freenove_WS2812_Lib_for_ESP32) for "blinking" the NeoPixel on an ESP32S3 board (***pin 48***)
* [`wifi_dd_blink`](/examples/wifi_dd_blink/README.md): Modified to incorporate with Arduino, in order to use the Arduino library [Arduino-DumbDisplay](https://github.com/trevorwslee/Arduino-DumbDisplay).
  With DumbDisplay, you can realize simple UI on your Android phone. You may want to refer to the post [Blink Test With Virtual Display, DumbDisplay](https://www.instructables.com/Blink-Test-With-Virtual-Display-DumbDisplay/) for a brief introduction to DumbDisplay. Note that this example `wifi_dd_blink` uses WiFi connectivity, rather than OTG as described in the post.
* [`le_dd_blink`](/examples/le_dd_blink/README.md): Like `wifi_dd_blink`, but is a bit more extensive in using DumbDisplay's features, and is using Bluetooth Low Energy connectivity. Moreover, `le_dd_blink` deliberately uses some ESP-IDF constructs like `xTaskCreate()` / `vTaskDelay()` / `printf()`   


# Highlights

The steps I worked out to add Android to ESP-IDF is based on the above mentioned [official] [Arduino as an ESP-IDF component](https://github.com/espressif/arduino-esp32/blob/master/docs/en/esp-idf_component.rst): 

* Add IDF component to `idf_component.yml`:
  ```
  dependencies:
    idf:
      version: '>=4.1.0'
    espressif/arduino-esp32: ^3.0.2
  ```

* The default of `CONFIG_FREERTOS_HZ` in `sdkconfig` is 100, change it to 1000

* The C entry point `app_main()` should be declared in a C++ file like
  ```
  #include "Arduino.h"
  extern "C" void app_main(void) {
      initArduino();
  }
  ```
  Notice:
  - The inclusion of the header file `Arduino.h`
  - The initialization routine `initArduino()` should be called the first thing in the entry point `app_main()`

* In order to make it more like programming with Arduino framework, `setup()` and `loop()` can be added like
  ```
  #include "Arduino.h"
  void setup() {}
  void loop() {}
  extern "C" void app_main(void) {
    initArduino();
    setup();
    while (1) {
      loop();
    }
  }
  ```

* ***A way*** to use Arduino library is to download the Arduino library source code and compile the library code as if it is part of the main program. Hence
  - in `main`, create the folder `arduino_libraries` for the the downloaded / cloned Arduino library source code
  - modify `CMakeLists.txt` in `main` to compile the library source, like
    ```
    idf_component_register(
        SRC_DIRS "." "arduino_libraries/Freenove_WS2812_Lib_for_ESP32/src"
        INCLUDE_DIRS "arduino_libraries/Freenove_WS2812_Lib_for_ESP32/src"
    )
    ```
    or
    ```
    idf_component_register(
        SRC_DIRS "." "arduino_libraries/Arduino-DumbDisplay"
        INCLUDE_DIRS "arduino_libraries/Arduino-DumbDisplay"
    )
    ```


# Demonstration

You may be interested in a demonstration of steps leading to the examples as recorded in the video [ESP-IDF with Arduino Examples; from IDF-Blink to Virtual Blink using WiFi / BLE](https://www.youtube.com/watch?v=RX5YHPoaXaY)


# Enjoy!

Hope that you will have fun with the examples!

Do share anything you find interesting / insightful concerning ESP-IDF with Arduino development.

Enjoy!


> Peace be with you!
> May God bless you!
> Jesus loves you!
> Amazing Grace!


