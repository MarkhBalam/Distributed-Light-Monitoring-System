// Interrupts and Switch Debouncing
//Debouncing is handled by checking the button state over intervals to stabilize input without library functions.



//Debounce with Interrupts:
volatile uint8_t debounceCounter = 0;

ISR(INT0_vect) {
    if (debounceCounter == 0) {
        debounceCounter = 10;   // Set debounce time
        // Code for handling button press
    }
}

void debounceHandler() {
    if (debounceCounter > 0) debounceCounter--;
}
