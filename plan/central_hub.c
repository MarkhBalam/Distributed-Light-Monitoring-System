#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD (Address, Columns, Rows)

void setup() {
    Serial.begin(9600); // Initialize serial communication
    lcd.init();
    lcd.backlight();
    lcd.print("Light Data:");
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n'); // Read incoming data
        lcd.setCursor(0, 1); // Display on second line of LCD
        lcd.print(data); // Show received light data
    }
}
