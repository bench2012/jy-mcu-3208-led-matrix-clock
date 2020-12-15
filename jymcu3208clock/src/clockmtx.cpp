// Clock programm for DX 32*8 LED Matrix + HT1632C + ATmega8; 
// DrJones 2012
// 20121227/ScottJ: change '1'; smaller colon; scroll-dot for second indicator
//
// button1: adjust time forward, keep pressed for a while for fast forward
// button2: adjust time backward, keep pressed for a while for fast backward
// button3: adjust brightness in 4 steps

// ScottJ 

//#define HOUR12 1
#include "Arduino.h"
#define F_CPU 16000000

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <HT1632.h>
HT1632Class LEDmatrix;

// active array size:
const byte xSize = 32;
const byte ySize = 8;

#define byte uint8_t
#define word uint16_t


#define key1 PIN_PD7
#define key2 PIN_PD6
#define key3 PIN_PD5




//Temperature read and display time
//#define temp 24
#define ds_sec 2 //Temp display time (sec)
#define temp_ds 10 //Temp display interval (sec)


//------------------------------------------------------------------------------------- CLOCK ------------------


volatile byte sec=5;
volatile byte sixty_sec=0;




byte sec0=200, minute, hour, day, month; word year;


inline void clocksetup() {  // CLOCK, interrupt every second
  //ASSR |= (1<<AS2);    //timer2 async from external quartz
  TCCR2 |= (1 << CS22)|(1 << CS21)|(1<<CS20);    //normal,off,/1024; 16MHz/256/1024 = 61 Hz
  TCNT2 = 0;  // initialize counter
  TIMSK |= (1<<TOIE2); //enable timer2-overflow-int
  sei();               //enable interrupts
}


// CLOCK interrupt
ISR(TIMER2_OVF_vect) {     //timer2-overflow-int
cli();
  sixty_sec++;
sei();

}



void incsec(byte add) {
  sec+=add;
  while (sec>=60) { 
    sec-=60;  minute++;
    while (minute>=60) {
      minute -= 60;  hour++;
      while (hour >=24) {
        hour-=24;  day++;
      }//24hours
    }//60min
  }//60sec
}

void decsec(byte sub) {
  while (sub>0) {
    if (sec>0) sec--; 
    else {
      sec=59; 
      if (minute>0) minute--; 
      else {
        minute=59; 
        if (hour>0) hour--;
        else {hour=23;day--;}
      }//hour
    }//minute
    sub--;
  }//sec
}

byte clockhandler(void) {


  if (sec==sec0) return 0;   //check if something changed
  sec0=sec;
  incsec(0);  //just carry over
  return 1;
}

//------------------------------------------------------------------------------------- TEMPERATURE ------------------

volatile byte tempsec=0;
volatile byte temp_cs=temp_ds;
int temp;

int ReadADC(uint8_t ch) {
  ADMUX&=0xF0; ADMUX|=ch;// MUX values needed to be changed to use ch
  ADCSRA |= (1<<ADSC); // Start A2D Conversions 
  while(!(ADCSRA&(1<<ADIF)));  // Check the ADIF bit for ADC conversion completes
  ADCSRA|=(1<<ADIF); //Reset if complete
  _delay_ms(1); //Wait a bit (1ms)
  return(ADC); //and return ADC value for LM35
}

void initADC() {
  ADMUX=(1<<REFS0);// Set ADC reference to AVCC
  ADCSRA=((1<<ADEN)|(1<<ADFR)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));//ADC Enable,Free runninng, pre-scale=128 (125KHz sampling for 16MHz clock)
}

byte temphandler(void) {
    
  if (temp_cs!=0) { //Check if Temp display time interval reached
    --temp_cs; //Dec. Temp display time interval
    return 0;
  }     //check if something changed
  else{
    temp=ReadADC(2); //Read LM35 at ADC2
    temp=temp/2.01; //Convert since 5.1mV and for 1 degree C and 2 units of ADC = 1 degree (10bit)
    tempsec=ds_sec; //Set Temp display time
    temp_cs=temp_ds; //Reset Temp display time interval
    return 1;
  }

}
//-------------------------------------------------------------------------------------- temperature render ----------
void rendertemp(void) {

int tmp = temp;
        LEDmatrix.clear();
        LEDmatrix.printChar(3, 'C');
        LEDmatrix.printChar(2, 248);
        LEDmatrix.printChar(1,(tmp%10)+192);
        LEDmatrix.printChar(0,(tmp/10)+192);
        LEDmatrix.render();
}
//-------------------------------------------------------------------------------------- clock render ----------

void renderclock(void) {
    
  int current_time;  
  current_time=(hour*100)+minute;
  LEDmatrix.clear();
  LEDmatrix.writeChar(0,((current_time%10000))/1000+192,6);
  LEDmatrix.writeChar(8,((current_time%1000))/100+192,6);
  LEDmatrix.writeChar(18,(((current_time%100)/10))+192,6);
  LEDmatrix.writeChar(26,(current_time%10)+192,6);
 
  if (sec%2==0) { //flash dot on even and odd sec.
    LEDmatrix.writeChar(15,58,2); //Chnage to : for sec. indicator
  }
  else {
    LEDmatrix.writeChar(15,32,2); 
  }
  LEDmatrix.render(); // This updates the display on the screen.

}

void setup() {


  //initialize the display
  LEDmatrix.begin(PIN_PB3, PIN_PB4, PIN_PB5);  // CS, WR, DATA
  pinMode(key1,INPUT_PULLUP);
  pinMode(key2,INPUT_PULLUP);
  pinMode(key3,INPUT_PULLUP);
}

void loop() {  //==================================================================== main ==================

    byte changing, bright=1;
    byte brights[4]={0,2,6,15}; //brightness levels
    initADC();
    clocksetup();
    LEDmatrix.setBrightness(brights[bright]);


  hour=8;minute=40;

  while(1){ 
        if (!digitalRead(key2)) {
          if (sixty_sec>changing) incsec(20); 
          else incsec(1); 
        }
          else 
        if (!digitalRead(key3)) {
          if (sixty_sec>changing) decsec(20); 
          else decsec(1); 
        }
        if (!digitalRead(key1)) {
          if (sixty_sec>changing) {
            bright=(bright+1)%4; 
            LEDmatrix.setBrightness(brights[bright]);
          } 
        } //only once per press
    changing=sixty_sec;
     if (sixty_sec>=61) {
      sixty_sec=0;
      sec++;
      } 
    if (clockhandler()) { //Time update check
       
      temphandler();
      if (tempsec==0) { //Check if Temp display time is reach
        renderclock(); 
        } 
      else {
        --tempsec; //Dec Time display time
        rendertemp(); 
        }
    }
  }
} //main
