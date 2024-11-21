//EEPROM Storage
//Each zone Arduino stores cumulative power usage in EEPROM periodically
 //to retain information even if power is lost. Directly accessing EEPROM registers ensures we avoid EEPROM library functions.




 //EEPROM Write and Read Functions:
 void writeEEPROM(int address, uint8_t data) {
    while (EECR & (1 << EEPE));       // Wait for EEPROM to be ready
    EEAR = address;                    // Set EEPROM address
    EEDR = data;                       // Set data
    EECR |= (1 << EEMPE);              // Enable master write
    EECR |= (1 << EEPE);               // Start EEPROM write
}

uint8_t readEEPROM(int address) {
    while (EECR & (1 << EEPE));       // Wait for EEPROM to be ready
    EEAR = address;                   // Set EEPROM address
    EECR |= (1 << EERE);              // Start EEPROM read
    return EEDR;                      // Return data
}
