#include <Arduino.h>
#include <Adafruit_NeoPixel.h>



#define BT_RED D1
#define BT_BLUE D3
#define BT_GREEN D5
#define BT_PINK D6
#define BRIGHTNESS 255
#define LED_COUNT  15
#define LED_PIN D7

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);



#define TIMEOUT 8000
#define TIMESTEP (TIMEOUT/LED_COUNT)

#define RED 1
#define GREEN 2
#define BLUE 3
#define PINK 4

long pressed[5] = {0,0,0,0,0};
int mode = 0;
int startTime = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(BT_RED, INPUT_PULLUP);
  pinMode(BT_GREEN, INPUT_PULLUP);
  pinMode(BT_BLUE, INPUT_PULLUP);
  pinMode(BT_PINK, INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);


  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void setStripColor(int mode, int count){
  int r,g,b;
  switch(mode){
    case RED:
      r = 255;
      g = 0;
      b = 0;
      break;
    case GREEN:
      r = 0;
      g = 255;
      b = 0;
      break;
    case BLUE:
      r = 0;
      g = 0;
      b = 255;
      break;
    case PINK:
      r = 255;
      g = 0;
      b = 0;
      break;
    default:
      r = 127;
      g = 127;
      b = 0;
      break;
  }
  for(int i=0; i < LED_COUNT; i++){
    if(i < count){
      strip.setPixelColor(i,r,g,b);
    }else{
      strip.setPixelColor(i,0,0,0);
    }
  }
  strip.show();
}

void loop() {
  // get timestamps for pressed buttons
  int m = millis();
  if(digitalRead(BT_RED)==LOW && pressed[RED] == 0){
    pressed[RED] = m;
  }
  if(digitalRead(BT_GREEN)==LOW && pressed[GREEN] == 0){
    pressed[GREEN] = m;
  }
  if(digitalRead(BT_BLUE)==LOW && pressed[BLUE] == 0){
    pressed[BLUE] = m;
  }
  if(digitalRead(BT_PINK)==LOW && pressed[PINK] == 0){
    pressed[PINK] = m;
  }

  // run for mode if a button is active
  if(mode != 0){
    int passedTime = millis() - startTime;
    if(passedTime > TIMEOUT){
      // TIMEOUT
      pressed[mode] = 0;
      mode = 0;

    }else{
      setStripColor(mode,LED_COUNT-(passedTime/TIMESTEP));
    }
  }

  if(mode == 0){
    int min = 0;
    for( int i = 1; i <= 4; i++){
      if( pressed[i] > 0 && (pressed[i] < pressed[min] || min == 0)){
        min = i;
      }
    }
    mode = min;
    startTime = millis();
  }

}