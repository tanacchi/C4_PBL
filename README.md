# C4_PBL

H29前期 実践プログラミングPBL課題用

Elements | Description
--- | ---
EV3/ | EV3用のソースファイルを入れてる。
include/ | クラスオブジェクトのインクルードファイルを入れてる。
src/ | クラスオブジェクトのソースファイルを入れてる。
.gitignore | github用の設定ファイル。
README.md | ドキュメント。
build.sh | ビルドファイル。実行するとターミナル上で動く実行ファイルができる。
connect_4.ino | Arduino用ソースファイル。
console_play.cpp | ターミナル上で動かす用のプログラム
github_url.txt | 管理しているgithubリポジトリのURL

## ソフトウェア構成
本当はオブジェクト指向で設計したかったが  
シリアル通信が上手くいかなくなったのでやめた

Elements | Description
--- | ---
VirtualPlate | ゲームの進行状況を把握するための仮想のゲーム盤
HandSeeker | 有効打を探すオブジェクト
BodyController | ハードウェア制御用のオブジェクト（実装成らず）
GameMaster | ゲーム運用のためのオブジェクト（実装成らず）

## 動かすための手順（メンバー用）

1. 学校のパソコン（Windows）を起動・ログインしておく
2. [EV3Shieldのライブラリ](https://github.com/mindsensors/EVShield "EV3Shiled") を**Clone or download**(緑色のボタン)→Download ZIP をクリックしてダウンロード
3. 「ダウンロード」フォルダでEVShield-masterを右クリック→全て解凍→エンターキー
4. 同様に[tanacchi/C4_PBL](https://github.com/tanacchi/C4_PBL "connect_4")からダウンロード→解凍
5. 解凍した２つのフォルダを Zドライブの方に移動させる
6. C4_PBL -> connect_4 に名前を変換
7. EVShield-masterのＣドライブ直下のArduino/liblaries/の中にコピーする
8. EV3とArduinoをパソコンに接続
9. BricxCCを起動（usb : ev3 : Linux）
10. 「ファイル」→「開く」で先ほどのconnect_4の中のEV3/EV3.cを指定する
11. connect_4/connect_4.inoをダブルクリックでArduinoIDEを開く
12. ArduinoIDEでツールを設定する
13. ArduinoIDEで「マイコンボードに書き込む」
14. ArduinoをEV3に接続
15. BricxCCで Compile -> Download and Run

## 感想
HandSeekerの設計は関数オブジェクトを使いたかったのだが、Arduinoでサポートされてなかったので出来なかった。  
おそらく動かなかったのも new / delete 演算子がサポートされていなかったから。  
一応使えるようにする方法をあったようだが、時間が足りなさすぎて断念。
せっかく動かせるようにメモリ管理やり直したのになあ。  
完成こそしたが腑に落ちない部分もあったというのが正直な所。  
しかし今まで意識していなかったメモリ節約や通信制御で得られた経験というのもかなり大きい。  
今後に活かしていこう。

### Special thanks
* EV3テキストプログラミング用のヘッダファイル  
　[http://www.mns.kyutech.ac.jp/~hanazawa/education/downloads/index.html](http://www.mns.kyutech.ac.jp/~hanazawa/education/downloads/index.html "花沢研究室")
* EVShield用のライブラリ  
　[https://github.com/mindsensors/EVShield](https://github.com/mindsensors/EVShield "mindsensors/EVShield")

本当にありがとうございました
