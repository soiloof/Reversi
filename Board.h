#ifndef __Board_H__
#define __Board_H__
#include <iostream>
using namespace std;
//定数
const int BOARD_SIZE = 10;
const int BOARD_FIRST = 1;
const int BOARD_LAST  = 8;
enum Stone_Num{Outside = -1, Space, Black, White};
enum Direction{NegativeDirection = -1, NonDirection, PositiveDirection};
//汎用関数
inline int opponent(int player_stone){
    return (Black+White)-player_stone;              //player = 1or2 => opponent = 2or1
}
inline int char_to_int_row(char row){
    return row-'1'+1;
}
inline int char_to_int_column(char col){
    return col-'a'+1;
}
inline char int_to_char_row(int row){
    row+=48;
    return (char)row;
}
inline char int_to_char_column(int col){
    col+=96;
    return (char)col;
}

class Board
{
/* 盤面の情報オブジェクト */
private:
    /* data */
    int board[BOARD_SIZE][BOARD_SIZE];
public:
    Board();
    ~Board();
    //表示
    void show();
    //盤面操作
    int  count_turn_over(int stone_num,int row,int column,int v_down,int v_right);
    void turn_over(int stone_num,int row,int column);
    bool is_legal_action(int stone_num,int row,int column);
    bool is_exist_action(int stone_num);
    //結果の表示
    int  calc_result(int stone_num);
};
#endif