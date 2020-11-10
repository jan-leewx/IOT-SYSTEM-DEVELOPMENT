#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>
#define soundbuzzer 10

rgb_lcd lcd;

const int colorR = 24;
const int colorG = 123;
const int colorB = 205;

const int trigPin = 8;
const int echoPin = 9;
int red = 11;
int yellow = 12;
int green = 13;

long duration;
int distance;
int sendv;

void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(red , OUTPUT);
  pinMode(yellow , OUTPUT);
  pinMode(green , OUTPUT);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.print("Distance");
  pinMode(soundbuzzer, OUTPUT);
}

void loop()
{
  duration=distance=0; 
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //calculate the time taken for the wave to return
  distance = (duration/2) / 2.91; //formulae to calculate the distance using time taken
  sendv = distance;
  Serial.println(sendv);

  if (distance >1000)//send the value to python only if it ranhes from 0-20 cm
  {    
    digitalWrite(red , LOW);
    digitalWrite(yellow , LOW);
    digitalWrite(green , HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance (mm): ");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    delay(100);
  }
  else if (distance > 500 && distance < 999)//send the value to python only if it ranhes from 0-20 cm
  {    
    digitalWrite(red , LOW);
    digitalWrite(yellow , HIGH);
    digitalWrite(green , LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance (mm): ");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    delay(100);
  }
  else if (distance > 150 && distance < 499)//send the value to python only if it ranhes from 0-20 cm
  {    
    digitalWrite(red , LOW);
    digitalWrite(yellow , LOW);
    digitalWrite(green , LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance (mm): ");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    delay(100);
      digitalWrite(red , LOW);
      delay(100);
      digitalWrite(red , HIGH);
      tone(soundbuzzer, 999, 100); 
     delay(100);
  }
  else
  {
    digitalWrite(red , HIGH);
    digitalWrite(yellow , LOW);
    digitalWrite(green , LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance (mm): ");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    tone(soundbuzzer, 999);
    delay(100);    
  }
  delay(200);
}
 
