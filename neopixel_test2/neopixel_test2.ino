// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second
int i=0;
int j=6;
int f = 0;
int f1 = 1;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

int getPixNum(int index, int offset){
  return (NUMPIXELS+index+offset) % NUMPIXELS;
}

int rcolors[NUMPIXELS];
int bcolors[NUMPIXELS];

void loop() {
  
  i = (i+NUMPIXELS+1) % NUMPIXELS;
  j = (j+NUMPIXELS+1) % NUMPIXELS;

 
  for (int k=0;k<NUMPIXELS;k++)
  {
    rcolors[k]=0;
    bcolors[k]=0;
  }
  
  rcolors[i] = 255;
  rcolors[getPixNum(i,1)] = 50;
  rcolors[getPixNum(i,-1)] = 50;
  rcolors[getPixNum(i,2)] = 15;
  rcolors[getPixNum(i,-2)] = 15;
  
  bcolors[j] = 255;
  bcolors[getPixNum(j,1)] = 50;
  bcolors[getPixNum(j,-1)] = 50;
  bcolors[getPixNum(j,2)] = 15;
  bcolors[getPixNum(j,-2)] = 15;


  for (int k=0;k<NUMPIXELS;k++)
  {
    pixels.setPixelColor(k,rcolors[k],0,bcolors[k],255);
  }
  pixels.show();

  delay(delayval); // Delay for a period of time (in milliseconds).
 
}
