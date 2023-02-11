#include <Wire.h>
#include "./imagedata.h"


#include "./Sasa_SSD1306.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
//Sasa_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
#define LED_PIN 13

#define SW_PUSH 4
#define UP_PUSH 5
#define RT_PUSH 6
#define LT_PUSH 7
#define DW_PUSH 8

uint8_t old_button = 0x00;
uint8_t cat_x = 0;
uint8_t cat_y = 0;

uint8_t getSwitch(){
  uint8_t result = 0;
  old_button = 0x00;
  result += digitalRead( SW_PUSH );
  result += digitalRead( UP_PUSH ) << 1;
  result += digitalRead( RT_PUSH ) << 2;
  result += digitalRead( LT_PUSH ) << 3;
  result += digitalRead( DW_PUSH ) << 4;

  return ~result;
}

void Clear_Display_All(){
  uint8_t i, j, k;
  
  for(i = 0; i < 7; i++){//Page(0-7)
    Wire.beginTransmission(0x3C);
      Wire.write(0b10000000); //control byte, Co bit = 1, D/C# = 0 (command)
        Wire.write(0xB0 | i); //set page start address(B0～B7)
      Wire.write(0b00000000); //control byte, Co bit = 0, D/C# = 0 (command)
        Wire.write(0x21); //set Column Address
          Wire.write(0); //Column Start Address(0-127)
          Wire.write(127); //Column Stop Address(0-127)
    Wire.endTransmission();
  
    for(j = 0; j < 16; j++){//column = 8byte x 16
      Wire.beginTransmission(0x3C);
        Wire.write(0b01000000); //control byte, Co bit = 0 (continue), D/C# = 1 (data)
        for(k = 0; k < 8; k++){ //continue to 31byte
          Wire.write(0x00);
        }
      Wire.endTransmission();
    }
  }
}

void print_data(const unsigned char data[]){
  uint8_t i, j, k;
  //int *p;
  
  for(i = 0; i < 7; i++){//Page(0-7)
    Wire.beginTransmission(0x3C);
      Wire.write(0b10000000); //control byte, Co bit = 1, D/C# = 0 (command)
        Wire.write(0xB0 | i); //set page start address(B0～B7)
      Wire.write(0b00000000); //control byte, Co bit = 0, D/C# = 0 (command)
        Wire.write(0x21); //set Column Address
          Wire.write(0); //Column Start Address(0-127)
          Wire.write(127); //Column Stop Address(0-127)
    Wire.endTransmission();
  
    for(j = 0; j < 16; j++){//column = 8byte x 16
      Wire.beginTransmission(0x3C);
        Wire.write(0b01000000); //control byte, Co bit = 0 (continue), D/C# = 1 (data)
        for(k = 0; k < 8; k++){ //continue to 31byte
          Wire.write(data[0]);
          data+=2;
          Serial.println(*data);
        }
      Wire.endTransmission();
    }
  }

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PUSH, INPUT);
  //display.begin();
  //display.write();

Wire.beginTransmission(0x3C);//※このバイトも含めて、以後、合計32バイトまで送信できる。
  Wire.write(0b10000000); //制御バイト、Coビット=1、D/C#=0(コマンド)
    Wire.write(0xAE); //表示オフ
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0xA8); //マルチプレックス比の設定 0xA8, 0x3F
      Wire.write(0b00111111); //64MUX
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0 (コマンド)    
    Wire.write(0xD3); //表示オフセット0xD3, 0x00の設定
      Wire.write(0x00);
  Wire.write(0b10000000); //制御バイト、Coビット=1、D/C#=0(コマンド)
    Wire.write(0x40); //表示開始ライン設定 0x40
  Wire.write(0b10000000); //制御バイト、Coビット=1、D/C#=0(コマンド)
    Wire.write(0xA0); //セグメントリマップ設定 0xA0/0xA1
  Wire.write(0b10000000); //制御バイト、Coビット=1、D/C#=0(コマンド)
    Wire.write(0xC0); //COM出力スキャン方向設定 0xC0,/0xC8
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0xDA); //COMピンのハードウェア設定 0xDA, 0x02
      //Wire.write(0b00010010); //128＊64のOLED用
      Wire.write(0b00000010); //128＊32のOLED用
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0x81); //コントラスト制御0x81、デフォルト=0x7Fに設定
      Wire.write(100); //0-255
  Wire.write(0b10000000); //制御バイト、Coビット=1、D/C#=0(コマンド)
    Wire.write(0xA4); //ディスプレイ全体の点灯を無効にする。
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0xA6); //通常表示0xA6、逆表示0xA7を設定する。
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0xD5); //表示クロック分割比/発振器周波数設定 0xD5, 0x80
      Wire.write(0b10000000);
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0x20); //メモリアドレスモード設定
      Wire.write(0x10); //ページアドレスモード設定
Wire.endTransmission();
Wire.beginTransmission(0x3C);
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0x22); //ページアドレスの設定
      Wire.write(0); //ページ設定開始
      Wire.write(7);//エンドページ設定
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0x21); //カラムアドレスの設定
      Wire.write(0); //カラム開始アドレス
      Wire.write(127);//カラムストップアドレス
  Wire.write(0b00000000); //制御バイト、Coビット=0、D/C#=0(コマンド)
    Wire.write(0x8D); //チャージポンプレギュレータの有効化 0x8D, 0x14 off=0x10
      Wire.write(0x14);
  Wire.write(0b10000000); //制御バイト、Coビット=1、D/C#=0(コマンド)
    Wire.write(0xAF); //ディスプレイ表示ON
Wire.endTransmission();

  delay(500);

  Clear_Display_All();

  delay(500);
  print_data(bitmap_title);
  /*
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);             
  Wire.write(0x21); Wire.write(16); Wire.write(27);
  Wire.write(0x22); Wire.write(1); Wire.write(3);
  Wire.endTransmission();
  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  Wire.write(0xFC); Wire.write(0xFA); Wire.write(0xF6); Wire.write(0x0E); Wire.write(0x0E); Wire.write(0x0E);
  Wire.write(0x0E); Wire.write(0x0E); Wire.write(0x0E); Wire.write(0xF6); Wire.write(0xFA); Wire.write(0xFC);
  Wire.write(0xFF); Wire.write(0xFF); Wire.write(0xE7); Wire.write(0x00); Wire.write(0x00); Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  Wire.write(0x00); Wire.write(0x00); Wire.write(0x00); Wire.write(0xE7); Wire.write(0xFF); Wire.write(0xFF);
  Wire.write(0x3F); Wire.write(0x5F); Wire.write(0x6F); Wire.write(0x70); Wire.write(0x70); Wire.write(0x70);
  Wire.write(0x70); Wire.write(0x70); Wire.write(0x70); Wire.write(0x6F); Wire.write(0x5F); Wire.write(0x3F);
  Wire.endTransmission();
  //*/
}

void loop() {

  //ボタン状態取得
  uint8_t button = getSwitch();
  if(button != old_button && button != 0xE0){
    digitalWrite( LED_PIN, HIGH );
    Serial.println(button,BIN);
    if(button == 0xE2) {
      Serial.println("up");
      cat_x -= 1;
    }
    if(button == 0xE4) {
      Serial.println("right");
      cat_y += 1;
    }
    if(button == 0xE8) {
      Serial.println("light");
      cat_y -= 1;
    }
    if(button == 0xF0) {
      Serial.println("down");
      cat_x += 1;
    }

    delay(50);
    old_button = button;
    digitalWrite( LED_PIN, LOW );
  }
  
}


