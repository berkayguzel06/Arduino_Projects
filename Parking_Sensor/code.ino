#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define I2C LCD Address
#define I2C_ADDR    0x27

// Initialize the LCD
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

// Define sensor and actuator pins
#define TRIG_PIN 2
#define ECHO_PIN 5
#define BUZZER_PIN 4
#define LED_PIN 3

// Define constants
const int BUZZER_LED_DURATION_MAX = 1000;
const int BUZZER_LED_DURATION_MIN = 10;
const int DISTANCE_MAX = 50;
const int DISTANCE_MIN = 5;
const int UPDATE_DURATION_BUZZER = 100;
const int UPDATE_DURATION_LCD = 100;

// Define global variables
int CURRENT_DISTANCE = 0;
int CURRENT_DURATION = 0;
unsigned long previousMillisBuzzer = 0;
unsigned long previousMillisLCD = 0;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial LCD message
  lcd.setCursor(0, 0);
  lcd.print("DISTANCE: ");
  lcd.setCursor(0, 1);
  lcd.print("DURATION: ");
}

void loop() {
  unsigned long currentMillis = millis();

  // Mesafeyi ölçme
  CURRENT_DISTANCE = readUltrasonicDistance();
  Serial.print("Distance: ");
  Serial.println(CURRENT_DISTANCE);

  // Süreyi hesaplama
  CURRENT_DURATION = calculateDuration(CURRENT_DISTANCE);

  // Buzzer ve LED kontrolü
  if (currentMillis - previousMillisBuzzer >= UPDATE_DURATION_BUZZER) {
    previousMillisBuzzer = currentMillis;
    
    if (CURRENT_DISTANCE <= DISTANCE_MIN) {
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    } else if (CURRENT_DISTANCE > DISTANCE_MAX) {
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    } else {
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
      delay(CURRENT_DURATION);
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
  }

  // LCD güncellemesi
  if (currentMillis - previousMillisLCD >= UPDATE_DURATION_LCD) {
    previousMillisLCD = currentMillis;
    
    lcd.setCursor(0, 0);
    lcd.print("DISTANCE: ");
    lcd.print(CURRENT_DISTANCE);
    lcd.print("cm   ");
    
    lcd.setCursor(0, 1);
    lcd.print("DURATION: ");
    lcd.print(CURRENT_DURATION);
    lcd.print("ms   ");
  }
}

int readUltrasonicDistance() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read echo pulse
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate distance in cm
  int distance = duration * 0.034 / 2;
  
  return distance;
}



int calculateDuration(int distance) {
  if (distance < DISTANCE_MIN) {
    return BUZZER_LED_DURATION_MAX;
  } else if (distance > DISTANCE_MAX) {
    return 0;
  } else {
    int duration = ((float)(distance - DISTANCE_MIN) / (DISTANCE_MAX - DISTANCE_MIN)) * 
                   (BUZZER_LED_DURATION_MAX - BUZZER_LED_DURATION_MIN) + 
                   BUZZER_LED_DURATION_MIN;
    return duration;
  }
}

void updateLCD(int distance, int duration) {

  lcd.setCursor(10, 0);
  lcd.print("    ");
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.setCursor(14, 0);
  lcd.print("cm");
  
  lcd.setCursor(10, 1);
  lcd.print("    ");
  lcd.setCursor(10, 1);
  lcd.print(duration);
  lcd.setCursor(14, 1);
  lcd.print("ms");
  
}