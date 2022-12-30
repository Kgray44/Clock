/*************************************************************
File Name: Example1_Basic.ino
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
Displays the current time.
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
  clock.displayint(clock.gettime());
  clock.rgb(0,clock.potentiometer(),0);
  clock.refresh();
}
