// 

#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;
  
void setup() {  
  mcp.begin();      // use default address 0
  TWBR = 12;    // go to 400 KHz I2C speed mode

  mcp.pinMode(0, OUTPUT);
}


// flip the pin #0 up and down

void loop() {
  delay(100);

  mcp.digitalWrite(0, HIGH);

  delay(100);

  mcp.digitalWrite(0, LOW);
}
