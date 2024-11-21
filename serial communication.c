//Serial Communication
//Serial communication between each zone Arduino and the central Arduino requires configuring UART register


//Serial Communication Setup and Send Function:

#define MYUBRR 103 // Baud rate 9600 for 16 MHz clock

void setupSerial() {
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0); // Enable TX and RX
}

void sendSerialData(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
    UDR0 = data;                      // Send data
}

