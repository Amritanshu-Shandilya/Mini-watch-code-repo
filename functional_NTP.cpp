#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>

#include <time.h>



// Resources
#include <numbers.h> //bytecode for digits

//Veiwers create your own secrets.h that currently holds wifi credentials to get time using NTP
#include <secrets.h> //passwords

#define SDA 21
#define SCL 22

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1

// Variables to save date and time
int GMT_offset = 19800;
int daylight_offset = 0;



// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayDay(int w_day){
    /*Code for displaying day of week on the screen.*/
    if (w_day == 0){

        display.println("Sunday");
    }
    else if (w_day == 1){
        display.println("Monday");
    }
    else if (w_day == 2){
        display.println("Tuesday");
    }
    else if (w_day == 3){
        display.println("Wednessday");
    }
    else if (w_day == 4){
        display.println("Thursday");
    }
    else if (w_day == 5){
        display.println("Friday");
    }
    else if (w_day == 6){
        display.println("Saturday");
    }
    else if (w_day == 7){
        display.println("Sunday");
    }
}

void setupText(int size){
  // Function to be called for setting size color and cursor position
  display.setTextSize(size);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
}

void connect2Wifi(){
  // Connect to Wi-Fi
  setupText(1);
  display.clearDisplay();
  display.println(F("Connecting to wifi"));
  display.display();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
  }
  display.clearDisplay();
  display.println(F("Connection successful"));
  display.println(WiFi.localIP());
  display.display();
}

void drawWatchFace(){
  //code to draw and update watchface
	int i;
  setupText(1);
  display.clearDisplay();
	for (i=0; i<10; i++){
		display.clearDisplay();
  	display.drawBitmap(18, 19, number_array[i], 20, 25, 1);
		display.drawBitmap(40, 19, number_array[i], 20, 25, 1);
		display.drawBitmap(67, 19, number_array[i], 20, 25, 1);
		display.drawBitmap(88, 19, number_array[i], 20, 25, 1);
  	display.display();
		delay(1000);
		if (i==9)
			i=-1;
	}
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //display.clearDisplay();
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    // Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  // Connect to Wi-Fi
  connect2Wifi();

  display.clearDisplay();
  // delay(1000);
  // drawWatchFace();

  configTime(GMT_offset, daylight_offset, "pool.ntp.org","time.nist.gov");
 
}

void loop(){

  time_t rawtime = time(nullptr);
  struct tm* timeinfo = localtime(&rawtime);

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print(timeinfo->tm_hour);
  display.print(":");
  if( timeinfo->tm_min <10)
  display.print("0");
  display.print(timeinfo->tm_min);
  display.display();
  display.setTextSize(2);
  display.setCursor(80,15);
  display.print(":");
  if( timeinfo->tm_sec <10)
  display.print("0");
  display.print(timeinfo->tm_sec); 
  display.setCursor(0,40);
  displayDay(timeinfo -> tm_wday);
  display.display();

  
  delay(1000); 

}
