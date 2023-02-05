// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
// クラス名はLGFXからLGFX_SSD1306に変更してます。（コンストラクタ名も）
class LGFX_SSD1306 : public lgfx::LGFX_Device {
  // 接続するOLED表示器にあったインスタンスを準備します。
  lgfx::Panel_SSD1306   _panel_instance;  // SSD1306を使用する場合
  lgfx::Bus_I2C   _bus_instance;          // I2Cバスのインスタンス (ESP32のみ)

  // コンストラクタを作成し、ここで各種設定を行います。
  public:
    LGFX_SSD1306() {  // コンストラクタ名はクラス名に合わせてLGFXからLGFX_SSD1306に変更してます。（クラス名と同じにする）
      { // バス制御の設定を行います。
        auto cfg = _bus_instance.config();  // I2Cバス設定用の構造体を取得します。
        cfg.i2c_port    = 0;          // 使用するI2Cポートを選択 (0 or 1)
        cfg.freq_write  = 400000;     // 送信時のクロック
        cfg.freq_read   = 400000;     // 受信時のクロック
        cfg.pin_sda     = 27;         // SDAを接続しているピン番号
        cfg.pin_scl     = 28;         // SCLを接続しているピン番号
        cfg.i2c_addr    = 0x3C;       // I2Cデバイスのアドレス

        _bus_instance.config(cfg);    // 設定値をバスに反映します。
        _panel_instance.setBus(&_bus_instance); // バスをパネルにセットします。
      }
      { // 表示パネル制御の設定を行います。
        // 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。
        auto cfg = _panel_instance.config();  // 表示パネル設定用の構造体を取得します。
        cfg.memory_width  = 128;      // ドライバICがサポートしている最大の幅
        cfg.memory_height =  32;      // ドライバICがサポートしている最大の高さ

        _panel_instance.config(cfg);  // 設定をパネルに反映
      }
      setPanel(&_panel_instance);     // 使用するパネルをセットします。
    }
};
