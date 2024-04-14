#include <Servo.h>

Servo Servo1;
Servo Servo2;

//pins
int servoPin1 = 7;
int clk1 = 6;
int dt1 = 5;

int servoPin2 = 10;
int clk2 = 9;
int dt2 = 8;

//rotary encoder
int degree1 = 0; 
int current1;
int last1;
int start1 = 0;
int end1 = 80;
int increment1 = 10;

int degree2 = 0; 
int current2;
int last2;
int start2 = 0;
int end2 = 40;
int increment2 = 10;

void setup() {
  //attach servos, setup inputs from rotary encoder
  Serial.begin (9600);
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);

  pinMode (clk1, INPUT);
  pinMode (dt1, INPUT);

  pinMode (clk2, INPUT);
  pinMode (dt2, INPUT);

  //reset position for servos
  degree1 = start1;  
  Servo1.write(degree1);
  last1 = digitalRead(clk1);

  degree2 = start1;  
  Servo2.write(degree2);
  last2 = digitalRead(clk2);  
}


void loop() {
  // learned and understood content from https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/
  current1 = digitalRead(clk1); // Reads the "current" state of the clk
  //if its changed from the last time, check with dt pin to see if its turned clockwise or counter clockwise
  if (current1 != last1){     
    if (digitalRead(dt1) != current1) { 
      degree1 -= increment1;
      Servo1.write(degree1);
    } else {
      degree1 += increment1;
      Servo1.write(degree1);
    }
    
    //if the degree is less than the minimum, set degree to minimum
    if (degree1 <= start1) {
      degree1 = start1;  
      Servo1.write(degree1);
      //if the degree is more than the maximum, set degree to maximum
    } else if (degree1 >= end1) {
      degree1 = end1;  
      Servo1.write(degree1);
    }
    //just used for debugging. not visible unless youre connected to the arduino
     Serial.println("DEGREE1");
     Serial.println(degree1);
   }
   //set the lsat variable to be the current so that you can compare to the last position 
   last1 = current1;



  // same thing, different servo and rotary encoder
  current2 = digitalRead(clk2); 
  if (current2 != last2){     
    if (digitalRead(dt2) != current2) { 
      degree2 += increment2;
      Servo2.write(degree2);
    } else {
      degree2 -= increment2;
      Servo2.write(degree2);
    }
    
    if (degree2 <= start2) {
      degree2 = start2;  
      Servo2.write(degree2);
    } else if (degree2 >= end2) {
      degree2 = end2;  
      Servo2.write(degree2);
    }
     Serial.println("DEGREE2");
     Serial.println(degree2);
   } 
   last2 = current2;
}