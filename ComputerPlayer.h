#ifndef __ComputerPlayer_H__
#define __ComputerPlayer_H__
#include "Player.h"

class ComputerPlayer : public Player
{
private:
    /* data */
public:
    /* コンストラクター */
    ComputerPlayer();
    ComputerPlayer(int stone_num);
    ~ComputerPlayer();
    /* メソッド */
    //name
    string get_name();
    //tutorial
    bool   does_need_tutorial();
    //action
    string get_action();
    string get_action(Board *board);
    int    evaluate_one_action(Board *board,int row,int column);
    int   computer_player_action(Board *board);
};

#endif