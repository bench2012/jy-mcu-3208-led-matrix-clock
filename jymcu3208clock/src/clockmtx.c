// Clock programm for DX 32*8 LED Matrix + HT1632C + ATmega8; 
// DrJones 2012
// 20121227/ScottJ: change '1'; smaller colon; scroll-dot for second indicator
//
// button1: adjust time forward, keep pressed for a while for fast forward
// button2: adjust time backward, keep pressed for a while for fast backward
// button3: adjust brightness in 4 steps

// ScottJ 

//#define HOUR12 1

#define F_CPU 16000000

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

#define byte uint8_t
#define word uint16_t



static const byte bigdigits[12][6]  PROGMEM  = {

  {126,129,129,129,129,126}, // 0

  //{128,132,130,255,128,128}, // 1
  {  0,132,130,255,128,128}, // 1
  //0b10000000,
  //0b10000100,
  //0b10000010,
  //0b11111111,
  //0b10000000,
  //0b10000000,

  {130,193,161,145,137,134}, // 2

  { 66,129,137,137,137,118}, // 3

  {0x3f,0x20,0x20,0xfc,0x20,0x20}, // 4

  {0x4f,0x89,0x89,0x89,0x89,0x71}, // 5

  {0x7e,0x89,0x89,0x89,0x89,0x72}, // 6

  {0x03,0x01,0xc1,0x31,0x0d,0x03}, // 7

  {0x76,0x89,0x89,0x89,0x89,0x76}, // 8

  {0x46,0x89,0x89,0x89,0x89,0x7e}, // 9

  //{0x00,0x00,0x06,0x09,0x09,0x06},  // Degree
  {0x00, 0x06, 0x09, 0x09, 0x06, 0x00}, // Degree

  {0x00,0x7e,0x81,0x81,0x81,0x66}   // C
};




//pins and macros

#define HTport   PORTB
#define HTddr    DDRB
#define HTstrobe 3
#define HTclk    4
#define HTdata   5

#define HTclk0    HTport&=~(1<<HTclk)
#define HTclk1    HTport|= (1<<HTclk)
#define HTstrobe0 HTport&=~(1<<HTstrobe)
#define HTstrobe1 HTport|= (1<<HTstrobe)
#define HTdata0   HTport&=~(1<<HTdata)
#define HTdata1   HTport|= (1<<HTdata)
#define HTpinsetup() do{  HTddr |=(1<<HTstrobe)|(1<<HTclk)|(1<<HTdata); HTport|=(1<<HTstrobe)|(1<<HTclk)|(1<<HTdata);  }while(0)
        // set as output and all high


#define key1 ((PIND&(1<<7))==0)
#define key2 ((PIND&(1<<6))==0)
#define key3 ((PIND&(1<<5))==0)
#define keysetup() do{ DDRD&=0xff-(1<<7)-(1<<6)-(1<<5); PORTD|=(1<<7)+(1<<6)+(1<<5); }while(0)  //input, pull up


byte leds[32];  //the screen array, 1 byte = 1 column, left to right, lsb at top. 


#define HTstartsys   0b100000000010 //start system oscillator
#define HTstopsys    0b100000000000 //stop sytem oscillator and LED duty    <default
#define HTsetclock   0b100000110000 //set clock to master with internal RC  <default
#define HTsetlayout  0b100001000000 //NMOS 32*8 // 0b100-0010-ab00-0  a:0-NMOS,1-PMOS; b:0-32*8,1-24*16   default:ab=10
#define HTledon      0b100000000110 //start LEDs
#define HTledoff     0b100000000100 //stop LEDs    <default
#define HTsetbright  0b100101000000 //set brightness b=0..15  add b<<1  //0b1001010xxxx0 xxxx:brightness 0..15=1/16..16/16 PWM
#define HTblinkon    0b100000010010 //Blinking on
#define HTblinkoff   0b100000010000 //Blinking off  <default
#define HTwrite      0b1010000000   // 101-aaaaaaa-dddd-dddd-dddd-dddd-dddd-... aaaaaaa:nibble adress 0..3F   (5F for 24*16)

//ADRESS: MSB first
//DATA: LSB first     transferring a byte (msb first) fills one row of one 8*8-matrix, msb left, starting with the left matrix
//timing: pull strobe LOW, bits evaluated at rising clock edge, strobe high
//commands can be queued: 100-ccccccccc-ccccccccc-ccccccccc-... (ccccccccc: without 100 at front)
//setup: cast startsys, setclock, setlayout, ledon, brightness+(15<<1), blinkoff

//Temperature read and display time
//#define temp 24
#define ds_sec 2 //Temp display time (sec)
#define temp_ds 300 //Temp display interval (sec)

void HTsend(word data, byte bits) {  //MSB first
  word bit=((word)1)<<(bits-1);
  while(bit) {
    HTclk0;
    if (data & bit) HTdata1; else HTdata0;
    HTclk1;
    bit>>=1;
  }
}

void HTcommand(word data) {
  HTstrobe0;
  HTsend(data,12);
  HTstrobe1;
}

void HTsendscreen(void) {
  cli();
  HTstrobe0;
  HTsend(HTwrite,10);
  for (byte mtx=0;mtx<4;mtx++)  //sending 8x8-matrices left to right, rows top to bottom, MSB left
    for (byte row=0;row<8;row++) {  //while leds[] is organized in columns for ease of use.
      byte q=0;
      for (byte col=0;col<8;col++)  q = (q<<1) | ( (leds[col+(mtx<<3)]>>row)&1 ) ;
      HTsend(q,8);
    }
  HTstrobe1;
  sei();
}


void HTsetup() {  //setting up the display
  HTcommand(HTstartsys);
  HTcommand(HTledon);
  HTcommand(HTsetclock);
  HTcommand(HTsetlayout);
  HTcommand(HTsetbright+(1<<1));
  HTcommand(HTblinkoff);
}

void HTbrightness(byte b) {
  HTcommand(HTsetbright + ((b&15)<<1) );
}

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
  byte col=0;

int tmp = temp;

<<<<<<< HEAD
 // for (byte i=0;i<6;i++) leds[col++]=0; //Blank Char
 cli(); 
  for (byte i=0;i<4;i++) leds[col++]=0; //Blank Char
 
=======
  for (byte i=0;i<12;i++) leds[col++]=0; //Blank Char
  
>>>>>>> with-temp
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[tmp/10][i]);   // Temperature 10th digit
  leds[col++]=0;

  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[tmp%10][i]);   // Temperature  1st digit
  leds[col++]=0;

  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[10][i]);  // Degree 
  //leds[col++]=0;

  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[11][i]);  // C
  leds[col++]=0;
sei();

}
//-------------------------------------------------------------------------------------- clock render ----------

void renderclock(void) {
  byte col=0;

byte hr = hour;
#ifdef HOUR12
  if (hour>12) {hr=hour-12;}
  if (hour==0) {hr=12;}
#endif

  //ScottJ  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hour/10][i]);   // HR 10th digit
#ifdef HOUR12
  if ( (hr/10) > 0) {
     for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hr/10][i]);   // HR 10th digit
  } else {
     // display blank instead of 0
     for (byte i=0;i<6;i++) leds[col++]=0;   // HR 10th digit
  }
#else
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hr/10][i]);   // HR 10th digit
#endif
  leds[col++]=0;

  //ScottJ  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hour%10][i]);   // HR  1st digit
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hr%10][i]);   // HR  1st digit
  leds[col++]=0;

  // flash colon every 2 seconds
  // 0x66 = 01100110
  if (sec%2) {leds[col++]=0x66;leds[col++]=0x66;} else {leds[col++]=0; leds[col++]=0;}
  // 0x24 = 0010 0100
  //if (sec%2) {leds[col++]=0x00;leds[col++]=0x24;} else {leds[col++]=0; leds[col++]=0;}  //SAJ  smaller colon: 0x24 
  leds[col++]=0;

  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[minute/10][i]);  // MI 10th digit
  leds[col++]=0;

  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[minute%10][i]);  // MI  1st digit
  leds[col++]=0;

  // progressive bar second indicator
  //leds[col++]=(sec>6) +((sec>13)<<1) +((sec>20)<<2) +((sec>26)<<3) +((sec>33)<<4) +((sec>40)<<5) +((sec>46)<<6) +((sec>53)<<7);

  // scrolling dot second indicator
  leds[col++]= (1<<(sec/8));
}



byte changing, bright=3;
byte brights[4]={0,2,6,15}; //brightness levels

int main(void) {  //==================================================================== main ==================

  HTpinsetup();
  HTsetup();
  keysetup();
  initADC();
  clocksetup();

  for (byte i=0;i<32;i++) leds[i]=0b01010101<<(i%2);  HTsendscreen();


  hour=7;minute=40;

  while(1){ 
         if (key2) {if (changing>250) incsec(20); else {changing++; incsec(1);} }
    else if (key3) {if (changing>250) decsec(20); else {changing++; decsec(1);} }
    else if (key1) {if (!changing) {changing=1; bright=(bright+1)%4; HTbrightness(brights[bright]);} } //only once per press
    else changing=0;
    if (sixty_sec>=61) {
      sixty_sec=0;
      sec++;
   }
    if (clockhandler()) { //Time update check
      temphandler();
      if (tempsec==0) { //Check if Temp display time is reach
        renderclock(); 
        HTsendscreen(); 
        } 
      else {
        --tempsec; //Dec Time display time
        rendertemp(); 
        HTsendscreen();
        }
       // temp=ReadADC(2);
       // temp=temp/2;
    }  
  }
  return(0);
}//main
