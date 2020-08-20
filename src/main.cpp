#include <Arduino.h>
#include <M5StickC.h>

#define TFT_GREY 0x5AEB // New colour

void setup(void) {
  M5.begin();
  M5.Lcd.setRotation(3);
}

void loop() {
  
  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  M5.Lcd.fillScreen(TFT_GREY);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'M5.Lcd.println'
  //  or stay on the line is there is room for the text with M5.Lcd.print)
  M5.Lcd.setCursor(0, 0, 2);
  // Set the font colour to be yellow with no background, set to font 6
  M5.Lcd.setTextColor(TFT_ORANGE); 
  M5.Lcd.println("Don't SHAKE it!");
  
  delay(1000);
}