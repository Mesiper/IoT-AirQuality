# IoT-AirQuality
Distributed IoT air quality monitoring system utilizing ESP32, MQTT, Node-RED, and InfluxDB.

## 🏗️ Hardware Architecture

* **Microcontroller:** ESP32 Development Board
* **Sensor:** Grove Air Quality Sensor v1.3 (MP503)
* **Wiring Setup (Cable Extension Method):**
  To ensure a stable physical connection, the original Grove cable is plugged into the sensor socket. DuPont jumper wires are then used to bridge the free end of the Grove cable directly to the ESP32 pins.
  * `GND` (Black wire)  ➔ ESP32 `GND`
  * `VCC` (Red wire)    ➔ ESP32 `3.3V` (CRITICAL: Do not use 5V to protect ESP32 ADC)
  * `SIG` (Yellow wire) ➔ ESP32 `Pin 34` / `G34` (Analog input)
  * `NC`  (White wire)  ➔ Not connected