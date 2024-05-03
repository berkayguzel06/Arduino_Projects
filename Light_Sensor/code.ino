int LED_ACTIVATION_VALUE = 500;   // Median point for light activation
int SERIAL_OUTPUT_FREQUENCY = 500; // Output frequency in milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);   // LED pin
  pinMode(A0, INPUT);   // Light sensor pin
}

void loop() {
  int value = analogRead(A0); // Read the light sensor value

  // Check if the sensor value is below the median point
  if (value < LED_ACTIVATION_VALUE) {
    digitalWrite(3, HIGH);   // Turn on LED
    Serial.print("LIGHT SENSOR: ");
    Serial.println(value);
    Serial.println("LED STATUS: ON");
  } else {
    digitalWrite(3, LOW);    // Turn off LED
    Serial.print("LIGHT SENSOR: ");
    Serial.println(value);
    Serial.println("LED STATUS: OFF");
  }

  // Delay before next output
  delay(SERIAL_OUTPUT_FREQUENCY);
}
