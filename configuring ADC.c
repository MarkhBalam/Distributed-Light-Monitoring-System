//Each zone Arduino uses ADC to read voltage and current values from sensors. Since we avoid using analogRead, we directly configure and read ADC registers.


void setupADC() {
    // Reference voltage: AVcc, ADC prescaler: 64 (for better accuracy with slower reads)
    ADMUX = (1 << REFS0); 
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

int readADC(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8) | channel; // Select ADC channel
    ADCSRA |= (1 << ADSC);             // Start conversion
    while (ADCSRA & (1 << ADSC));      // Wait for conversion to finish
    return ADC;                        // Return ADC result
}


//Usage Example:

int voltageReading = readADC(0); // Read from channel 0
int currentReading = readADC(1); // Read from channel 1
