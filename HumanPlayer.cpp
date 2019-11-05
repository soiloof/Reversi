#include "HumanPlayer.h"
using namespace std;

/* コンストラクター */
HumanPlayer::HumanPlayer(){
}
HumanPlayer::HumanPlayer(int stone_num) :Player(stone_num){
}
HumanPlayer::~HumanPlayer(){
}

/* メソッド */
//name
string HumanPlayer::get_name(){
    string player_name;
    cout << "あなたの名前は何ですか？" << endl << "-> ";
    cin >> player_name;
    return player_name;
}
//tutorial
bool  HumanPlayer::does_need_tutorial(){
    char answer;
    while (true)
    {
        /* code */
        cout << name << "さん、ReversiのTutorialが必要ですか？[y/n] ";
        cin >> answer;
        switch (answer)
        {
        case 'y':
            return true;
            break;
        case 'n':
            return false;
        default:
            cout << "不正な値です" << endl;
            break;
        }
    }
}
//action
string HumanPlayer::get_action(){
    string action;
    cin >> action;
    return action;
}
int HumanPlayer::human_player_action(Board *board){
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
            /* code */
            ask_action();
            action = get_action();
            row = char_to_int_row(action[0]);
            column = char_to_int_column(action[1]);
        } while (! board->is_legal_action(stone_num,row,column));
        board->turn_over(stone_num,row,column);
        return 0;
}