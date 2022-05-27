char receivedChar;
boolean newData = false;

int RedPin = 3;
int GreenPin = 5;
int BluePin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 255);
  recvOneChar();
  showNewData();
}


void recvOneChar() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    newData = true;
  }
}

void showNewData() {
  if (newData== true) {
    Serial.println(receivedChar);
    analogWrite(RedPin, 0);
    analogWrite(BluePin, 0);
    analogWrite(GreenPin, 255);
    delay(1000);
    newData= false;
  }
}
