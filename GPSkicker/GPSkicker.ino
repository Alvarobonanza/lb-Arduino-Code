#include <Adafruit_GPS.h>
#include <inttypes.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
boolean usingInterrupt = false;

void setup()  
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("serial init");
  GPS.begin(9600);
  delay(1000);
  Serial.println("gps init");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  delay(1000);
  Serial.println("rmc command set");
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  // 1 Hz update rate
  delay(100);
  Serial.println("1 hz command set");
  useInterrupt(true);
  if (GPS.LOCUS_StartLogger())
    Serial.println("Logging STARTED!");
  else
    Serial.println("!No response!");
  useInterrupt(false);
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } 
  else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

void loop(void)
{
  
}

