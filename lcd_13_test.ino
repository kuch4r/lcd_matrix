
/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*********************************************************************
I change the adafruit SSD1306 to SH1106

SH1106 driver don't provide several functions such as scroll commands.

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SH1106.h"
#include <Fonts/FreeSans24pt7b.h>

Adafruit_SH1106 displays[8];

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  Wire1.begin();

  for( int i = 0 ; i <= 7 ; i++ ) {
    Wire1.beginTransmission(0x70);
    Wire1.write(1 << i);
    Wire1.endTransmission();  

    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    displays[i].initDisplay(SH1106_EXTERNALVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    // init done
    
    // Clear the buffer.
    displays[i].clearDisplay();
    displays[i].setFont(&FreeSans24pt7b);
    displays[i].drawLine(0, 0, displays[i].width()-1, 0, WHITE);
    displays[i].drawLine(0, displays[i].height()-1, displays[i].width()-1, displays[i].height()-1, WHITE);
    {
      int16_t x,y;
      uint16_t w,h;
      displays[i].getTextBounds((char*)"99.9",0,0,&x,&y,&w,&h);
      Serial.print("Height ");
      Serial.println(h);
      h-=5;
      displays[i].setCursor((displays[i].width()-w)/2,((displays[i].height()-h)/2) +h);
    }
    
    //display.setCursor(0,36);
    displays[i].setTextSize(1);
    displays[i].setTextColor(WHITE);
    displays[i].println("99.9");
    displays[i].display();
  }  
}


void loop() {
  
}


