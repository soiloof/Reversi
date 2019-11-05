// include
#include "Player.h"
#include <iostream>
using namespace std;

/* コンストラクター */
Player::Player(void){
    printf("デフォルトコンストラクタ\n");
}
Player::Player(int player_stone_num){ 
    stone_num = player_stone_num;
}
Player::~Player(){
}

/* メソッド */
//player_name
string Player::get_str_stone(){
    switch (stone_num)
    {
    case Black:
        return "(○)";
        break;
    case White:
        return "(●)";
        break;
    default:
        return "";
        break;
    }
}
void Player::set_name(string name,string stone){
    this->name = name+stone;
}
void Player::get_set_name(){
    string player_name = get_name();
    string stone = get_str_stone();
    set_name(player_name,stone);
}


//tutorial
void Player::print_tutorial(){
    cout << "最初はこの盤面から始まります。先攻が○、後攻が●です。"   << endl
         << "自分の色で相手の色を挟むとひっくりかえすことができます"  << endl
         << "例えば先攻が5fにおくと5eの●がひっくり返り○になります"  << endl
         << "どこにおいてもひっくり返すことができない時は自動的にpassとなります。"
         << "それ以外でpassはできません" << endl
         << "これをお互い繰り返し、"
         << "最終的におく場所がお互いなくなった時に自分の色の石が多い方が勝ちです。" << endl;
}
void Player::tutorial(Board *board){
    if(does_need_tutorial()){
        board->show();
        print_tutorial();
    }
}

//action
void Player::save_valid_action(Board *board){
    /* playerが打つことが可能な手[row_valid_action][col_valid_action]を毎回初期化してその盤面に対応したものを格納する */
    row_valid_action.clear();
    col_valid_action.clear();
    for (int row = BOARD_FIRST; row <= BOARD_LAST; row++)
    {
        for (int column = BOARD_FIRST; column <= BOARD_LAST; column++){
            if(board->is_legal_action(stone_num,row,column)){
                row_valid_action.push_back(row);
                col_valid_action.push_back(column);
            }
        }
    }
}
void Player::show_valid_action(){
    for (int i = 0; i < row_valid_action.size(); i++)
    {
        /* code */
        cout << row_valid_action[i] << int_to_char_column(col_valid_action[i]) << " ";
    }
    cout << endl;
}
void Player::ask_action(){
    cout << name << "さんのターンです。どこに置きますか?（選択可能なのは以下です）" << endl;
    show_valid_action();
}



