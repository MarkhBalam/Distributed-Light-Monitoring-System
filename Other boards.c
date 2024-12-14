// ATmega328P Register Definitions
#define DDRB (*(volatile uint8_t*)(0x24))
#define PORTB (*(volatile uint8_t*)(0x25))
#define PINB (*(volatile uint8_t*)(0x23))
#define DDRC (*(volatile uint8_t*)(0x27))
#define PORTC (*(volatile uint8_t*)(0x28))
#define ADMUX (*(volatile uint8_t*)(0x7C))
#define ADCSRA (*(volatile uint8_t*)(0x7A))
#define ADCH (*(volatile uint8_t*)(0x79))
#define ADCL (*(volatile uint8_t*)(0x78))
#define TWAR (*(volatile uint8_t*)(0xBA))
#define TWDR (*(volatile uint8_t*)(0xBB))
#define TWCR (*(volatile uint8_t*)(0xBC))

#define DEVICE_ADDRESS 10 // Change for different boards
#define LDR_PIN 0 // ADC0
#define BUTTON_PIN 3 // PB3
#define LED_PIN 2 // PB2

uint16_t lightValue = 0;
uint8_t dayMode = 1;
uint8_t lastButtonState = 1;

void initADC(void) {
    ADMUX = (1 << REFS0); // AVCC reference
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler = 64
}
uint16_t readADC(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | channel;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return (ADCL | (ADCH << 8));
}
void i2cInit(void) {
    TWAR = (DEVICE_ADDRESS << 1);
    TWCR = (1 << TWEN) | (1 << TWEA);
}
void setup(void) {
    // Configure pins
    DDRB |= (1 << LED_PIN); // LED as output
    DDRB &= ~(1 << BUTTON_PIN); // Button as input
    PORTB |= (1 << BUTTON_PIN); // Enable pull-up
    initADC();
    i2cInit();
}
void loop(void) {
    // Read LDR
    lightValue = readADC(LDR_PIN);
    // Check button
    uint8_t buttonState = (PINB & (1 << BUTTON_PIN)) >> BUTTON_PIN;
    if (!buttonState && lastButtonState) {
        dayMode = !dayMode;
        _delay_ms(200);
    }
    lastButtonState = buttonState;
    _delay_ms(1000);
}
ISR(TWI_vect) {
    PORTB |= (1 << LED_PIN); // LED ON
    char buffer[16];
    sprintf(buffer, "%d,%s", lightValue, dayMode ? "Day" : "Night");

    uint8_t i = 0;
    while (buffer[i] && i < 16) {
        TWDR = buffer[i++];
        TWCR = (1 << TWEN) | (1 << TWINT);
        while (!(TWCR & (1 << TWINT)));
    }
    PORTB &= ~(1 << LED_PIN); // LED OFF
}
