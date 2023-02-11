#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

#define LED_PIN 13

#define SW_PUSH 4
#define UP_PUSH 5
#define RT_PUSH 6
#define LT_PUSH 7
#define DW_PUSH 8


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

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PUSH, INPUT);

  Serial.begin( 9600 );
	display.clearDisplay();

	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.println("Hello, OLED SSD1306");
	display.display();

}

void loop() {
  // put your main code here, to run repeatedly:
  byte button = getSwitch();
  
  digitalWrite( LED_PIN, HIGH );
  digitalWrite( LED_PIN, LOW );


  delay(150);
}


