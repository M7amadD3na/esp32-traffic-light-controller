# ESP32 Traffic Light Controller

Implements a timed traffic light sequence with push-button interrupt handling and a pedestrian-priority mode.

## Technologies

ESP32, GPIO interrupts, millis()

## Requirements

Arduino core for ESP32.

## Hardware and setup notes

LED GPIOs: red 23, yellow 22, green 21; button GPIO18. Timing values are implemented with `millis()` and the button uses an interrupt. Provide an appropriate external pull-up or pull-down, according to the circuit.

## Run

1. Install the Arduino IDE and the required board support and libraries.
2. Open `ESP32_Traffic_Light_Controller.ino` from this folder.
3. Review pin assignments, the target board, and any network settings.
4. Replace placeholders (such as `YOUR_THINGSPEAK_WRITE_API_KEY`) with **your own settings locally**. Never commit real passwords or API keys.
5. Compile and upload to compatible hardware; monitor serial output where relevant.

> Note: This portfolio package is a cleaned copy of an existing project sketch, not a claim that it was retested on hardware or security-hardened.
