#include <Arduino.h>

// === Hardware configuration ===

/**
 * @brief The GPIO pin connected to the sensor's signal (SIG) line.
 * Labeled as G34 on the ESP32 board.
 */
constexpr int SENSOR_PIN = 34;

/**
 * @brief Delay between consecutive sensor readings (in milliseconds).
 */
constexpr int MEASURE_DELAY_MS = 2000;

/**
 * @brief Serial monitor baud rate. Must match platformio.ini serial monitor baud rate.
 */
constexpr int SERIAL_MONITOR_BAUD_RATE = 115200;

/**
 * Initializes the serial communication interface.
 */
void setup() {
  Serial.begin(SERIAL_MONITOR_BAUD_RATE);

  // Brief delay to allow the serial interface to stabilize
  delay(200);

  Serial.println("Setup completed.");
}

/**
 * Periodically samples the analog pin and transmits the reading over Serial.
 */
void loop() {
  int raw_air_quality = analogRead(SENSOR_PIN);
  Serial.printf("MP503 Raw Analog Value: %d\n", raw_air_quality);
  delay(MEASURE_DELAY_MS);
}
