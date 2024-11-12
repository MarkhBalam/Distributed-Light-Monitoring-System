ISR(TIMER1_COMPA_vect) {
    // Timer1 ISR: Called every second for sampling
    Serial.println("Timer Event: Sampling data");
}

void setup() {
    Serial.begin(9600);

    // Configure Timer1 for CTC mode with 1Hz (1-second intervals)
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, 1024 prescaler
    OCR1A = 15624; // Compare value for 1Hz at 16MHz

    TIMSK1 = (1 << OCIE1A); // Enable Timer1 Compare A interrupt
    sei(); // Enable global interrupts
}

void loop() {
    // Empty loop since ISR handles timing events
}
