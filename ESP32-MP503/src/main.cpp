#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


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


// === Network & MQTT configuration ===

/**
 * @brief Wi-Fi network credentials.
 */
constexpr auto WIFI_SSID     = "czar(nuch)prys";
constexpr auto WIFI_PASSWORD = "nygger2137";

/**
 * @brief MQTT Broker settings. Replace with the IP of the laptop running Docker.
 */
constexpr auto MQTT_SERVER   = "192.168.0.143";
constexpr auto MQTT_PORT     = 1883;

/**
 * @brief MQTT Topic configured in Node-RED / board_sim.py.
 */
constexpr auto MQTT_TOPIC    = "DATA";


// === Global objects ===

/**
 * Network client handling the physical Wi-Fi connection.
 */
WiFiClient espClient;

/**
 * MQTT client operating over the Wi-Fi network object.
 */
PubSubClient mqtt{espClient};


// === Helper functions ===

/**
 * @brief Initializes and establishes connection to the local Wi-Fi network.
 */
void connectToWiFi() {
  Serial.printf("[WIFI] Connecting to %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\n[WIFI] Connected! IP Address: ");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Ensures the MQTT session is active. Reconnects if the connection is lost.
 */
void ensureMQTTConnection() {
  while (!mqtt.connected()) {
    Serial.print("[MQTT] Connecting to broker... ");

    // Generate a unique client ID for this specific board
    String clientId = "ESP32_Hardware_" + String(random(0xffff), HEX);

    if (mqtt.connect(clientId.c_str())) {
      Serial.println("CONNECTED: 0");
    } else {
      Serial.printf("Failed, rc=%d. Retrying in 5 seconds...\n", mqtt.state());
      delay(5000);
    }
  }
}

// === Main program ===

/**
 * @brief Initializes the serial communication interface, Wi-Fi, and MQTT.
 */
void setup() {
  Serial.begin(SERIAL_MONITOR_BAUD_RATE);

  // Brief delay to allow the serial interface to stabilize
  delay(200);

  // Initialize network and broker configuration
  connectToWiFi();
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);

  Serial.println("Setup completed.");
}

/**
 * @brief Periodically samples the analog pin, transmits the reading over Serial,
 * formats it into a JSON payload, and publishes it via MQTT.
 */
void loop() {
  // Maintain network connection
  ensureMQTTConnection();
  mqtt.loop();

  // Read and print hardware data
  int raw_air_quality = analogRead(SENSOR_PIN);
  Serial.printf("MP503 Raw Analog Value: %d\n", raw_air_quality);

  // Format to JSON {"air_quality" : value}
  String payload = String("{\"air_quality\":") + String(raw_air_quality) + String("}");

  // Publish over MQTT
  bool result = mqtt.publish(MQTT_TOPIC, payload.c_str());
  Serial.printf("[MQTT] publish rc: %d | Sent: %s\n", result, payload.c_str());

  delay(MEASURE_DELAY_MS);
}