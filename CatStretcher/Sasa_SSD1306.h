#ifndef Sasa_SSD1306_h
#define Sasa_SSD1306_h
#include "arduino.h"
#include <Wire.h>

// クラスの定義
// クラス名・コンストラクタ名・関数名や使用する変数名を定義します。
class Sasa_SSD1306
{
  public:
    Sasa_SSD1306(uint8_t w, uint8_t h, TwoWire *twi = &Wire);
    void begin() ;
    void write() ;
  private:
    TwoWire *wire;
    uint8_t width;
    uint8_t height;
} ;

#endif