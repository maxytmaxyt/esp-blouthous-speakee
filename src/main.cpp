#include <Arduino.h>
#include "BluetoothA2DPSink.h"

// Initialize the Bluetooth Sink
BluetoothA2DPSink a2dp_sink;

void setup() {
    // Configure the internal DAC of the ESP32 (GPIO 25 and 26)
    // This allows connecting the HW-710 directly without an external I2S DAC
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

    // Apply the configuration to the sink
    a2dp_sink.set_i2s_config(i2s_config);

    // Start Bluetooth with the name of your choice
    // The device will appear as "ESP32_Speaker" on your phone
    a2dp_sink.start("ESP32_Speaker");
}

void loop() {
    // The library handles audio streaming automatically in the background
    // No code needed here unless you want to add buttons for volume/playback
}
