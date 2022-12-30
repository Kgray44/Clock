File Name: readme.md

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
Functions list
*************************************************************

void begin(int brightness=100)

void refresh()

float temperature(bool f=true)

float humidity()

void setalarm(int alarmnumber=1,int hour=5,int minute=0,int second=0,int day=1,bool pm=false,bool armed=true)

int gettime()

int gethour()

void checkalarm()

void doalarm(int soundseq=1, int count=15)

int potentiometer(int mapped=true)

int ldr(int mapped=true)

void beep(int t=200)

void rgb(int r, int g, int b)

void displayint(int number=10000, int decimalplace=2)

void displayfloat(float number=10000, int decimalplace=1)

void displaychar(char *stringd="NA")

void displayclear()


*************************************************************
Syntax / Definitions
*************************************************************

void begin(int brightness=100)

*Starts the clock; takes a integer for brightness (should stay on default; 100)*

void refresh()

*Required in `void loop()`.  Refreshes the display to make it work*

float temperature(bool f=true)

*Returns a `float` value of the current temperature.  Can only be read once every 2 seconds.  Takes a `bool` value for F vs. C (default is F)*

float humidity()

*Returns a `float` value of the current humidity.  Can only be read once every 2 seconds.*

void setalarm(int alarmnumber=1,int hour=5,int minute=0,int second=0,int day=1,bool pm=false,bool armed=true)

*Sets a alarm.  Takes multiple values.*

*The first value (`alarmnumber`) is a `int` value and is the alarm number that you are setting; max of 10 alarms.*

*Second value (`hour`) is a `int`.  It is the alarm hour.*

*Third value (`minute`) is a `int`.  It is the alarm minute.*

*Fourth value (`second`) is a `int`.  It is the alarm second.*

*Fifth value (`day`) is a `int`.  It is the alarm day.  This value can be from 1 to 7.  The number correlates to the day of the week; 1=Sunday, 7=Saturday.*

*Sixth value (`pm`) is a `bool`.  It is the alarm AM/PM.  If this value is `true`, the alarm will be in the afternoon; if this value is `false`, the alarm will be in the morning.*

*Seventh value (`armed`) is a `bool`.  It is the alarm armed value.  If this value is `true`, the alarm will be activated; if this value is `false`, the alarm will be deactivated.*


int gettime()

*Returns a `int` value of the current time that can be displayed; includes the hour and the minute.  Works with 12-hour time.*

int gethour()

*Returns a `int` value of the current hour.  Works with 12-hour time.*

void checkalarm()

*Checks if any alarms have gone off.*

void doalarm(int soundseq=1, int count=15)

*If the `checkalarm()` function is true, the `doalarm()` function sounds the alarm.  This function takes two values.  The first is a `int` that specifies the alarm sequence and can be from 1 to 4.  The second is the amount of times it buzzes.*

int potentiometer(int mapped=true)

*Returns a `int` value from reading the potentiometer.  Takes one `bool` value.  If this value is true, the output will be mapped from 0 - 255, else the value will be from 0 - 1023.*

int ldr(int mapped=true)

*Returns a `int` value from reading the LDR.  Takes one `bool` value.  If this value is true, the output will be mapped from 0 - 255, else the value will be from 0 - 1023.*

void beep(int t=200)

*Beeps the buzzer.  Takes one `int` value for specifying how long the buzzer is on.*

void rgb(int r, int g, int b)

*Sets the RGB LEDs.  Takes three `int` values for Red, Green, and Blue.  These values can be from 0 (off) to 255 (on).*

void displayint(int number=10000, int decimalplace=2)

*Displays a `int` value.  Takes two `int` values.  The first is the `int` being displayed, and the second is where the decimal place is. For example, "152".*

void displayfloat(float number=10000, int decimalplace=1)

*Displays a `float` value.  Takes two values; one `int` and one `float`.  The first value is the `float` being displayed.  The second is where the decimal place is. For example, "12.24".*

void displaychar(char *stringd="NA")

*Displays a `String` value.  Takes one `String` value to be displayed.  For example, "Fun".*

void displayclear()

*Clears the display.*
