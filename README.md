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

  ## 🌐 System Architecture & Payload

1. **Edge Device:** ESP32 reads analog data and publishes a JSON payload every 10 seconds.
2. **Message Broker:** Broker receives MQTT payloads on the `TO DO` topic.
3. **Processing Node:** Node-RED subscribes to the topic, parses the JSON, and routes the data.
4. **Database:** InfluxDB stores the telemetry data for long-term retention and visualization.

**MQTT Payload Format:**
```json
{
  "quality": 2345
}
```
*(Note: The `quality` value is a raw 12-bit ADC reading ranging from 0 to 4095).*

## 🚀 Setup Instructions

### ⚠️ Important Note for VS Code / PlatformIO Users
Due to the repository structure, Visual Studio Code must be opened directly in the PlatformIO project subfolder to properly load the build environment and IntelliSense.

If the PlatformIO toolbar is missing at the bottom of the screen, or if you see `#include` errors:
1. Go to **File** -> **Open Folder...**
2. Select the inner directory: `IoT-AirQuality/ESP32-MP503` (do not just open the root repository folder).

### 1. Embedded Firmware (PlatformIO)
1. Clone this repository to your local machine.
2. Open the `ESP32-MP503` directory in **Visual Studio Code** (see note above).
3. Verify your board's COM port in the Windows Device Manager and update `upload_port` and `monitor_port` in `platformio.ini` if necessary.
4. Build and upload the code to the ESP32 using the PlatformIO sidebar.