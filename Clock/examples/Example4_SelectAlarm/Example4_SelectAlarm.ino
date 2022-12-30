/*************************************************************
File Name: Example3_SelectAlarm.ino
Processor/Platform: Arduino (Atmega16 tested)
Development Environment: Arduino 2.0.3

Download latest code here:
https://github.com/Kgray44/Clock

Clock code meant to be used alongside the tutorial found here:
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
Sets alarms for different times according to the location of the slide switch
*************************************************************/

#include "Clock.hpp"

SevSeg sevseg;
dht DHT;	
uRTCLib rtc(0x68);

Clock clock(&sevseg, &DHT, &rtc);

void setup(){
  clock.begin();
}

void loop(){
  if (clock.slider(1)){
    clock.setalarm(1,5,0,0,6);//Set a alarm for 5:0:0 AM on Friday
    clock.setalarm(2,8,30,0,6,true);//Set a alarm for 8:30:0 PM on Friday
  }
  else if (clock.slider(2)){
    clock.setalarm(1,12,30,0,6);//Set a alarm for 12:30:0 AM on Friday
  }
  else if (clock.slider(3)){
    clock.setalarm(1,2,45,0,6,true);//Set a alarm for 2:45:0 PM on Friday
  }
  else if (clock.slider(4)){
    clock.setalarm(1,4,10,7,6,true);//Set a alarm for 4:10:07 PM on Friday
  }
  clock.displayint(clock.gettime());
  clock.rgb(0,clock.potentiometer(),0);
  clock.checkalarm();
  clock.doalarm();
  clock.refresh();
}
