#include "ComputerPlayer.h"
using namespace std;

//定数
const int Corner = 100;
const int Next_To_Corner = 0;
const int NTNTC = 50; //Next_To_Next_To_Corner
const int Default = 10;
const int Default_Edge = 20;
const int Init_Setted = -1;

/* コンストラクター */
ComputerPlayer::ComputerPlayer(){
}
ComputerPlayer::ComputerPlayer(int stone_num) :Player(stone_num){
}
ComputerPlayer::~ComputerPlayer(){
}

/* メソッド */
//name
string ComputerPlayer::get_name(){
    /* complayerの名前はcom */
    return "com";
}
//tutorial
bool ComputerPlayer::does_need_tutorial(){
    return false;
}

//action
string ComputerPlayer::get_action(){
    string action = "1a";
    return action;
}
string ComputerPlayer::get_action(Board *board){
    /* 評価関数で評価の高い手をうつai */
    int row,column;
    int max = -1;           /* 評価関数の最低値0より小さい値 */
    for (int i = 0; i < row_valid_action.size(); i++)
    {
        /* 選択可能な手から評価関数によって最も得点の高い手を取得する */
        if (max < evaluate_one_action(board,row_valid_action[i],col_valid_action[i])) {
            max = evaluate_one_action(board,row_valid_action[i],col_valid_action[i]);
            row    = row_valid_action[i];
            column = col_valid_action[i];
        }
    }
    char act[] = {int_to_char_row(row),int_to_char_column(column),'\0'};
    string action(act,sizeof(act));
    return action;
}
int ComputerPlayer::evaluate_one_action(Board *board,int row,int column){
    /* 
    評価関数。引数の[r][c]ごとに評価テーブルに基づいた値+ひっくり返せる石の数の値を返す
    :評価テーブルの配分について
    角がもっとも優先度が高いため100pt,
    その近傍はおきたくないので最低の0pt,
    その近傍は優先度が高いので角より十分に低い50pt,
    その周りは角の近傍よりは優先度が高まるので10ptだがその中でも端は取られにくいことからやや優先度の高い20pt
    */
    const int evaluation_table[BOARD_SIZE][BOARD_SIZE]=
        {{Outside,        Outside,        Outside, Outside,      Outside,      Outside, Outside,        Outside,        Outside, Outside},
         {Outside,         Corner, Next_To_Corner,   NTNTC, Default_Edge, Default_Edge,   NTNTC, Next_To_Corner,         Corner, Outside}, 
         {Outside, Next_To_Corner, Next_To_Corner,   NTNTC,      Default,      Default,   NTNTC, Next_To_Corner, Next_To_Corner, Outside}, 
         {Outside,          NTNTC,          NTNTC,   NTNTC,      Default,      Default,   NTNTC,          NTNTC,          NTNTC, Outside}, 
         {Outside,   Default_Edge,        Default, Default,  Init_Setted,  Init_Setted, Default,        Default,   Default_Edge, Outside}, 
         {Outside,   Default_Edge,        Default, Default,  Init_Setted,  Init_Setted, Default,        Default,   Default_Edge, Outside}, 
         {Outside,          NTNTC,          NTNTC,   NTNTC,      Default,      Default,   NTNTC,          NTNTC,          NTNTC, Outside}, 
         {Outside, Next_To_Corner, Next_To_Corner,   NTNTC,      Default,      Default,   NTNTC, Next_To_Corner, Next_To_Corner, Outside}, 
         {Outside,         Corner, Next_To_Corner,   NTNTC, Default_Edge, Default_Edge,   NTNTC, Next_To_Corner,         Corner, Outside}, 
         {Outside,        Outside,        Outside, Outside,      Outside,      Outside, Outside,        Outside,        Outside, Outside}};
    int count=0;
    //8近傍全てについてcount_turn_overを実行しcountに加算していく
    for (int v_down = NegativeDirection; v_down <= PositiveDirection; v_down++) {
        for (int v_right = NegativeDirection; v_right <= PositiveDirection; v_right++) {
            if ((v_down == NonDirection) && (v_right == NonDirection)){continue;} 
            count += board->count_turn_over(stone_num,row,column,v_down,v_right);
        }
    }
    //evaluation_table+countを返す
    return evaluation_table[row][column]+count;
}
int ComputerPlayer::computer_player_action(Board *board){
        board->show();
        save_valid_action(board);
        string action;
        int row,column;
        if (! board->is_exist_action(stone_num)){
            cout << "pass" << endl;
            return 0;
        }
        do
        {
            ask_action();
            action = get_action(board);
            cout << action << endl;
            row = char_to_int_row(action[0]);
            column = char_to_int_column(action[1]);
        } while (! board->is_legal_action(stone_num,row,column));
        board->turn_over(stone_num,row,column); 
        return 0;
}
