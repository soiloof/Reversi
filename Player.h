#ifndef __Player_H__
#define __Player_H__
// include
#include <vector>
#include <string>
#include "Board.h"
using namespace std;

class Player
{
/* プレイヤー親クラス */
public:
    /* data */
    string name;
    int stone_num;
    int score;
    vector<int> row_valid_action;              /* 選択可能な手の中でrowを保存しておく可変長配列 */
    vector<int> col_valid_action;              /* 選択可能な手の中でcolumnを保存しておく可変長配列 */ 
    /* コンストラクター */ 
    Player();
    Player(int player_stone_num);
    ~Player();
    /* メソッド */
    //name
    virtual string  get_name()=0;
    virtual string  get_str_stone();
    virtual void    set_name(string name,string stone);
    virtual void    get_set_name();
    //tutorial
    virtual bool    does_need_tutorial()=0;
    virtual void    print_tutorial();
    virtual void    tutorial(Board *board);
    //action
    virtual void    save_valid_action(Board *board);
    virtual void    show_valid_action();
    virtual void    ask_action();
    virtual string  get_action()=0;
};
#endif