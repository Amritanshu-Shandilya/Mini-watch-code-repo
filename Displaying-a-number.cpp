#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

#define SDA 21
#define SCL 22

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1

//Digit 0 bytecode
const unsigned char epd_bitmap_M0 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0xff, 0xc0, 0x03, 0xfc, 0xc0, 0x07, 
	0x00, 0xc0, 0x0c, 0x70, 0xc0, 0x18, 0x70, 0xe0, 0x38, 0xe6, 0x60, 0x33, 0xce, 0x60, 0x37, 0xce, 
	0x60, 0x27, 0x9e, 0x60, 0x67, 0x36, 0x60, 0x67, 0x36, 0x60, 0x66, 0x66, 0x60, 0x60, 0xec, 0xc0, 
	0x20, 0xfc, 0xc0, 0x30, 0xf9, 0x80, 0x30, 0x03, 0x00, 0x38, 0x07, 0x00, 0x1f, 0xfc, 0x00, 0x07, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void writeHello() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.display();
  delay(1000);
}


void drawWatchFace(){
  display.clearDisplay();
  display.drawBitmap(0, 0, epd_bitmap_M0, 20, 25, 1);
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
  writeHello();

  drawWatchFace();
   
}

void loop(){
  //Empty
}

