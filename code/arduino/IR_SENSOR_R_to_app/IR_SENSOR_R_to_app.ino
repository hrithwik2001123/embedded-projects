int MIF = 2;
int MIR = 3;
int MIF1 = 4;
int MIR1 = 5;
int IR = 6; 
int sensorValue = HIGH;
void setup()
{
  Serial.begin(9600);
  pinMode(IR, INPUT);
  pinMode(MIF, OUTPUT);
  pinMode(MIR, OUTPUT);
  pinMode(MIF1, OUTPUT);
  pinMode(MIR1, OUTPUT);
}

void loop()
{
   sensorValue = digitalRead(IR);

//   Send IR value to app
 

  if (sensorValue == LOW) {  
    digitalWrite(MIF, LOW);
    digitalWrite(MIR, LOW);
    digitalWrite(MIF1, LOW);
    digitalWrite(MIR1, LOW);
    Serial.println("IR Value: obstacle");
    return; 
  } 

  if (Serial.available()) {
    char msg = Serial.read();
    
    if (msg == 'F') { // Forward
      digitalWrite(MIF, HIGH);
      digitalWrite(MIR, LOW);
      digitalWrite(MIF1, HIGH);
      digitalWrite(MIR1, LOW);
      delay(500);
    }
    else if (msg == 'B') { // Backward
      digitalWrite(MIF, LOW);
      digitalWrite(MIR, HIGH);
      digitalWrite(MIF1, LOW);
      digitalWrite(MIR1, HIGH);
      delay(500);
    }
    else if (msg == 'C') { // Stop command
      digitalWrite(MIF, LOW);
      digitalWrite(MIR, LOW);
      digitalWrite(MIF1, LOW);
      digitalWrite(MIR1, LOW);
      delay(500);
    }
  }
}
