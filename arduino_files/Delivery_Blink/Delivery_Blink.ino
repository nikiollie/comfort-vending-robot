#include <Servo.h>
#include <FastLED.h>

char receivedChar;
boolean newData = false;
Servo lift;

#define NUM_LEDS 60
#define DATA_PIN 9
#define BRIGHTNESS 80
CRGB leds[NUM_LEDS];

//int RedPin = 3;
//int GreenPin = 5;
//int BluePin = 6;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness( BRIGHTNESS);
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
      leds[i] = CRGB::Red;
    }
    FastLED.show();

    lift.attach(10);
    delay(2000);
    lift.write(60);
    delay(2500);
    lift.write(90);
    delay(7000);
    lift.write(120);
    delay(2500);
    lift.write(90);
    lift.detach();
    
    newData= false;
  }
}
