/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  

  This example shows how to send values to the Blynk App,
  when there is a widget, attached to the Virtual Pin and it
  is set to some frequency

  Project setup in the app:
    Value Display widget attached to V5. Set any reading
    frequency (i.e. 1 second)
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT SwSerial

#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include <Adafruit_MLX90614.h>
#include<string.h>
String temperature;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "SIJw0kbNRtqogbBxebn8fCXLbT6_SM44";

// Use Virtual pin 5 for uptime display
#define PIN_UPTIME V5

// This function tells Arduino what to do if there is a Widget
// which is requesting data for Virtual Pin (5)
BLYNK_READ(PIN_UPTIME)
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
  
  temperature = String(mlx.readObjectTempC(), 1);
  if(digitalRead(2)==0){
  Blynk.virtualWrite(PIN_UPTIME,temperature);
  }
  if(digitalRead(2)==1){
  Blynk.virtualWrite(PIN_UPTIME,0);
  }
  }

void setup()
{
  // Debug console
  SwSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  mlx.begin();
  Blynk.begin(Serial, auth);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop()
{ int temperature = (mlx.readObjectTempC());
  Blynk.run();
  if(digitalRead(2)==0 && temperature>=25  ){
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
  }
  if(digitalRead(2)==1){
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  if(digitalRead(2)==0 && temperature<25){
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  delay(2000);
}
