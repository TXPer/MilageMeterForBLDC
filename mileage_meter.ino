#include <SPI.h>
#include <Wire.h>
#include <FreqMeasure.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
double sum=0;
int count=0;
int x=0;
int y=0;
float totalkm;



void setup() {
  FreqMeasure.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  totalkm = EEPROM.get(0, totalkm);
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);

  if(totalkm < 10000){
    display.clearDisplay();
    display.setCursor(20, 10); 
    display.setTextSize(2); 
    display.print("Mileage:");
    display.setCursor(5, 35); 
    display.print(totalkm, 1);
    display.print("  km"); 
    display.display();
  }
  else {
    display.clearDisplay();
    display.setCursor(20, 10); 
    display.setTextSize(2); 
    display.print("Mileage:");
    display.setCursor(5, 35); 
    display.print(totalkm, 1);
    display.print(" km"); 
    display.display();
    }
}



void loop() {

  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      x = x + 1;
      sum = 0;
      count = 0;
        if (x > 65){
        y = y + 1;
        totalkm = totalkm + 0.1;
        x = 0;
          if(totalkm < 10000){
            display.clearDisplay();
            display.setCursor(20, 10); 
            display.setTextSize(2); 
            display.print("Mileage:");
            display.setCursor(5, 35); 
            display.print(totalkm, 1);
            display.print("  km"); 
            display.display();
              if (y = 10){
                EEPROM.put(0, totalkm);
                y = y + 1;
              }
          else {
            display.clearDisplay();
            display.setCursor(20, 10); 
            display.setTextSize(2); 
            display.print("Mileage:");
            display.setCursor(5, 35); 
            display.print(totalkm, 1);
            display.print(" km"); 
            display.display();
          }
        }     
      }
    }
  }
}




