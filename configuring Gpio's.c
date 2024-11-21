//GPIO (LED and Button Handling)
//We control LEDs for alerts and buttons for user input (e.g., reset button), directly manipulating GPIO registers without digitalWrite or pinMode.


//Setup for GPIO Control:
void setupGPIO() {
    DDRB |= (1 << DDB0);    // Set PB0 (LED pin) as output
    PORTB &= ~(1 << PB0);   // Start with LED off

    DDRD &= ~(1 << DDD2);   // Set PD2 (Button pin) as input
    PORTD |= (1 << PD2);    // Enable pull-up resistor on button
}





//LED Control Functions:

void turnOnLED() {
    PORTB |= (1 << PB0);    // Turn LED on
}

void turnOffLED() {
    PORTB &= ~(1 << PB0);   // Turn LED off
}
