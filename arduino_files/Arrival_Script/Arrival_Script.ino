#include <Servo.h>
#include <FastLED.h>

/*
 * CSE 176A/276D Arrival Script
 *
 * Triggers LED color change and starts vending mechanism when a character 
 * is read from the Serial Monitor. A character is only sent to the Serial 
 * Monitor from the main script (start_nav.sh) when the robot successfully
 * reaches its goal.  
 */

char receivedChar; // saving character read from Serial monitor
boolean dataReceived = false; // flag to signal if a character was read
Servo lift;

#define NUM_LEDS 60
#define DATA_PIN 9
#define BRIGHTNESS 80
CRGB leds[NUM_LEDS];


void setup() {
 
  // setup LED strip
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness( BRIGHTNESS);

  Serial.begin(9600);
}

void loop() {

  // LEDs are blue to indicate delivery mode
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  
  // call helper functions to read from Serial Monitor and
  // trigger LED color change and vending mechanism
  readFromSerial();
  ledAndVending();
}


/* 
 * Function to read from the Serial Monitor and 
 * toggle dataReceived flag 
 */
void readFromSerial() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    dataReceived = true;
  }
}


/* 
 * Function to check dataReceived flag and if it's true, then 
 * change LED color to green and trigger vending mechanism
 */
void ledAndVending() {
  if (dataReceived == true) {
    Serial.println(receivedChar);

    // turn LED green to indicate arrival (label says Red due to GRB ordering)
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
    }
    FastLED.show();

    // trigger vending mechanism (elevator goes up, pauses, elevator goes down)
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
    
    // toggle dataReceived flag
    dataReceived = false;
  }
}
