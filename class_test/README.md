# class_test

Bodycontrollerの実装に向けたテストを行う
Serial通信はビット演算を利用して8ビットずつ送受信すること

* serial通信に必要なプログラム(SerialBeginなど)をclass内で実行するようにしてArduinoは呼び出すだけみたいな
* EV3shield-EV3IntelligentBlockの相互通信(タッチセンサーとモーターのみ)
* 専用のEV3,Arduinoのソースコードもこちらで管理
* テスト終了次第消す

## EV3のすること
* モーター・センサー識別用の配列かなんかを用意
* センサーへの命令なのかモーターへの命令なのか識別する
* SerialReadでどのセンサーを調べるのか読む
* 呼ばれたセンサーの状態をSerialWriteで返す
* SerialReadでどのモーターをどのくらい動かすのか読む
* モーターを動かす

## Arduinoのすること
* Tester tester();
* if (tester.is_pressed(1)) tester.run_motor(4);
* if (tester.is_pressed(4)) tester.run_motor(1);

## Tester(class)のすること
* 初期化・ポート振り分け
* 