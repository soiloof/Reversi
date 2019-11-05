#ifndef __HumanPlayer_H__
#define __HumanPlayer_H__
#include "Player.h"

class HumanPlayer : public Player
{
private:
    /* data */
public:
    /* コンストラクター */
    HumanPlayer();
    HumanPlayer(int stone_num);
    ~HumanPlayer();
    /* メソッド */
    //name
    string get_name();
    //tutrial
    bool  does_need_tutorial();
    //action
    string  get_action();
    int  human_player_action(Board *board);
};

#endif