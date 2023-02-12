#include "WString.h"
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"
#include <Wire.h>
#include "uRTCLib.h"
#include <SevSeg.h>
#include <dht.h>
#include "Clock_Pins.h"

unsigned long lastmillis=0;
unsigned long lastMillis=0;

bool AM;
bool buzzeralarm;
    
unsigned long startmillis=0;

class Clock
{
  public:

    SevSeg* sevseg;
    dht *DHT;	
    uRTCLib *rtc;

    Clock(SevSeg* s, dht *d, uRTCLib *r) : sevseg(s), DHT(d), rtc(r) {}
    
    void begin(int brightness=100){
      SetupPinModes();

      byte numDigits = 4;
      byte digitPins[] = {S7SEG_PIN_DIG1, S7SEG_PIN_DIG2, S7SEG_PIN_DIG3, S7SEG_PIN_DIG4};
      byte segmentPins[] = {S7SEG_PIN_A, S7SEG_PIN_B, S7SEG_PIN_C, S7SEG_PIN_D, S7SEG_PIN_E, S7SEG_PIN_F, S7SEG_PIN_G, S7SEG_PIN_DECIMAL};
      bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
      byte hardwareConfig = COMMON_ANODE; // See README.md for options
      bool updateWithDelays = false; // Default 'false' is Recommended
      bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
      bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

      sevseg->begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
      sevseg->setBrightness(brightness);

      URTCLIB_WIRE.begin();

      //attachInterrupt(digitalPinToInterrupt(PIN_PB2), isr_function, FALLING);//Switch3
    }

    void refresh(){
      rtc->refresh();
      sevseg->refreshDisplay();
    }

    float temperature(bool f=true){
      int readData = DHT->read11(DHT_PIN_DATA);
      if (f){
        return((DHT->temperature*1.8)+32);
      }
      else {
        return(DHT->temperature);
      }
    }
    float humidity(){
      int readData = DHT->read11(DHT_PIN_DATA);
      return(DHT->humidity);
    }

    void setalarm(int alarmnumber=1,int hour=5,int minute=0,int second=0,int day=1,bool pm=false,bool armed=true){
      alarm[alarmnumber].hour = hour;
      alarm[alarmnumber].minute = minute;
      alarm[alarmnumber].second = second;
      alarm[alarmnumber].day = day;
      alarm[alarmnumber].pm = pm;
      alarm[alarmnumber].armed = armed;
    }

    int gettime(){
      if (rtc->hour() > 12){
        AM=false;
        return(((rtc->hour()-12)*100)+rtc->minute());
      }
      else {
        AM=true;
        return((rtc->hour()*100)+rtc->minute());
      }
    }
    int gethour(){
      if (rtc->hour() > 12){
        return(rtc->hour()-12);
      }
      else {
        return(rtc->hour());
      }
    }

    void checkalarm(){
      for (int i=1;i<10;i++){
        if (alarm[i].armed == 1){
          if (alarm[i].hour == gethour()){
            if (alarm[i].minute == rtc->minute()){
              if (alarm[i].second == rtc->second()){
                if (alarm[i].pm == !AM){
                  buzzeralarm = true;
                }
              }
            }
          }
        }
      }
    } 

    void doalarm(int soundseq=1, int count=15, bool buttonoff = true){
      if (count < 10){count=10;}
      if (buzzeralarm == true){
        if (soundseq == 1){
          for (int i=0;i<count;i++){
            digitalWrite(Buzzer, HIGH);
            delay(500);
            digitalWrite(Buzzer, LOW);
            delay(500);
            if (buttonoff){
              if (digitalRead(Button1) == LOW){
                goto exit;
              }
            }
          }
        }
        else if (soundseq == 2){
          for (int i=0;i<count;i++){
            digitalWrite(Buzzer, HIGH);
            delay(1000);
            digitalWrite(Buzzer, LOW);
            delay(500);
            if (buttonoff){
              if (digitalRead(Button1) == LOW){
                goto exit;
              }
            }
          }
        }
        else if (soundseq == 3){
          for (int i=0;i<count;i++){
            digitalWrite(Buzzer, HIGH);
            delay(500);
            digitalWrite(Buzzer, LOW);
            delay(1000);
            if (buttonoff){
              if (digitalRead(Button1) == LOW){
                goto exit;
              }
            }
          }
        }
        else if (soundseq == 4){
          for (int i=0;i<count/2;i++){
            digitalWrite(Buzzer, HIGH);
            delay(1000);
            digitalWrite(Buzzer, LOW);
            delay(500);
            if (buttonoff){
              if (digitalRead(Button1) == LOW){
                goto exit;
              }
            }
          }
          delay(5000);
          for (int i=0;i<count/2;i++){
            digitalWrite(Buzzer, HIGH);
            delay(1000);
            digitalWrite(Buzzer, LOW);
            delay(500);
            if (buttonoff){
              if (digitalRead(Button1) == LOW){
                goto exit;
              }
            }
          }
        }
      }
      exit:
      buzzeralarm = false;
    }

    int potentiometer(int mapped=true){
      if (mapped){
        return(map(analogRead(POT1),0,1023,0,255));
      }
      else{
        return(analogRead(POT1));
      }
    }

    int ldr(int mapped=true){
      if (mapped){
        return(map(analogRead(LDR),0,1023,0,255));
      }
      else{
        return(analogRead(LDR));
      }
    }

    /*void isr_function(){
      buzzeralarm=false;
    }*/

    void beep(int t=200){
      digitalWrite(Buzzer, HIGH);
      delay(t);
      digitalWrite(Buzzer, LOW);
    }

    void rgb(int r, int g, int b){
      analogWrite(RGBRed, r);
      analogWrite(RGBGreen, g);
      analogWrite(RGBBlue, b);
    }

    void displayint(int number=10000, int decimalplace=2){
      sevseg->setNumber(number,decimalplace);
    }
    void displayfloat(float number=10000, int decimalplace=1){
      sevseg->setNumber(number,decimalplace);
    }
    void displaychar(char *stringd="NA"){
      sevseg->setChars(stringd);
    }
    void displayclear(){
      sevseg->blank();
    }
    
    bool button(int buttonnumber=1){
      if (buttonnumber==1){
        return(digitalRead(Button1));
      }
      else if (buttonnumber==2){
        return(digitalRead(Button2));
      }
      else if (buttonnumber==3){
        return(digitalRead(Button3));
      }
      else if (buttonnumber==4){
        return(digitalRead(Button4));
      }
    }
    bool slider(int buttonnumber=1){
      if (buttonnumber==1){
        return(digitalRead(SW1));
      }
      else if (buttonnumber==2){
        return(digitalRead(SW2));
      }
      else if (buttonnumber==3){
        return(digitalRead(SW3));
      }
      else if (buttonnumber==4){
        return(digitalRead(SW4));
      }
    }
    
    void timerstart(){
      startmillis=millis();
    }
  
    unsigned long timer(){
      return(millis() - startmillis);
    }
        
  private:
  
    struct alarmstruct {
      int hour=0;
      int minute=0;
      int second=0;
      int day=0;
      bool pm=false;
      bool armed=false;
    };
    alarmstruct alarm[10];

    void SetupPinModes(){
      pinMode(Button1, INPUT_PULLUP);
      pinMode(Button2, INPUT_PULLUP);
      pinMode(Button3, INPUT_PULLUP);
      pinMode(Button4, INPUT_PULLUP);
      pinMode(SW1, INPUT);
      pinMode(SW2, INPUT);
      pinMode(SW3, INPUT);
      pinMode(SW4, INPUT);
      pinMode(LDR, INPUT);
      pinMode(POT1, INPUT);
      pinMode(LED4, OUTPUT);
      pinMode(RGBRed, OUTPUT);
      pinMode(RGBGreen, OUTPUT);
      pinMode(RGBBlue, OUTPUT);
      pinMode(Buzzer, OUTPUT);
    }
    
};

#endif
