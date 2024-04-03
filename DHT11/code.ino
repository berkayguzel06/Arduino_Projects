#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 3 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

bool buttonState = LOW;
bool buttonPressed = false;
unsigned long buttonPressTime = 0;
const unsigned long longPressDuration = 10;

char LCD_LANGUAGE = 'E';
float h;
float t;
float f;

void setup() {
    dht.begin();
    lcd.init();
    lcd.backlight();
    pinMode(2, INPUT);
}

void loop() {
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = (t * 1.8) + 32;
    bool currentButtonState = digitalRead(2);
    if (currentButtonState != buttonState) {
        if (currentButtonState == HIGH) {
            buttonPressed = true;
            buttonPressTime = millis();
        } else {
            if (buttonPressed && (millis() - buttonPressTime >= longPressDuration)) {
                if (LCD_LANGUAGE == 'T') {
                    LCD_LANGUAGE = 'E';
                } else if (LCD_LANGUAGE == 'E') {
                    LCD_LANGUAGE = 'T';
                }
            }
            buttonPressed = false;
        }
        buttonState = currentButtonState;
    }

    if (LCD_LANGUAGE == 'E') {
        lcd.setCursor(0, 0);
        lcd.print("TEM(F): ");
        lcd.print(f);
        lcd.setCursor(14, 0);
        lcd.print("EN");
        lcd.setCursor(0, 1);
        lcd.print("HUM(%): ");
        lcd.print(h);
    } else if (LCD_LANGUAGE == 'T') {
        lcd.setCursor(0, 0);
        lcd.print("SIC(C): ");
        lcd.print(t);
        lcd.setCursor(14, 0);
        lcd.print("TR");
        lcd.setCursor(0, 1);
        lcd.print("NEM(%): ");
        lcd.print(h);
    }
}