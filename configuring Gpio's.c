void setup() {
    Serial.begin(9600);

    // Set PB5 (Digital pin 13) as output for LED
    DDRB |= (1 << DDB5); 
    // Set PD2 (Digital pin 2) as input with pull-up for button
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2); // Enable pull-up
}

bool readButton() {
    return !(PIND & (1 << PIND2)); // Check if button is pressed
}

void loop() {
    if (readButton()) {
        PORTB |= (1 << PORTB5); // Turn on LED
    } else {
        PORTB &= ~(1 << PORTB5); // Turn off LED
    }
    delay(100); // Short delay for stability
}
