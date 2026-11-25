
//forwarde
int MIF = 4;  // GPIO4 = D2 on NodeMCU
int MIR = 5;  // GPIO5 = D1 on NodeMCU
int MIF1 = 0;  // GPIO0 = D3 on NodeMCU
int MIR1 = 2;  // GPIO2 = D4 on NodeMCU

// backward
int MIF2 = 14;  // GPIO14 = D5 on NodeMCU
int MIR2 = 12;  // GPIO12 = D6 on NodeMCU
int MIF3 = 13;  // GPIO13 = D7 on NodeMCU
int MIR3 = 15;  // GPIO15 = D8 on NodeMCU

void setup() {
  pinMode(MIF, OUTPUT);
  pinMode(MIR, OUTPUT);
  pinMode(MIF1, OUTPUT);
  pinMode(MIR1, OUTPUT);
  pinMode(MIF2, OUTPUT);
  pinMode(MIR2, OUTPUT);
  pinMode(MIF3, OUTPUT);
  pinMode(MIR3
  , OUTPUT);
}

void loop() {
  // Forward
  digitalWrite(MIF, HIGH);
  digitalWrite(MIR, LOW);
  digitalWrite(MIF1, HIGH);
  digitalWrite(MIR1, LOW);
// backward
  digitalWrite(MIF2, LOW);
  digitalWrite(MIR2, HIGH);
  digitalWrite(MIF3, LOW);
  digitalWrite(MIR3, HIGH);
  delay(500);
}
