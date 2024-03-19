const int SOUND_DURATION = 500;
const int SILENCE_DURATION = 50;
const int MELODY[] = {1, 1, 5, 5, 6, 6, 5, 0, 4, 4, 3, 3, 2, 2, 1}; // Do, Do, Sol, Sol, La, La, Sol, No sound, Fa, Fa, Mi, Mi, Re, Re, Do
const int MELODY2[] = {2,2,3,1, 2,2,3,1, 2,2,3,1,4,4, 2,2,3,0, 1,2,2,2,0, 1,1,2,2,2,2,4,4};
const int BUZZER_PIN = 8;
const int BUTTON_PIN = 7;
const int NOTES[] = {0, 262, 294, 330, 349, 392, 440, 494}; // Frequencies of Do, Re, Mi, Fa, Sol, La, Si
const int size = sizeof(MELODY) / sizeof(MELODY[0]);


void playMelody() {
  for (int i = 0; i < size; i++) {
    if (MELODY[i] == 0) { // If it's a rest
      noTone(BUZZER_PIN);
      delay(SOUND_DURATION);   
    } else {
      tone(BUZZER_PIN, NOTES[MELODY[i]]); 
      delay(SOUND_DURATION);
    }
    noTone(BUZZER_PIN);
    delay(SILENCE_DURATION);
  }
  
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN)) {
    playMelody();    
  }
}