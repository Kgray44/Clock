/*************************************************************
File Name: Example2_TimeTemp.ino
Processor/Platform: Arduino (Atmega16 tested)
Development Environment: Arduino 2.0.3

Download latest code here:
https://github.com/Kgray44/Clock

Driveway Gates code meant to be used alongside the tutorial found here:
https://www.hackster.io/k-gray/diy-clock-kit-338901

Copyright 2022 K Gray

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Liscense found here:
https://opensource.org/licenses/MIT


*************************************************************
Summary
Press "B1" to change between displaying the current time or the temperature.
*************************************************************/

#include "Clock.hpp"

SevSeg sevseg;
dht DHT;	
uRTCLib rtc(0x68);

bool mode=false;

float temp=0;

Clock clock(&sevseg, &DHT, &rtc);

void setup(){
  clock.begin();
  Serial.begin(9600);
}

void loop(){
  if (digitalRead(Button1) == LOW){
    mode = !mode;
    delay(500);
  }

  if (millis() - lastmillis > 2000){
    temp = clock.temperature();
    lastmillis = millis();
  }

  if (!mode){
    clock.displayint(clock.gettime());
  }
  else {
    clock.displayfloat(temp);
  }
  clock.rgb(0,clock.potentiometer(),0);
  clock.refresh();
}
