//Main Program Outline (for Each Zone Arduino)
//Combining all code elements into the main structure:

void setup() {
    setupADC();
    setupGPIO();
    setupTimer();
    setupSerial();
    sei(); // Enable global interrupts
}

void loop() {
    debounceHandler();
    // Regular checks, e.g., sending power data, checking thresholds
    int voltage = readADC(0);
    int current = readADC(1);
    int power = voltage * current;
    if (power > THRESHOLD) turnOnLED();
    else turnOffLED();
    
    // Periodically write data to EEPROM or send via serial
}
