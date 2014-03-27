#include <Adafruit_NeoPixel.h>

float movement = 0;

float brightness = 64;
float size = 10;
float worldWidth = 40;
float worldHeight = 40;
int ledFactor = 3;

int minShade = -1;
int maxShade = 1;

const int DATAPIN = 6;
const int LEDCOUNT = 24;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDCOUNT, DATAPIN, NEO_GRB + NEO_KHZ800);

class LED
{
public:
      int x;
      int y;
      LED(int _x, int _y)
      {
        x=_x;
        y=_y;
      }
 };

  

  
//each line is a vertical on the vest  
LED leds[LEDCOUNT] = 
{
 LED(0,1), LED(0, 2), LED(0,3), LED(0,4), LED(0,5), LED(0,6), LED(0,7), LED(0,8), LED(0,9), LED(0,10),
 LED(1, 0),LED(1,1),LED(1,2),LED(1,3),LED(1,4),LED(1,5),LED(1,6),LED(1,7),LED(1,8),LED(1,9),LED(1,10),LED(1,11),LED(1,12),LED(1,13) 
};
 
 
void setup()
{
  strip.begin();
  movement = random(0,20); //randomize start pattern
}

void loop()
{
  Plasma();
  //delay(10);
}

void Plasma()
{
  int r,g,b;
  float shade = 0;
 
  for(int i = 0; i<LEDCOUNT; i++)
  {
    //get the xy co-ordinates and spread out by factor.
    LED c = leds[i];
    c.x*=ledFactor;
    c.y*=ledFactor;

      shade = SinVerticle(c.x,c.y,size)
            + SinRotating(c.x,c.y,size) 
            + SinCircle(c.x,c.y, size);
 
    //r = map( sin(shade*PI)*100, minShade, maxShade, 0, brightness);
    //g = map( sin(shade*PI+2*PI/3)*100, minShade, maxShade, 0, brightness);
    //b = map( sin(shade*PI+4*PI/3)*100, minShade, maxShade, 0, brightness);
     
    r = map( sin(shade*PI)*100, minShade, maxShade, 0, brightness);
    g = map( sin(shade*PI+2*PI*sin(movement/23))*100, minShade, maxShade, 0, brightness);
    b = map( sin(shade*PI+4*PI*sin(movement/20))*100, minShade, maxShade, 0, brightness);
      
      strip.setPixelColor(i,Color(r,g,b));
 
    }
  
    movement+=0.03;
    strip.show();
    
    //self correct mapping values to use maximum led resolution
    if(sin(shade*PI)*100 < minShade) minShade = sin(shade*PI)*100;
    if(sin(shade*PI)*100 > maxShade) maxShade = sin(shade*PI)*100;
  
    //show the last frame/pixel
    /*
    Serial.print("Shade="); Serial.println(shade);
    Serial.print("r="); Serial.print(r); Serial.print("From="); Serial.println(sin(shade*PI));
    Serial.print("g="); Serial.print(g); Serial.print("From="); Serial.println(sin(shade*PI+2*PI*sin(movement/23)));
    Serial.print("b="); Serial.print(b); Serial.print("From="); Serial.println(sin(shade*PI+4*PI*sin(movement/20)));
    Serial.println();
    */
}

float SinVerticle(float x, float y, float size)
{
  return sin(x / size + movement);
}
 
float SinRotating(float x, float y, float size)
{
  return sin( (x * sin(movement/50 ) + y * cos(movement/44)) /size ) ;
}
 
float SinCircle(float x, float y, float size)
{
  float cx = worldWidth * sin(movement/10);
  float cy = worldHeight * cos(movement/10);
  float dist = sqrt(sq(cy-y) + sq(cx-x));
  return sin((dist/size ) + movement );
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}


