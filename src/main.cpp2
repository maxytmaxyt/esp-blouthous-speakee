#include <Arduino.h>
#include "BluetoothA2DPSink.h"

// Configuration constants
const char* DEVICE_NAME = "ESP32_Speaker";
const uint32_t SERIAL_BAUD_RATE = 115200;

BluetoothA2DPSink a2dp_sink;

void setup() {
    // Initialize serial communication for logging
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("Starting ESP32 Bluetooth A2DP Sink...");

    // Define the I2S configuration for the internal DAC (GPIO 25 and 26)
    // Kept inline for clear visibility of all hardware settings
    const i2s_config_t i2s_config = {
        .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t) I2S_COMM_FORMAT_STAND_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false
    };

    Serial.println("Applying I2S configuration for internal DAC...");
    a2dp_sink.set_i2s_config(i2s_config);

    // Register a callback to log connection changes
    a2dp_sink.set_on_connection_state_changed([](esp_a2d_connection_state_t state, void *ptr) {
        if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
            Serial.println("Connection status: DEVICE CONNECTED");
        } else if (state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
            Serial.println("Connection status: DEVICE DISCONNECTED");
        }
    });

    // Register a callback to log volume changes for better control
    a2dp_sink.set_on_volumechange_called([](int volume) {
        // Convert the 0-127 volume range to a percentage for easier reading
        int volume_percent = (volume * 100) / 127;
        Serial.printf("Volume changed to: %d%%\n", volume_percent);
    });

    // Start the Bluetooth device
    Serial.print("Starting Bluetooth service with name: ");
    Serial.println(DEVICE_NAME);
    
    a2dp_sink.start(DEVICE_NAME);

    Serial.println("Setup completed successfully. Waiting for connection...");
}

void loop() {
    // The ESP32-A2DP library uses FreeRTOS tasks in the background.
    // No manual audio processing is required in the main loop.
    
    delay(1000); // Small delay to prevent the loop from running too fast unnecessarily
}
