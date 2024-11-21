// Timers and Counters
//We use timers to control the sampling intervals for the sensors, ensuring that data is sampled and processed at regular intervals.




//Timer Setup and Interrupt Service Routine (ISR):
void setupTimer() {
    TCCR1B |= (1 << WGM12) | (1 << CS12);  // CTC mode, prescaler 256
    OCR1A = 62500;                         // Set compare value for 1s interval (at 16 MHz)
    TIMSK1 |= (1 << OCIE1A);               // Enable Timer1 compare interrupt
    sei();                                 // Enable global interrupts
}

ISR(TIMER1_COMPA_vect) {
    // Sampling routine for voltage and current
    int voltage = readADC(0);
    int current = readADC(1);
    // Power calculation (P = V * I) and other processing can be added here
}
