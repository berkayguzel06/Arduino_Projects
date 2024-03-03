// C++ code
//
int VALUE = 0;
int INCREMENT_VALUE = 7;
int WAIT_TIME = 500;


void setup()
{
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void checkLed(int pinNum, bool status){
  if(pinNum==0){
    digitalWrite(1,status);
  }else if(pinNum==1){
    digitalWrite(2, status);
  }else if(pinNum==2){
    digitalWrite(3,status);
  }else if(pinNum==3){
    digitalWrite(4,status);
  }else if(pinNum==4){
    digitalWrite(5,status);
  }
}

void loop()
{
  VALUE += INCREMENT_VALUE;
  if(VALUE>32){
    VALUE = VALUE-32;
  }else if(VALUE==32){
    VALUE = 1;
  }
  for(int i=7; i>=0; i--)
  {
    bool m = bitRead(VALUE, i); 
    checkLed(i,m);
  }
  delay(WAIT_TIME);
}