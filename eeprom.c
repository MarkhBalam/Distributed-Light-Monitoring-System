void writeEEPROM(int address, uint8_t value) {
    while (EECR & (1 << EEPE)); // Wait for previous write
    EEAR = address; // Set EEPROM address
    EEDR = value; // Set data to write
    EECR |= (1 << EEMPE); // Master Write Enable
    EECR |= (1 << EEPE); // Start EEPROM write
}

uint8_t readEEPROM(int address) {
    while (EECR & (1 << EEPE)); // Wait for completion
    EEAR = address; // Set EEPROM address
    EECR |= (1 << EERE); // Start EEPROM read
    return EEDR; // Return read data
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readString();
        
        if (data.startsWith("V:")) { // Example data processing
            int value = data.substring(2).toInt();
            writeEEPROM(0, value); // Store voltage reading at address 0
        } else if (data.startsWith("I:")) {
            int value = data.substring(2).toInt();
            writeEEPROM(1, value); // Store current reading at address 1
        }
    }

    delay(1000); // Check for data periodically
}
