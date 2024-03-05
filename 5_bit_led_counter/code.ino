// C code
//
int VALUE = 0; // Current value
int INCREMENT_VALUE = 1;
int WAIT_TIME = 500;


void setup()
{
  // Pin Setups
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
// Checks Leds according to given Led number and status
void checkLed(int pinNum, bool status){
  if(pinNum==0){
    digitalWrite(2,status);
  }else if(pinNum==1){
    digitalWrite(3, status);
  }else if(pinNum==2){
    digitalWrite(4,status);
  }else if(pinNum==3){
    digitalWrite(5,status);
  }else if(pinNum==4){
    digitalWrite(6,status);
  }
}

// Bit read function takes the value and makes AND operation
// 0 is the LSB if after operation value is 1 return true otherwise return false
bool readBit(int value, int bitIndex) {
    return (value & (1 << bitIndex)) != 0;
}

void loop()
{
  // First increment current value
  VALUE += INCREMENT_VALUE;
  // Check if the value equal or bigger than 32
  if(VALUE>32){
    VALUE = VALUE-32;
  }else if(VALUE==32){
    VALUE = 1;
  }
  // Check and Read bits of the value
  for(int i=4; i>=0; i--)
  {
    // If the bit is 1 return true
    bool m = readBit(VALUE, i); 
    // Send pin number and status
    checkLed(i,m);
  }
  delay(WAIT_TIME);
}