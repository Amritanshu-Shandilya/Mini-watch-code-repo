#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

#define SDA 21
#define SCL 22

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1

//WatchFace bytecode
const unsigned char watchface_code[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xfe, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawWatchFace(){
  display.clearDisplay();
  display.drawBitmap(0, 0, watchface_code, 128, 64, 1);
  display.display();
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000);
  display.clearDisplay();
  delay(1000);
  drawWatchFace();
   
}

void loop(){
  //Empty
}

