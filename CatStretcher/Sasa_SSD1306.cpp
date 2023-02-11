#include "arduino.h"
#include "Sasa_SSD1306.h"

Sasa_SSD1306::Sasa_SSD1306(uint8_t w, uint8_t h, TwoWire *twi){
  width = w;
  height = h;
  *wire = *twi;
}

void Sasa_SSD1306::begin()
{
  wire->beginTransmission(0x3C);                    //デバイスアドレス
  wire->write(0x00);                                //Co=0, D/C#=0
  wire->write(0xA8); wire->write(height-1);            //総ライン数 64行：0x3F(63 DEC)
  wire->write(0xD3); wire->write(0x00);              //Set Display Offset 0x00
  wire->write(0x40);                                //Set Display Start Line 0x40
  wire->write(0xA1);                                //左右反転 0xA0/0xA1
  wire->write(0xC8);                                //上下反転 0xC0/0xC8
  wire->write(0xDA); wire->write(0x12);              //Set COM Pins hardware configuration//
  wire->write(0x81); wire->write(0xA0);              //コントラスト//0-255
  wire->write(0xA4);                                //Disable Entire Display On A4/A5
  wire->write(0xA6);                                //白黒反転 A6/A7
  wire->write(0xD5); wire->write(0x80);              //Oscillator Frequency 0x80
  wire->write(0x20); wire->write(0x00);              //Addressing Mode //horizontal 0x00
  wire->write(0x8D); wire->write(0x14);              //Set Enable charge pump regulator 0x8D, 0x14
  wire->write(0xAF);                                //Display On 0xAF
  wire->endTransmission();
}
// ＬＥＤを消灯する関数(メソド関数)
void Sasa_SSD1306::write()
{
  wire->beginTransmission(0x3C);
  wire->write(0x00);             
  wire->write(0x21); wire->write(16); wire->write(27);
  wire->write(0x22); wire->write(1); wire->write(3);
  wire->endTransmission();
  wire->beginTransmission(0x3C);
  wire->write(0x40);
  wire->write(0xFC); wire->write(0xFA); wire->write(0xF6); wire->write(0x0E); wire->write(0x0E); wire->write(0x0E);
  wire->write(0x0E); wire->write(0x0E); wire->write(0x0E); wire->write(0xF6); wire->write(0xFA); wire->write(0xFC);
  wire->write(0xFF); wire->write(0xFF); wire->write(0xE7); wire->write(0x00); wire->write(0x00); wire->write(0x00);
  wire->endTransmission();
  wire->beginTransmission(0x3C);
  wire->write(0x40);
  wire->write(0x00); wire->write(0x00); wire->write(0x00); wire->write(0xE7); wire->write(0xFF); wire->write(0xFF);
  wire->write(0x3F); wire->write(0x5F); wire->write(0x6F); wire->write(0x70); wire->write(0x70); wire->write(0x70);
  wire->write(0x70); wire->write(0x70); wire->write(0x70); wire->write(0x6F); wire->write(0x5F); wire->write(0x3F);
  wire->endTransmission();
}
