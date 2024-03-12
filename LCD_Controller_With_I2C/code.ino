#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const bool SCROLL_FLAG = true; // Flag to enable scrolling
const int SCROLL_WAIT = 500;   // Delay between scrolling steps
char SCROLL_DIRECTION = 'R';   // Direction of scrolling ('L' for left, 'R' for right)
char LCD_ROW_1[] = "This text is for row 0 and longer than 16 characters."; // First row text
char LCD_ROW_2[] = "ABCD EFGH"; // Second row text
char result[17];  // The size of the array is desiredLength + 1
int currentCharIndex = 0; // Current index for scrolling on row 1
int currentCharIndex2 = 0; // Current index for scrolling on row 2
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t cTr[8] = {
      0b00000,
      0b01110,
      0b10001,
      0b10000,
      0b10000,
      0b10001,
      0b01110,
      0b00100
    };
    uint8_t GTr[8] = {
      0b01110,
      0b00000,
      0b01110,
      0b10001,
      0b10000,
      0b10111,
      0b10001,
      0b01111
    };
    uint8_t STr[8] = {
      0b00000,
      0b00000,
      0b01110,
      0b10000,
      0b01110,
      0b00001,
      0b01110,
      0b00100
    };
    uint8_t _gTr[8] = {
      0b01110,
      0b00000,
      0b01111,
      0b10001,
      0b10001,
      0b01111,
      0b00001,
      0b01110
    };
    uint8_t ITr[8] = { 
      0b00100,
      0b00000,
      0b01110,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b01110
    };
    uint8_t _iTr[8] = { 
      0b00000,
      0b00000,
      0b00000,
      0b01100,
      0b00100,
      0b00100,
      0b00100,
      0b01110
    };
    

// Function to add spaces to a string until it reaches the desired length
char* spaces(const char *str, int desiredLength) {
    int currentLength = strlen(str);
    
    // If the length of the string is greater than or equal to the desired length, copy and return
    if (currentLength >= desiredLength) {
        char *result = (char *)malloc(currentLength + 1);
        if (result == NULL) {
            Serial.println("Memory error!");
            return NULL;
        }
        strcpy(result, str);
        return result;
    }
    
    // Create a new string and fill it with spaces to reach the desired length
    char *result = (char *)malloc(desiredLength + 1);
    if (result == NULL) {
        Serial.println("Memory error!");
        return NULL;
    }
    strcpy(result, str); // Copy the original string
    for (int i = currentLength; i < desiredLength; i++) {
        result[i] = ' '; // Add spaces
    }
    result[desiredLength] = '\0'; // Terminate the string
    return result;
}

void setup() { 
  Serial.begin(9600);
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on backlight
 

  lcd.createChar(0, cTr);
  lcd.createChar(1, GTr);
  lcd.createChar(2, STr);
  lcd.createChar(3, _gTr);
  lcd.createChar(4, ITr);
  lcd.createChar(5, _iTr);
  
  lcd.setCursor(0, 0);
  
  lcd.write((byte)0);
  lcd.write((byte)1);
  lcd.write((byte)2);
  lcd.write((byte)3);
  lcd.write((byte)4);
  lcd.write((byte)5);

 
  delay(4000);
  // Check if the length of LCD_ROW_2 is less than 16 characters
  if(strlen(LCD_ROW_2) < 15){
    // Add spaces to LCD_ROW_2 to make it 16 characters long
    char *temp_result = spaces(LCD_ROW_2, 16);
    if(temp_result != NULL) {
      strcpy(result, temp_result);
      free(temp_result); // Free the memory allocated to temp_result to prevent memory leak
    }
  }
}

void loop() {
  // Check if scrolling is enabled
  if(SCROLL_FLAG){
    lcd.clear(); // Clear the LCD screen
    lcd.setCursor(0, 0);
    // Scroll through characters on row 1
    for(int i = 0; i < 16; i++) {
      lcd.print(LCD_ROW_1[(currentCharIndex + i) % strlen(LCD_ROW_1)]);
    }
    
    // Update the index for scrolling on row 1
    if (SCROLL_DIRECTION == 'L') {
      currentCharIndex = (currentCharIndex + 1) % strlen(LCD_ROW_1);
    } else if (SCROLL_DIRECTION == 'R') {
      currentCharIndex = (currentCharIndex - 1 + strlen(LCD_ROW_1)) % strlen(LCD_ROW_1);
    }

    lcd.setCursor(0, 1);
    
    // Scroll through characters on row 2
    for(int i = 0; i < 16; i++) {
      lcd.print(result[(currentCharIndex2 + i) % strlen(result)]);
    }
    
    // Update the index for scrolling on row 2
    if (SCROLL_DIRECTION == 'L') {
      currentCharIndex2 = (currentCharIndex2 + 1) % strlen(result);
    } else if (SCROLL_DIRECTION == 'R') {
      currentCharIndex2 = (currentCharIndex2 - 1 + strlen(result)) % strlen(result);
    }
    delay(SCROLL_WAIT); // Delay before the next scrolling step
  }
}