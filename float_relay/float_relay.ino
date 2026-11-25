int const relay_pin = 7;
int const switch_pin = 3;

void setup() {
  pinMode(relay_pin, OUTPUT);
  pinMode(switch_pin, INPUT_PULLUP); 
}

void loop() {
  int switchState = digitalRead(switch_pin);

  if (switchState == LOW) {   
    digitalWrite(relay_pin, HIGH);
  } else {                    
    digitalWrite(relay_pin, LOW);
  }
}
