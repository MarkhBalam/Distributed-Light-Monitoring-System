#include <EEPROM.h>

#define BUTTON_PIN 2       // Button connected to PD2
#define LED_PIN 13         // LED connected to PB5
#define LDR_PIN A0         // LDR connected to ADC0
#define DEBOUNCE_DELAY 50  // Debouncing delay in milliseconds

unsigned long lastReadTime = 0;  // Timer to track sampling interval
const unsigned long interval = 1000; // 1 second interval
bool dayMode; // Mode: true = Day, false = Night
bool lastButtonState = HIGH; // Last button state
unsigned long lastDebounceTime = 0;

void setup() {
    // Configure LED as output
    DDRB |= (1 << DDB5);   // Set PB5 (Pin 13) as output

    // Configure button as input
    DDRD &= ~(1 << DDD2);  // Set PD2 (Pin 2) as input
    PORTD |= (1 << PORTD2); // Enable pull-up on PD2

    Serial.begin(9600); // Start serial communication
    dayMode = EEPROM.read(0); // Load saved mode
}

void loop() {
    // Read button state with debounce
    bool reading = !(PIND & (1 << PIND2)); // Read button state (active LOW)
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading != dayMode) {
            dayMode = reading;
            EEPROM.update(0, dayMode); // Save new mode to EEPROM
        }
    }
    lastButtonState = reading;

    // Light sampling at regular intervals
    if (millis() - lastReadTime >= interval) {
        lastReadTime = millis();

        // Read light intensity from LDR
        int lightValue = analogRead(LDR_PIN);

        // Toggle LED to indicate reading
        PORTB |= (1 << PORTB5); // Turn LED ON
        delay(100);             // Small delay for visualization
        PORTB &= ~(1 << PORTB5); // Turn LED OFF

        // Format and send light data
        String data = "Node: " + String(lightValue) + (dayMode ? " Day" : " Night");
        Serial.println(data);
    }
}
