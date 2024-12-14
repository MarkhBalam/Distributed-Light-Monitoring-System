// ATmega328P I2C (TWI) Register Definitions
#define TWBR (*(volatile uint8_t*)(0xB8))
#define TWSR (*(volatile uint8_t*)(0xB9))
#define TWAR (*(volatile uint8_t*)(0xBA))
#define TWDR (*(volatile uint8_t*)(0xBB))
#define TWCR (*(volatile uint8_t*)(0xBC))

// ATmega328P USART Register Definitions
#define UDR0 (*(volatile uint8_t*)(0xC6))
#define UCSR0A (*(volatile uint8_t*)(0xC0))
#define UCSR0B (*(volatile uint8_t*)(0xC1))
#define UBRR0H (*(volatile uint8_t*)(0xC5))
#define UBRR0L (*(volatile uint8_t*)(0xC4))

// LCD Port Definitions
#define LCD_DDR DDRD
#define LCD_PORT PORTD
#define LCD_RS PD0
#define LCD_EN PD1

// I2C Board Addresses
#define BOARD_A 8
#define BOARD_B 9
#define BOARD_C 10

// TWI Status Codes
#define TW_START 0x08
#define TW_MT_SLA_W 0x18
#define TW_MT_DATA 0x28

void i2cInit(void) {
    TWBR = ((F_CPU / 100000UL) - 16) / 2; // Set bit rate for 100kHz
    TWSR = 0; // No prescaler
    TWCR = (1 << TWEN); // Enable TWI
}
void i2cStart(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}
void i2cStop(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
void i2cWrite(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}
uint8_t i2cRead(uint8_t ack) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}
void lcdCommand(uint8_t cmd) {
    LCD_PORT = cmd;
    LCD_PORT &= ~(1 << LCD_RS);
    LCD_PORT |= (1 << LCD_EN);
    _delay_ms(1);
    LCD_PORT &= ~(1 << LCD_EN);
}
void lcdData(uint8_t data) {
    LCD_PORT = data;
    LCD_PORT |= (1 << LCD_RS);
    LCD_PORT |= (1 << LCD_EN);
    _delay_ms(1);
    LCD_PORT &= ~(1 << LCD_EN);
}
void setup(void) {
    // Initialize I2C
    i2cInit();
    
    // Initialize LCD
    LCD_DDR = 0xFF;
    _delay_ms(15);
    lcdCommand(0x38);
    lcdCommand(0x0C);
    lcdCommand(0x01);
    _delay_ms(2);
    
    // Initialize UART
    UBRR0H = (F_CPU / 16 / 9600 - 1) >> 8;
    UBRR0L = (F_CPU / 16 / 9600 - 1);
    UCSR0B = (1 << TXEN0);
}
void loop(void) {
    readSensor(BOARD_A);
    _delay_ms(1000);
    readSensor(BOARD_B);
    _delay_ms(1000);
    readSensor(BOARD_C);
    _delay_ms(1000);
}
void readSensor(uint8_t address) {
    i2cStart();
    i2cWrite((address << 1) | 0x01); // Read mode
    
    char data[16];
    for (uint8_t i = 0; i < 15; i++) {
        data[i] = i2cRead(1); // Read with ACK
    }
    data[15] = i2cRead(0); // Read last byte with NACK
    i2cStop();

    // Display on LCD
    lcdCommand(0x01);
    for (uint8_t i = 0; i < 16; i++) {
        lcdData(data[i]);
    }
}
