# C4_PBL

H29前期 実践プログラミングPBL課題用

## ソフトウェア構成（暫定）

Elements | Description
--- | ---
VirtualPlate | ゲームの進行状況を把握するための仮想のゲーム盤
HandSeeker | コンピューターのために有効打を探して教えてくれる子

## Check List
- [x] とりあえずゲーム進行に合わせて動くか  
- [ ] EV3Shield側からデータを送信してプログラム終了の合図が出せるか(どっちのターンとかもわかると良いね)  
- [ ] BodyControlerを実装できるか  
- [ ] GameMasterを再び構築できるか  
- [ ] その他リファクタリング  

## 動かすための手順

1. 学校のパソコン（Windows）を起動・ログインしておく
2. [EV3Shieldのライブラリ](https://github.com/mindsensors/EVShield "shiled") を**Clone or download**(緑色のボタン)→Download ZIP をクリックしてダウンロード
3. 「ダウンロード」フォルダでEVShield-masterを右クリック→全て解凍→エンターキー
4. 同様に[tanacchi/C4_PBL](https://github.com/tanacchi/C4_PBL "connect_4")からダウンロード→解凍
5. 解凍した２つのフォルダをＤドライブの方に移動させる
6. C4_PBL -> connect_4 に名前を変換
7. EVShield-masterのＣドライブ直下のArduino/liblaries/の中にコピーする
8. EV3とArduinoをパソコンに接続
9. BricxCCを起動（usb : ec3 : Linux）
10. 「ファイル」→「開く」で先ほどのconnect_4の中のEV3/EV3.cを指定する
11. connect_4/connect_4.inoをダブルクリックでArduinoIDEを開く
12. ArduinoIDEでツールを設定する
13. ArduinoIDEで「マイコンボードに書き込む」
14. ArduinoをEV3に接続
15. BricxCCで Compile -> Download and Run

