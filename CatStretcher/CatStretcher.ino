#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_SSD1306.hpp>

static LGFX_SSD1306 lcd;
static LGFX_Sprite canvas(&lcd);

#define LED_PIN 13

#define SW_PUSH 4
#define UP_PUSH 5
#define RT_PUSH 6
#define LT_PUSH 7
#define DW_PUSH 8

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PUSH, INPUT);

  Serial.begin( 9600 );

  //lcd設定
  lcd.init();
  canvas.setTextWrap(false);
  canvas.createSprite(lcd.width(), lcd.height());
}

void loop() {
  // put your main code here, to run repeatedly:
  byte button = getSwitch();
  
  digitalWrite( LED_PIN, HIGH );
  digitalWrite( LED_PIN, LOW );

  canvas.fillScreen(TFT_BLACK);
  canvas.setTextColor(TFT_WHITE);
  
  canvas.setCursor(0, 0);
  canvas.setFont(&fonts::lgfxJapanGothic_16);
  canvas.println("液晶表示");

  canvas.pushSprite(0, 0);
  delay(50);
}

byte getSwitch(){
  byte result = 0;
  result += digitalRead( SW_PUSH );
  result += digitalRead( UP_PUSH ) << 1;
  result += digitalRead( RT_PUSH ) << 2;
  result += digitalRead( LT_PUSH ) << 3;
  result += digitalRead( DW_PUSH ) << 4;
  
  Serial.println( result );
  return result;
}
