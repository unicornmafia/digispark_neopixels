// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

//#include "DigiKeyboard.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEOPIXEL_PIN            0
#define PWM_PIN                 4

#define RING1          0
#define RING2          1

#define DELAY_MAX      100
#define DELAY_MIN      10
#define PWM_MAX        2000
#define PWM_MIN        1000

#define DIR_COUNTERCLOCKWISE -1
#define DIR_CLOCKWISE         1

// How many NeoPixels are attached to the Arduino?
#define NUMRINGS       2
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS*NUMRINGS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);



int i1=0;
int i2=0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  
  long offColor = pixels.Color(0,0,50);
  for (int k=0;k<24;k++){
    pixels.setPixelColor(k,offColor);
  }
  pixels.show();
}

int getPixNum(int index, int offset, int ringNum){
  return ((NUMPIXELS+index+offset) % NUMPIXELS) + ringNum * (NUMPIXELS) ;
}

void loop() { 
  
  moveRing(i1,RING1,DIR_CLOCKWISE);
  moveRing(i2,RING2,DIR_COUNTERCLOCKWISE);
  int delayval = readSpeed();
  delay(delayval); // Delay for a period of time (in milliseconds).
}

long readSpeed(){
  int pwm = (int) pulseIn(PWM_PIN,HIGH);
  if (pwm<1000){
    pwm=1000;
  }
  
  long delayRange = DELAY_MAX-DELAY_MIN;
  long pwmRange = PWM_MAX-PWM_MIN;

  long ddelay =  delayRange + DELAY_MIN - (delayRange) * (pwm-PWM_MIN) / (pwmRange) ;
  
  return ddelay;
}

void moveRing(int &i, int ringNum, int motionDir){
  long onColor = pixels.Color(255,255,255);
  long onColor2 = pixels.Color(128,128,128);
  long onColor3 = pixels.Color(50,50,50);
  //long onColor4 = pixels.Color(5,5,5);
  long offColor = pixels.Color(0,0,50);
  // shut off the old trailing pixel
  pixels.setPixelColor(getPixNum(i,-2*motionDir, ringNum),offColor);
 
  
  i = (i+motionDir) % NUMPIXELS;
  
  pixels.setPixelColor(getPixNum(i, 0, ringNum),onColor);
  pixels.setPixelColor(getPixNum(i,-motionDir, ringNum),onColor2);
  pixels.setPixelColor(getPixNum(i,-2*motionDir, ringNum),onColor3);
  //pixels.setPixelColor(getPixNum(i,-3*motionDir, ringNum),onColor4);

  pixels.show(); // This sends the updated pixel color to the hardware.
}


