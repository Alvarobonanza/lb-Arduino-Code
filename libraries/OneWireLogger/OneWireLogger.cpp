////////////////////////////////////////////////////////////////////////////
//  OneWireLogger.cpp - Library for OneWireLogger
//  Created by Douglas Gilliland. 2013-08-29
//  OneWireLogger is an Leonardo compatible
////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "OneWireLogger.h"
 
////////////////////////////////////////////////////////////////////////////
// OneWireLogger constructor
////////////////////////////////////////////////////////////////////////////

OneWireLogger::OneWireLogger(void)
{
  initPins();
  return;
}

////////////////////////////////////////////////////////////////////////////
// initPins() - Initialize the pins on the part
////////////////////////////////////////////////////////////////////////////

void OneWireLogger::initPins(void)
{
  pinMode(BACKLIGHT, OUTPUT);     // LCD Backlight
  pinMode(LCD_RST, OUTPUT);       // LCD Reset
  pinMode(SD_CS, OUTPUT);         // SD Card Chip Select
  digitalWrite(BACKLIGHT, LOW);
  digitalWrite(LCD_RST, HIGH);
  digitalWrite(SD_CS, HIGH);
  return;
}

////////////////////////////////////////////////////////////////////////////
// pollKeypad() - Returns the value of the instantenously pressed keys
////////////////////////////////////////////////////////////////////////////

signed char OneWireLogger::pollKeypad(void)
{
  unsigned int sensorValue = analogRead(KEYPAD);
#ifdef SERIAL_DEBUG
  Serial.print("pollKeypad(): Switch Value = ");
  Serial.println(sensorValue);
#endif
  if (sensorValue > 871)    // quick if none is pressed
    return((byte)NONE);  
  else if (sensorValue <= 67)
    return((byte)RIGHT);
  else if (sensorValue <= 214)
    return((byte)UP);
  else if (sensorValue <= 384)
    return((byte)DOWN);
  else if (sensorValue <= 596)
    return((byte)LEFT);
  else
    return((byte)SELECT);
}

////////////////////////////////////////////////////////////////////////////
// waitForKeyRelease() - Stick in the routine as long as the key is pressed
////////////////////////////////////////////////////////////////////////////

void OneWireLogger::waitForKeyRelease(void)
{
  while (analogRead(KEYPAD) <= 871)
    delay(5);
}

////////////////////////////////////////////////////////////////////////////
// getKeyPressed() - Hang around polling the keypad waiting for a key 
//  to be pressed.
// When the key is pressed, hang around waiting for the key to be released.
// Returns the value of the key that was pressed.
////////////////////////////////////////////////////////////////////////////

signed char OneWireLogger::getKeyPressed(void)
{
  signed char keyPadVal2;
  keyPadVal2 = pollKeypad();
  if (keyPadVal2 == NONE)
    return((byte)NONE);
  waitForKeyRelease();
  return((byte)keyPadVal2);
}

////////////////////////////////////////////////////////////////////////////
// waitKeyPressed()
////////////////////////////////////////////////////////////////////////////

signed char OneWireLogger::waitKeyPressed(void)
{
  signed char keyPadVal3;
  do
  {
    keyPadVal3 = pollKeypad();
  }
  while (keyPadVal3 == NONE);
  delay(5);
  waitForKeyRelease();
  return((byte)keyPadVal3);
}

////////////////////////////////////////////////////////////////////////////
// delayAvailable(int delayTime) - Delay but check the Serial.available flag
// This is useful for places that a delay lasts for a noticable time and
//  there is a reason to break into the delay for serial input.
////////////////////////////////////////////////////////////////////////////

signed char OneWireLogger::delayAvailable(int delayTime)
{  
  int delayTimeDiv5;
  delayTimeDiv5 = delayTime / 5;
  while (delayTimeDiv5 > 0)
  {
    if (pollKeypad() != NONE)
      return((byte)1);
    delay(5);
    delayTimeDiv5--;
  }
  return((byte)0);
}
