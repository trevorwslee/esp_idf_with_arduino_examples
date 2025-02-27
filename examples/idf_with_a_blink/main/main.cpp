#include "Arduino.h"

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

extern "C" void app_main(void)
{
  initArduino();
  setup();
  while(1)
  {
    loop();
  }
}