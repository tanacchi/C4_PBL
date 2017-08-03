#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.hpp"

/*
  列番号とスコアを記憶するためのデータ型
*/
typedef struct {
  short position_;
  float score_;
} HandList;


/*
  先読みをするためのクラスオブジェクト
  メンバに仮想盤面と自分の型のポインタをもち、再帰的に処理を行ことで
  樹形図的に広がるパターンを全て査定することができる
*/
class HandSeeker {
public:

  /*
    各コンストラクタ
    デフォルトコンストラクタにとる引数で
    「何手先まで読むのか」を指定することができる
   */
  HandSeeker(unsigned short max_depth = 5);
  HandSeeker(const HandSeeker& src);


  /*
    デストラクタ
   */
  ~HandSeeker() = default;


  /*
    引数に現時点の盤面をとり、最適な手を検索して数値で返す
    Arduino側ではこれを呼び出すだけで良い
    各列の点数を決定し、その点数で並び替えて最適な手を決定する
   */
  short get_conclusion(VirtualPlate game_plate);

  /*
    列の点数を決定する関数
    列の数だけ自分の複製をメンバの仮想盤面にコマを挿入しながら作成・削除し
    再帰処理を行う
   */
  float get_list_score();

  /*
    仮想盤面の状態を見て、点数化する関数
   */
  float evaluate_plate();
private:
  const HandSeeker& operator=(const HandSeeker&); // コンストラクタ以外で自分の複製は作らない
  VirtualPlate myplate_;   // 仮想盤面
  HandList hand_list_[PLATE_WIDTH]; // 列ごとの点数を記録するためのリスト
  HandSeeker* sub_;           // 自分の複製を作るためのポインタ
  Stone mystone_;             // 呼び出した時のアクティブなコマ
  const unsigned short max_depth_;   // 調べる階層
  unsigned short mydepth_;     // 現在の階層
};

#endif // HAND_SEEKER_H_
