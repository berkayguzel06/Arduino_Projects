int TIMER_START = 30;
int TIMER_SPEED = 1000;
int ANIMATION_SPEED = 200;

// Define global variables
int motionPin = 10;  // Pin connected to motion sensor
int ledPin = 11;     // Pin connected to LED
int displayPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pins connected to 7 segment display segments

int motionDetected = 0; // Variable to track motion detection

void setup() {
  Serial.begin(9600);
  pinMode(motionPin, INPUT);
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(displayPins[i], OUTPUT);
  }
}

void loop() {
  motionDetected = digitalRead(motionPin); // Check for motion
  // If motion detected, start countdown
  if (motionDetected == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    countdown();
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED if no motion
    displayHex(0,3); // Reset
  }
}

// Countdown function
void countdown() {
  int remainingTime = TIMER_START; // Set remaining time to initial value
  
  while (remainingTime >= 0) {
    displayTime(remainingTime);
    Serial.print(remainingTime);
    remainingTime--; // Decrement remaining time
  }
}

// Function to display remaining time on 7 segment display
void displayTime(int time) {
  if (time <= 15) {
    delay(TIMER_SPEED);
    // Display remaining time in hexadecimal from F to 0
    displayHex(time,0); // Without animation countdown
  } else {
    displayHex(0,1); // Animation
  }
}

// Function to display hexadecimal digit on 7 segment display
void displayHex(int digit, int anim) {
  // Define hexadecimal values for segments
  byte segments[] = {
    B11000000, // 0
    B11111001, // 1
    B10100100, // 2
    B10110000, // 3
    B10011001, // 4
    B10010010, // 5
    B10000010, // 6
    B11111000, // 7
    B10000000, // 8
    B10010000, // 9
    B10001000, // A
    B10000011, // B
    B11000110, // C
    B10100001, // D
    B10000110, // E
    B10001110  // F
  };
  byte animation[] = { // Animation bytes
    B11111110,
    B11111101,
    B11111011,
    B11110111,
    B11101111,
    B11011111,
  };
  byte reset = B11111111; // reset byte
  if(anim==0){ // Countdown according to value
    for (int i = 0; i < 8; i++){
      digitalWrite(displayPins[i], bitRead(segments[digit],i));
    }
  }
  else if(anim==1){ // Animation
    for(int j=0; j < 6; j++){
      for (int i = 0; i < 8; i++){
      	digitalWrite(displayPins[i], bitRead(animation[j],i));
       }
    	delay(ANIMATION_SPEED);
    }
  }
  else if(anim==3){ // Reset
    for (int i = 0; i < 8; i++){
      	digitalWrite(displayPins[i], bitRead(reset,i));
     }
  }
}