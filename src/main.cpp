#include <Arduino.h>
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

#define LED_PIN 2
#define SCK_PIN 27

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void connection_state_changed(esp_a2d_connection_state_t state, void *ptr)
{
    switch (state)
    {
        case ESP_A2D_CONNECTION_STATE_CONNECTED:
            digitalWrite(LED_PIN, HIGH);
            break;
        case ESP_A2D_CONNECTION_STATE_DISCONNECTED:
            digitalWrite(LED_PIN, LOW);
            break;
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // SCK PIN of the ADC should grounded 
    pinMode(SCK_PIN, OUTPUT);
    digitalWrite(SCK_PIN, LOW);

    auto cfg = i2s.defaultConfig();
    cfg.pin_bck = 14;
    cfg.pin_ws = 13;
    cfg.pin_data = 12;
    i2s.begin(cfg);

    a2dp_sink.set_on_connection_state_changed(connection_state_changed);
    a2dp_sink.start("Standa & Slata speaker");
}

void loop()
{
    delay(1000);
}
