#ifndef VIRTUAL_PLATE_H_
#define VIRTUAL_PLATE_H_

#define PLATE_HEIGHT 6
#define PLATE_WIDTH  7

enum class Stone {     // コマ識別用のデータ型
	Space,
	Red,
	Blue
};

/*
  終了判定に使うベクトル
  ４つ並んでいるかどうかは
  各地点から右上、右、右下、真下の４方向を調べるだけでよい
  また最後に置いた場所が始点or終点になるとは限らないので
  全ての自分のコマからの視点で調べる必要がある
*/
static const short dx[4] = { 1, 1, 1, 0 };
static const short dy[4] = {-1, 0, 1, 1 };

/*
  VirtualPlate(仮想盤面)
  プレート本体(plate_)の他、アクティブなプレイヤーが置くコマの種類(active_stone_)
  メンバ関数でプレートの振る舞いを実装した
*/
class VirtualPlate { 
 public:

  /*
    各種コンストラクタ
    デフォルトコンストラクタはplate_を全てスペースで、active_stone_を赤で初期化
    コピーコンストラクタは、各メンバ変数をコピー
    STLがサポートされていなかったので for文で１つずつ代入するしかなかった
   */
  VirtualPlate();
  VirtualPlate(const VirtualPlate& plate);

  
  /*
    代入演算子
    結局使わなかった
   */
  const VirtualPlate& operator=(const VirtualPlate& src);

  
  /*
    デストラクタ
   */
  ~VirtualPlate() = default;

  
  /*
    plate_の全ての要素にSpaceを代入
   */
  void init();

  
  /*
    src内のplate_を自分のにコピー
   */
  void copy_plate(const VirtualPlate& src);

  
  /*
    プレートの座標を指定して
    そこが最下層でなくて、かつ真下がスペースならtrueを返す
    下に落ちられるかどうかの判定をする
    インライン関数にしたかったけどコンパイラが許してくれない
   */
  bool can_drop(short x, short y) const;

  
  /*
    x座標を指定するとそこにコマを落とす
    どこまで落ちられるかをcan_dropで判定しているので
    これをコールするだけでＣ４の動きを再現できる
   */
  void insert(short input_x);

  
  /*
    アクティブなコマを切り替える(Red <--> Blue)
   */
  void switch_active_stone();

  
  /*
    ゲームの終了判定（引き分け）を行う
    全列の一番上を調べて１つでも落とせる列が見つかったらtrueを返す
   */
  bool can_continue() const;

  
  /*
    指定された座標がplateの中かどうかを判定する
    勝敗判定やキーボード入力の時に使う
   */
  bool is_inside_plate(short x, short y) const;

  
  /*
    ゲームの終了判定（勝敗）を行う
    アクティブなコマが４つ並んでいる箇所が１つでもあったらtrueを返す
    （非アクティブなコマを調べる必要はない）
   */
  bool is_game_finish() const;

  
  /*
    コマがいくつ連続で並んでいるかを返す
    第一、第二引数に始点となる座標、
    第三、第四引数に調べる方向のx, y成分を指定する
   */
  short get_length(short x, short y, short dx, short dy) const;

  
  /*
    不正な入力を弾く
    ゲームの進行の分岐に関係するので別個で宣言した
    引数に指定した列の一番上がSpaceならtrueを返す
    やはり別個で宣言する必要はなかったかもしれない
   */
  bool is_valid_hand(short x) const;

  
  /*
    アクティブなコマを返す
    HandSeeker内で必要であった
   */
  Stone get_active_stone() const;

  
  /*
    コンソールに表示する用
    コマ（Stone）を全角文字に変換する
   */
  friend const char* to_char(Stone stone);

  
  /*
    コンソールに表示する用
    plate_の状態を表示
   */
  friend void show(const VirtualPlate& plate);
private:
  Stone plate_[PLATE_HEIGHT][PLATE_WIDTH];  // プレート本体
  Stone active_stone_;                      // アクティブなコマ
};

#endif // VIRTUAL_PLATE_H_
