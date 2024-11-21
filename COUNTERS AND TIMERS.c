void setupTimer() {
    TCCR1B |= (1 << WGM12) | (1 << CS12); // CTC mode, prescaler 256
    OCR1A = 62500; // Set compare value for 1s interval (at 16 MHz)
    TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt
    sei(); // Enable global interrupts
}

ISR(TIMER1_COMPA_vect) {
    // Code to sample and store data every second
}
