#include <FastLED.h>

char receivedChar;
boolean newData = false;

#define NUM_LEDS 60
#define DATA_PIN 9
CRGB leds[NUM_LEDS];

//int RedPin = 3;
//int GreenPin = 5;
//int BluePin = 6;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

//  pinMode(RedPin, OUTPUT);
//  pinMode(GreenPin, OUTPUT);
//  pinMode(BluePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  analogWrite(RedPin, 0);
//  analogWrite(GreenPin, 0);
//  analogWrite(BluePin, 255);

  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  
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
//    analogWrite(RedPin, 0);
//    analogWrite(BluePin, 0);
//    analogWrite(GreenPin, 255);

    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
    
    delay(1000);
    newData= false;
  }
}
