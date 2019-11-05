#include "Board.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <time.h>
//関数
int decide_player_stone_num(){
    /* 先攻を決める */
    unsigned int now = time(0);                /* 現在時刻をseed値にする */
    srand(now);
    int player_stone_num = rand()%2+1;         /* 乱数%2+1 = Black or White */
    return player_stone_num;
}
int print_message(string msg){
    /* メッセージ表示 */
    cout << msg << endl;
    return 0;
}
string get_winning_message(Player *player){
    return player->name + " win!";
}
string get_result_message(Player *p1,Player *p2){
    string result_message;
    if (p1->score > p2->score){
        result_message = get_winning_message(p1);
    }else if (p1->score < p2->score){
        result_message = get_winning_message(p2);
    }else{
        result_message = "draw!";
    }
    return result_message;    
}

int main(int argc, char const *argv[])
{
    //最初のメッセージ
    const string FIRST_MESSAGE = "それではゲームを開始します";
    print_message(FIRST_MESSAGE);
    //先攻を決める
    int player_stone_num = decide_player_stone_num();
    cout << player_stone_num << endl;
    //ゲームのプレイヤーオブジェクトを生成
    HumanPlayer *player1;
    player1 = new HumanPlayer(player_stone_num);
    ComputerPlayer *player2;
    player2 = new ComputerPlayer(opponent(player_stone_num));
    //プレイヤーの名前の取得
    player1->get_set_name();
    player2->get_set_name();
    //盤面のオブジェクトを生成
    Board *board;
    board = new Board;
    //プレイヤーに対してチュートリアルを実施
    player1->tutorial(board);
    player2->tutorial(board);
    //ゲーム開始の合図を表示
    const string start_message = player1->name + " vs " + player2->name + "\n";
    print_message(start_message);
    //ゲーム開始 1ターンごとの動きでループを回す
    while (board->is_exist_action(Black) || board->is_exist_action(White))
    {
        /* どちらかのプレイヤーが打てる手が存在する限り続行 */
        switch (player1->stone_num)
        /* 先攻によって場合分け */
        {
        case Black:
            player1->human_player_action(board);
            player2->computer_player_action(board);
            break;
        case White:
            player2->computer_player_action(board);
            player1->human_player_action(board);
        default:
            break;
        }
    }
    //最終盤面の表示
    board->show();
    //各プレイヤーのスコア計算
    player1->score = board->calc_result(player1->stone_num);
    player2->score = board->calc_result(player2->stone_num);
    //結果
    string result_message;
    result_message = get_result_message(player1,player2);
    //result表示
    print_message(result_message);
    //delete
    delete player1;
    delete player2; 
    delete board;
    return 0;
}
