
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
# Name（リポジトリ/プロジェクト/OSSなどの名前）
 
分かりやすくてカッコイイ名前をつける（今回は"hoge"という名前をつける）
 
"hoge"が何かを簡潔に紹介する
 
# DEMO
 
"hoge"の魅力が直感的に伝えわるデモ動画や図解を載せる
 
# Features
 
"hoge"のセールスポイントや差別化などを説明する
 
# Requirement
 
"hoge"を動かすのに必要なライブラリなどを列挙する
 
* huga 3.5.2
* hogehuga 1.0.2
 
# Installation
 
Requirementで列挙したライブラリなどのインストール方法を説明する
 
```bash
pip install huga_package
```
 
# Usage
 
DEMOの実行方法など、"hoge"の基本的な使い方を説明する
 
```bash
git clone https://github.com/hoge/~
cd examples
python demo.py
```
 
# Note
 
注意点などがあれば書く
 
# Author
 
作成情報を列挙する
 
* 作成者
* 所属
* E-mail
 
# License
ライセンスを明示する
 
"hoge" is under [MIT license](https://en.wikipedia.org/wiki/MIT_License).
 
社内向けなら社外秘であることを明示してる
 
"hoge" is Confidential.

# ねこのばしポータブル取扱説明書
## 構成
| Core | ATMEGA328 |
| ファームウェア | Arduino Mini Core |
| バッテリー | CR2032 |
| ディスプレイ | SSD1306 (128*64) |
| ボタン | SKRHADE010 (上下左右押し込み)|
| スピーカ | ピエゾ素子 |
| 外部コネクタ | Grove(i2c) SSD1306と同じチャンネル |
## 操作方法
ボタンを押し込むと猫がのびて、
ボタンを離すと占いの結果を持ってきてくれます。
## プログラムの書き換え
別売りのUSB-Serial変換基板を使って、ArduinoIDEからプログラムの書き込みができます。
ピンアサインは以下の通り。
## できること
### 画面表示
SSD1306はi2cに接続されています。
### ボタン認識
ボタンの機能はそれぞれのGPIOに接続されています。
### スピーカ出力
スピーカはGPIOに接続されています。




