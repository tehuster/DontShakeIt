/*
  This Unit connects to GRVOE B on M5Core.
  hx711 library fork from https://github.com/aguegu/ardulibs/tree/master/hx711
*/

#include <M5StickC.h>
#include "hx711.h"

#define FRONT 1

#define X_LOCAL 40
#define Y_LOCAL 40
#define X_F 30
#define Y_F 30

HX711 scale(33, 32);

void header(const char *string, uint16_t color){
    M5.Lcd.fillScreen(color);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_MAGENTA, TFT_BLUE);
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLUE);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(string, 160, 3, 4);  
}


void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.setCursor(2, 2,FRONT);
  M5.Lcd.print("Connect Unit to GROVE B");

  M5.Lcd.setCursor(2,11,FRONT);
  M5.Lcd.print("Btn_A to reset");
  Serial.begin(115200);
}

float weight;

void loop(){
    M5.update();
    if (M5.BtnA.wasReleased()) {
      scale.setOffset(scale.averageValue());
    }
    weight =scale.getGram();
    Serial.println(weight);
    M5.Lcd.setCursor(2,21,FRONT);
    M5.Lcd.printf("                             ");
    M5.Lcd.setCursor(2,31,FRONT);
    M5.Lcd.printf("weight:%0.2f g     ",weight);
}
