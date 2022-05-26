/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <std_msgs/UInt16.h>

int RedPin = 3;
int GreenPin = 5;
int BluePin = 6;

ros::NodeHandle  nh;

std_msgs::UInt16 toggle_msg;

void messageCb( const std_msgs::UInt16& toggle_msg){
  if (toggle_msg.data == 1) {
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 255);
  } else {
    analogWrite(RedPin, 0);
    analogWrite(BluePin, 0);
    analogWrite(GreenPin, 255);
  }
}

ros::Subscriber<std_msgs::UInt16> sub("toggle_led", &messageCb );

void setup()
{ 
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
