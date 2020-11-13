// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <Arduino.h>

#include "secure.h"
#include "DHT.h"

#define _CONST_DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
// #define _DHTTYPE DHT11   // DHT 11
// #define _DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define _CONST_DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT _VAR_dht(_CONST_DHTPIN, _CONST_DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  _VAR_dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float _VARL_h = _VAR_dht.readHumidity();
  // Read temperature as Celsius (the default)
  float _VARL_t = _VAR_dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float _VARL_f = _VAR_dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(_VARL_h) || isnan(_VARL_t) || isnan(_VARL_f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float _VARL_hif = _VAR_dht.computeHeatIndex(_VARL_f, _VARL_h);
  // Compute heat index in Celsius (isFahreheit = false)
  float _VARL_hic = _VAR_dht.computeHeatIndex(_VARL_t, _VARL_h, false);

  Serial.print(F("Humidity: "));
  Serial.print(_VARL_h);
  Serial.print(F("%  Temperature: "));
  Serial.print(_VARL_t);
  Serial.print(F("°C "));
  Serial.print(_VARL_f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(_VARL_hic);
  Serial.print(F("°C "));
  Serial.print(_VARL_hif);
  Serial.println(F("°F"));
}




