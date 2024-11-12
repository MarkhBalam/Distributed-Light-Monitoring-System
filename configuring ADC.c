void setup() {
    Serial.begin(9600); // Start serial for communication

    // Configure ADC: AVCC as reference, ADC enabled, prescaler of 128
    ADMUX = (1 << REFS0); // Reference voltage on AVCC
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC and set prescaler
}

int readADC(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // Select ADC channel
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
    return ADC; // Return ADC value
}

void loop() {
    int voltage = readADC(0); // Read from A0
    int current = readADC(1); // Read from A1

    // Sending data over serial to Arduino 4 (EEPROM)
    Serial.print("V:");
    Serial.print(voltage);
    Serial.print(",I:");
    Serial.println(current);

    delay(1000); // Sample every second
}
